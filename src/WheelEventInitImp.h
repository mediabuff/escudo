// Generated by esidl 0.3.0.
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_WHEELEVENTINITIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_WHEELEVENTINITIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/events/WheelEventInit.h>

#include <org/w3c/dom/events/EventTarget.h>
#include <org/w3c/dom/html/Window.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class WheelEventInitImp : public ObjectMixin<WheelEventInitImp>
{
public:
    // WheelEventInit
    bool getBubbles();
    void setBubbles(bool bubbles);
    bool getCancelable();
    void setCancelable(bool cancelable);
    html::Window getView();
    void setView(html::Window view);
    int getDetail();
    void setDetail(int detail);
    int getScreenX();
    void setScreenX(int screenX);
    int getScreenY();
    void setScreenY(int screenY);
    int getClientX();
    void setClientX(int clientX);
    int getClientY();
    void setClientY(int clientY);
    bool getCtrlKey();
    void setCtrlKey(bool ctrlKey);
    bool getShiftKey();
    void setShiftKey(bool shiftKey);
    bool getAltKey();
    void setAltKey(bool altKey);
    bool getMetaKey();
    void setMetaKey(bool metaKey);
    unsigned short getButton();
    void setButton(unsigned short button);
    unsigned short getButtons();
    void setButtons(unsigned short buttons);
    events::EventTarget getRelatedTarget();
    void setRelatedTarget(events::EventTarget relatedTarget);
    double getDeltaX();
    void setDeltaX(double deltaX);
    double getDeltaY();
    void setDeltaY(double deltaY);
    double getDeltaZ();
    void setDeltaZ(double deltaZ);
    unsigned int getDeltaMode();
    void setDeltaMode(unsigned int deltaMode);
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return events::WheelEventInit::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return events::WheelEventInit::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_WHEELEVENTINITIMP_H_INCLUDED
