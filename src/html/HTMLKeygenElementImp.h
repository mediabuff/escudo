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

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLKEYGENELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLKEYGENELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLKeygenElement.h>
#include "HTMLElementImp.h"

#include <org/w3c/dom/html/HTMLElement.h>
#include <org/w3c/dom/NodeList.h>
#include <org/w3c/dom/html/HTMLFormElement.h>
#include <org/w3c/dom/html/ValidityState.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class HTMLKeygenElementImp : public ObjectMixin<HTMLKeygenElementImp, HTMLElementImp>
{
public:
    HTMLKeygenElementImp(DocumentImp* ownerDocument) :
        ObjectMixin(ownerDocument, u"keygen")
    {
    }

    // Node - override
    virtual Node cloneNode(bool deep = true) {
        auto node = std::make_shared<HTMLKeygenElementImp>(*this);
        node->cloneAttributes(this);
        if (deep)
            node->cloneChildren(this);
        return node;
    }

    // HTMLKeygenElement
    bool getAutofocus();
    void setAutofocus(bool autofocus);
    std::u16string getChallenge();
    void setChallenge(const std::u16string& challenge);
    bool getDisabled();
    void setDisabled(bool disabled);
    html::HTMLFormElement getForm();
    std::u16string getKeytype();
    void setKeytype(const std::u16string& keytype);
    std::u16string getName();
    void setName(const std::u16string& name);
    std::u16string getType();
    bool getWillValidate();
    html::ValidityState getValidity();
    std::u16string getValidationMessage();
    bool checkValidity();
    void setCustomValidity(const std::u16string& error);
    NodeList getLabels();
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::HTMLKeygenElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::HTMLKeygenElement::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLKEYGENELEMENTIMP_H_INCLUDED
