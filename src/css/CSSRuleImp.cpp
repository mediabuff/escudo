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

#include "CSSRuleImp.h"
#include "CSSStyleSheetImp.h"

namespace org { namespace w3c { namespace dom { namespace bootstrap {

void CSSRuleImp::setParentStyleSheet(const CSSStyleSheetPtr& sheet)
{
    parentStyleSheet = sheet;
}

void CSSRuleImp::setParentRule(const CSSRulePtr& rule)
{
    parentRule = rule;
}

// CSSRule
unsigned short CSSRuleImp::getType()
{
    return 0;  // UNKNOWN_RULE, obsoleted by CSSOM
}

std::u16string CSSRuleImp::getCssText()
{
    return u"";
}

void CSSRuleImp::setCssText(const std::u16string& cssText)
{
}

css::CSSRule CSSRuleImp::getParentRule()
{
    return parentRule.lock();
}

css::CSSStyleSheet CSSRuleImp::getParentStyleSheet()
{
    return parentStyleSheet.lock();
}

}}}}  // org::w3c::dom::bootstrap
