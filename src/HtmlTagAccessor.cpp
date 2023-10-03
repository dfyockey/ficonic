/*
 * HtmlTagAccessor.cpp
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

#include "HtmlTagAccessor.hpp"

///// private ////////////////////////////////////////////////////////

///// protected //////////////////////////////////////////////////////

string HtmlTagAccessor::getAttrText(nodeItr itr, string attr) {
	return itr->attribute(attr).second;
}

void HtmlTagAccessor::getIconTags(string tagtype, ficonic::ficonvector& ficons) {
	HTML::ParserDom parser;

	tree<HTML::Node> dom = parser.parseTree(html);

	nodeItr domItr = dom.begin();
	nodeItr domEnd = dom.end();

	while (domItr != domEnd ) {

		if ( str_tolower( domItr->tagName().c_str() ) == tagtype  ) {
			procIconTag(domItr, ficons);
		}
		++domItr;
	}
}

///// public /////////////////////////////////////////////////////////

HtmlTagAccessor::HtmlTagAccessor() : IconsRetriever() {
}

HtmlTagAccessor::~HtmlTagAccessor() {
}

void HtmlTagAccessor::pull(string url, string& htmlref) {
	if (url != prev_url || html.empty()) {
		Curler::pull(url, html);
		prev_url = url;
	}
	htmlref = html;
}

