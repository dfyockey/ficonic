/*
 * HtmlTagAccessor.hpp
 *
 *  Created on: Jul 25, 2023
 *      Author: David Yockey
 *
 * Copyright © 2023 David Yockey
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

#ifndef SRC_HTMLTAGACCESSOR_HPP_
#define SRC_HTMLTAGACCESSOR_HPP_

#include "IconsRetriever.hpp"
#include <htmlcxx/html/ParserDom.h>
#include <string>
#include "ficon.hpp"

using namespace htmlcxx;
using std::string;

class HtmlTagAccessor : virtual protected IconsRetriever {
protected:
	typedef tree<HTML::Node>::iterator nodeItr;
private:
	string html;
	string prev_url;
protected:
	string getAttrText(nodeItr itr, string attr);
	virtual void procIconTag(nodeItr itr, ficonvector& ficons) = 0;
	void getIconTags(string tagtype, ficonic::ficonvector& ficons);
public:
	HtmlTagAccessor();
	virtual ~HtmlTagAccessor();
	void pull(string url, string& htmlref);
};

#endif /* SRC_HTMLTAGACCESSOR_HPP_ */
