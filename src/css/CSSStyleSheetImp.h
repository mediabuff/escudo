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

#ifndef ORG_W3C_DOM_BOOTSTRAP_CSSSTYLESHEETIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_CSSSTYLESHEETIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/css/CSSStyleSheet.h>

#include <org/w3c/dom/stylesheets/StyleSheet.h>
#include <org/w3c/dom/css/CSSRule.h>

#include <deque>

#include "StyleSheetImp.h"
#include "CSSRuleListImp.h"

namespace org { namespace w3c { namespace dom { namespace bootstrap {

class DocumentImp;
typedef std::shared_ptr<DocumentImp> DocumentPtr;

class CSSStyleSheetImp : public ObjectMixin<CSSStyleSheetImp, StyleSheetImp>
{
    Retained<CSSRuleListImp> ruleList;

public:
    void append(css::CSSRule rule, const DocumentPtr& document);

    // StyleSheet
    virtual std::u16string getType();

    // CSSStyleSheet
    css::CSSRule getOwnerRule();
    css::CSSRuleList getCssRules();
    unsigned int insertRule(const std::u16string& rule, unsigned int index);
    void deleteRule(unsigned int index);
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return css::CSSStyleSheet::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return css::CSSStyleSheet::getMetaData();
    }
};

typedef std::shared_ptr<CSSStyleSheetImp> CSSStyleSheetPtr;

}}}}  // org::w3c::dom::bootstrap

#endif  // ORG_W3C_DOM_BOOTSTRAP_CSSSTYLESHEETIMP_H_INCLUDED
