/*
 * Copyright 2011-2013 Esrille Inc.
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

#include "HistoryImp.h"

#include <org/w3c/dom/html/Location.h>

#include <iostream>
#include "utf.h"

#include "DocumentImp.h"
#include "WindowProxy.h"

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{

HistoryImp::
SessionHistoryEntry::SessionHistoryEntry(const URL& url, const WindowPtr& window) :
    url(url),
    window(window)
{
}

HistoryImp::
SessionHistoryEntry::SessionHistoryEntry(const WindowPtr& window) :
    url(window->getDocument()->getURL()),
    window(window)
{
}

HistoryImp::
SessionHistoryEntry::SessionHistoryEntry(const SessionHistoryEntry& other) :
    url(other.url),
    window(other.window)
{
}

void HistoryImp::removeAfterCurrent()
{
    if (!sessionHistory.empty()) {
        if (!replace) {
            Document currentDocument = sessionHistory.back().window->getDocument();
            if (sessionHistory.size() == 1 && currentDocument.getURL() == u"about:blank")
                replace = true;
            else if (currentDocument.getReadyState() != u"complete")
                replace = true;
        }
        sessionHistory.erase(sessionHistory.begin() + currentSession + (replace ? 0 : 1), sessionHistory.end());
    }
}

void HistoryImp::update(const URL& url, const WindowPtr& window)
{
    removeAfterCurrent();
    replace = false;
    SessionHistoryEntry e(url, window);
    sessionHistory.push_back(e);
    currentSession = getLength() - 1;

    if (auto document = window->getDocument())
        document->setURL(static_cast<std::u16string>(url));
}

void HistoryImp::update(const WindowPtr& window)
{
    removeAfterCurrent();
    replace = false;
    SessionHistoryEntry e(window);
    sessionHistory.push_back(e);
    currentSession = getLength() - 1;
}

int HistoryImp::getLength()
{
    return static_cast<int>(sessionHistory.size());
}

Any HistoryImp::getState()
{
    // TODO: implement me!
    return 0;
}

void HistoryImp::go()
{
    if (sessionHistory.empty())
        return;
    SessionHistoryEntry& e = sessionHistory[currentSession];
    if (auto document = e.window->getDocument())
        document->getLocation().reload();
}

void HistoryImp::go(int delta)
{
    if (sessionHistory.empty())
        return;
    if (delta == 0) {
        go();
        return;
    }
    int nextSession = currentSession + delta;
    if (getLength() <= nextSession)
        nextSession = getLength() - 1;
    else if (nextSession < 0)
        nextSession = 0;
    if (nextSession != currentSession) {
        currentSession = nextSession;
        SessionHistoryEntry& e = sessionHistory[currentSession];
        window->setWindowPtr(e.window);
    }
}

void HistoryImp::back()
{
    go(-1);
}

void HistoryImp::forward()
{
    go(1);
}

void HistoryImp::pushState(Any data, const std::u16string& title)
{
    // TODO: implement me!
}

void HistoryImp::pushState(Any data, const std::u16string& title, const std::u16string& url)
{
    // TODO: implement me!
}

void HistoryImp::replaceState(Any data, const std::u16string& title)
{
    // TODO: implement me!
}

void HistoryImp::replaceState(Any data, const std::u16string& title, const std::u16string& url)
{
    // TODO: implement me!
}

}
}
}
}
