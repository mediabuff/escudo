/*
 * Copyright 2010-2013 Esrille Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "HTMLLinkElementImp.h"

#include <boost/bind.hpp>
#include <boost/version.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

#include "one_at_a_time.hpp"

constexpr auto Intern = &one_at_a_time::hash<char16_t>;

#include "DocumentImp.h"
#include "DOMTokenListImp.h"
#include "WindowProxy.h"
#include "HTMLUtil.h"
#include "css/BoxImage.h"
#include "css/CSSInputStream.h"
#include "css/CSSParser.h"
#include "css/CSSStyleSheetImp.h"
#include "css/Ico.h"

#include "Test.util.h"

namespace org { namespace w3c { namespace dom { namespace bootstrap {

HTMLLinkElementImp::HTMLLinkElementImp(DocumentImp* ownerDocument) :
    ObjectMixin(ownerDocument, u"link"),
    dirty(false),
    current(0)
{
    tabIndex = -1;
}

HTMLLinkElementImp::HTMLLinkElementImp(const HTMLLinkElementImp& org) :
    ObjectMixin(org),
    dirty(false),
    current(0),
    styleSheet(org.styleSheet) // TODO: make a clone sheet, too?
{
}

void HTMLLinkElementImp::resetStyleSheet()
{
    if (styleSheet) {
        styleSheet = nullptr;
        if (auto document = getOwnerDocumentImp())
            document->resetStyleSheets();
    }
}

void HTMLLinkElementImp::handleMutation(events::MutationEvent mutation)
{
    switch (Intern(mutation.getAttrName().c_str())) {
    case Intern(u"media"):
        if (styleSheet) {
            styleSheet.setMedia((mutation.getAttrChange() != events::MutationEvent::REMOVAL) ? mutation.getNewValue() : u"");
            if (DocumentPtr document = getOwnerDocumentImp()) {
                // TODO: Optimize the following steps later
                if (WindowProxyPtr view = document->getDefaultWindow())
                    view->setViewFlags(Box::NEED_SELECTOR_REMATCHING);
            }
        }
        break;
    case Intern(u"href"):
    case Intern(u"rel"):
    case Intern(u"hreflang"):
    case Intern(u"type"):
    case Intern(u"sizes"):
        requestRefresh();
        break;
    default:
        HTMLElementImp::handleMutation(mutation);
        break;
    }
}

void HTMLLinkElementImp::notify(NotificationType type)
{
    requestRefresh();
}

void HTMLLinkElementImp::requestRefresh()
{
    if (dirty)
        return;
    dirty = true;

    DocumentPtr owner = getOwnerDocumentImp();
    assert(owner);
    if (WindowProxyPtr window = owner->getDefaultWindow()) {
        Task task(self(), boost::bind(&HTMLLinkElementImp::refresh, this));
        window->putTask(task);
    }
}

void HTMLLinkElementImp::refresh()
{
    if (!dirty)
        return;
    dirty = false;

    std::u16string href = getHref();
    if (!href.empty()) {
        DocumentPtr document = getOwnerDocumentImp();
        std::u16string rel = getRel();
        toLower(rel);
        if (::contains(rel, u"stylesheet")) {
            // TODO: check "type"
            if (!::contains(rel, u"alternate")) {
                if (current)
                    current->cancel();
                current = std::make_shared<HttpRequest>(document->getDocumentURI());
                if (current) {
                    current->open(u"GET", href);
                    current->setHandler(boost::bind(&HTMLLinkElementImp::linkStyleSheet, this, current));
                    document->incrementLoadEventDelayCount(current->getURL());
                    current->send();
                    return; // Do not reset styleSheet.
                }
            }
        } else if (::contains(rel, u"icon")) {
            if (current)
                current->cancel();
            current = std::make_shared<HttpRequest>(document->getDocumentURI());
            if (current) {
                current->open(u"GET", href);
                current->setHandler(boost::bind(&HTMLLinkElementImp::linkIcon, this, current));
                document->incrementLoadEventDelayCount(current->getURL());
                current->send();
            }
        }
    }
    resetStyleSheet();
}

void HTMLLinkElementImp::linkStyleSheet(const HttpRequestPtr& request)
{
    if (current != request)
        return;

    DocumentPtr document = getOwnerDocumentImp();
    if (current->getStatus() == 200) {
        boost::iostreams::stream<boost::iostreams::file_descriptor_source> stream(current->getContentDescriptor(), boost::iostreams::close_handle);
        CSSParser parser(current->getURL());
        CSSInputStream cssStream(stream, current->getResponseMessage().getContentCharset(), utfconv(document->getCharacterSet()));
        styleSheet = parser.parse(document, cssStream);
        if (auto imp = std::dynamic_pointer_cast<CSSStyleSheetImp>(styleSheet.self()))
            imp->setOwnerNode(self());
        styleSheet.setMedia(getMedia());
        if (4 <= getLogLevel())
            dumpStyleSheet(std::cerr, styleSheet.self());
        document->resetStyleSheets();
        if (WindowProxyPtr view = document->getDefaultWindow())
            view->setViewFlags(Box::NEED_SELECTOR_REMATCHING);
    }
    document->decrementLoadEventDelayCount(request->getURL());
}

void HTMLLinkElementImp::linkIcon(const HttpRequestPtr& request)
{
    if (current != request)
        return;

    DocumentPtr document = getOwnerDocumentImp();
    setFavicon(document);
    document->decrementLoadEventDelayCount(request->getURL());
}

bool HTMLLinkElementImp::setFavicon(const DocumentPtr& document)
{
    std::u16string rel = getRel();
    toLower(rel);
    if (!::contains(rel, u"icon"))
        return false;
    if (!current || current->getStatus() != 200)
        return false;
    bool result = false;
    if (FILE* file = current->openFile()) {
        std::u16string type = getType();
        if (type == u"image/vnd.microsoft.icon" || type.empty()) {
            IcoImage ico;
            if (ico.open(file)) {
                if (WindowProxyPtr view = document->getDefaultWindow()) {
                    view->setFavicon(&ico, file);
                    result = true;
                }
            }
        } else {
            BoxImage image;
            image.open(file);
            if (image.getState() == BoxImage::CompletelyAvailable) {
                if (WindowProxyPtr view = document->getDefaultWindow()) {
                    view->setFavicon(&image);
                    result = true;
                }
            }
        }
        fclose(file);
    }
    return result;
}

// HTMLLinkElement
bool HTMLLinkElementImp::getDisabled()
{
    if (!styleSheet)
        return false;
    return styleSheet.getDisabled();
}

void HTMLLinkElementImp::setDisabled(bool disabled)
{
    if (styleSheet)
        styleSheet.setDisabled(disabled);
}

std::u16string HTMLLinkElementImp::getHref()
{
    return getAttributeAsURL(u"href");
}

void HTMLLinkElementImp::setHref(const std::u16string& href)
{
    setAttribute(u"href", href);
}

std::u16string HTMLLinkElementImp::getRel()
{
    return getAttribute(u"rel");
}

void HTMLLinkElementImp::setRel(const std::u16string& rel)
{
    setAttribute(u"rel", rel);
}

DOMTokenList HTMLLinkElementImp::getRelList()
{
    return std::make_shared<DOMTokenListImp>(std::static_pointer_cast<HTMLLinkElementImp>(self()), u"rel");
}

std::u16string HTMLLinkElementImp::getMedia()
{
    return getAttribute(u"media");
}

void HTMLLinkElementImp::setMedia(const std::u16string& media)
{
   setAttribute(u"media", media);
}

std::u16string HTMLLinkElementImp::getHreflang()
{
    return getAttribute(u"hreflang");
}

void HTMLLinkElementImp::setHreflang(const std::u16string& hreflang)
{
   setAttribute(u"hreflang", hreflang);
}

std::u16string HTMLLinkElementImp::getType()
{
    return getAttribute(u"type");
}

void HTMLLinkElementImp::setType(const std::u16string& type)
{
    setAttribute(u"type", type);
}

DOMSettableTokenList HTMLLinkElementImp::getSizes()
{
    // TODO: implement me!
    return nullptr;
}

void HTMLLinkElementImp::setSizes(const std::u16string& sizes)
{
    // TODO: implement me!
}

stylesheets::StyleSheet HTMLLinkElementImp::getSheet()
{
    return styleSheet;
}

std::u16string HTMLLinkElementImp::getCharset()
{
    // TODO: implement me!
    return u"";
}

void HTMLLinkElementImp::setCharset(const std::u16string& charset)
{
    // TODO: implement me!
}

std::u16string HTMLLinkElementImp::getRev()
{
    // TODO: implement me!
    return u"";
}

void HTMLLinkElementImp::setRev(const std::u16string& rev)
{
    // TODO: implement me!
}

std::u16string HTMLLinkElementImp::getTarget()
{
    // TODO: implement me!
    return u"";
}

void HTMLLinkElementImp::setTarget(const std::u16string& target)
{
    // TODO: implement me!
}

}}}}  // org::w3c::dom::bootstrap
