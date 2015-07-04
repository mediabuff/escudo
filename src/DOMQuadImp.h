// Generated by esidl 0.4.0.
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_DOMQUADIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_DOMQUADIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/DOMQuad.h>

#include <org/w3c/dom/DOMPoint.h>
#include <org/w3c/dom/DOMPointInit.h>
#include <org/w3c/dom/DOMRectReadOnly.h>
#include <org/w3c/dom/DOMQuad.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class DOMQuadImp : public ObjectMixin<DOMQuadImp>
{
public:
    // DOMQuad
    DOMPoint getP1();
    DOMPoint getP2();
    DOMPoint getP3();
    DOMPoint getP4();
    DOMRectReadOnly getBounds();
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return DOMQuad::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return DOMQuad::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_DOMQUADIMP_H_INCLUDED