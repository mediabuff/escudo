// Generated by esidl 0.3.0.
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLMARQUEEELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLMARQUEEELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLMarqueeElement.h>
#include "HTMLElementImp.h"

#include <org/w3c/dom/events/EventHandlerNonNull.h>
#include <org/w3c/dom/html/HTMLElement.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class HTMLMarqueeElementImp : public ObjectMixin<HTMLMarqueeElementImp, HTMLElementImp>
{
public:
    // HTMLMarqueeElement
    std::u16string getBehavior();
    void setBehavior(const std::u16string& behavior);
    std::u16string getBgColor();
    void setBgColor(const std::u16string& bgColor);
    std::u16string getDirection();
    void setDirection(const std::u16string& direction);
    std::u16string getHeight();
    void setHeight(const std::u16string& height);
    unsigned int getHspace();
    void setHspace(unsigned int hspace);
    int getLoop();
    void setLoop(int loop);
    unsigned int getScrollAmount();
    void setScrollAmount(unsigned int scrollAmount);
    unsigned int getScrollDelay();
    void setScrollDelay(unsigned int scrollDelay);
    bool getTrueSpeed();
    void setTrueSpeed(bool trueSpeed);
    unsigned int getVspace();
    void setVspace(unsigned int vspace);
    std::u16string getWidth();
    void setWidth(const std::u16string& width);
    events::EventHandlerNonNull getOnbounce();
    void setOnbounce(events::EventHandlerNonNull onbounce);
    events::EventHandlerNonNull getOnfinish();
    void setOnfinish(events::EventHandlerNonNull onfinish);
    events::EventHandlerNonNull getOnstart();
    void setOnstart(events::EventHandlerNonNull onstart);
    void start();
    void stop();
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::HTMLMarqueeElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::HTMLMarqueeElement::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLMARQUEEELEMENTIMP_H_INCLUDED
