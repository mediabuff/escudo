/*
 * Copyright 2013 Esrille Inc.
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

#ifndef ORG_W3C_DOM_BOOTSTRAP_UINT8ARRAYIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_UINT8ARRAYIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/Uint8Array.h>

#include <org/w3c/dom/ArrayBuffer.h>
#include <org/w3c/dom/Uint8Array.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class Uint8ArrayImp : public ObjectMixin<Uint8ArrayImp>
{
public:
    // Uint8Array
    unsigned int getLength();
    unsigned char get(unsigned int index);
    virtual void set(unsigned int index, unsigned char value);
    virtual void set(Uint8Array array);
    virtual void set(Uint8Array array, unsigned int offset);
    virtual void set(ObjectArray<unsigned char> array);
    virtual void set(ObjectArray<unsigned char> array, unsigned int offset);
    virtual Uint8Array subarray(int start, int end);
    // ArrayBufferView
    ArrayBuffer getBuffer();
    unsigned int getByteOffset();
    unsigned int getByteLength();
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return Uint8Array::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return Uint8Array::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_UINT8ARRAYIMP_H_INCLUDED
