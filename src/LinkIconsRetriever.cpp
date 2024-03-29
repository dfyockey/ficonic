/*
 * LinkIconsRetriever.cpp
 *
 *  Created on: Jun 27, 2023
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

#include "LinkIconsRetriever.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::flush;

///// private ////////////////////////////////////////////////////////

void LinkIconsRetriever::procIconTag(nodeItr itr, ficonvector& ficons) {
	itr->parseAttributes();
	string rel = getAttrText(itr, "rel");

	if (rels.find(rel) != rels.end()) {
		string url = getAttrText(itr, "href");

		if( noHttpProtocol(url) ) {
			url = pulledsite_url + clipLeadingSlash(url);
		}

		pullIcon(url, rel, ficons);
	}
}

///// public /////////////////////////////////////////////////////////

LinkIconsRetriever::LinkIconsRetriever() : HtmlTagAccessor() {
}

void LinkIconsRetriever::pull(string url, ficonic::ficonvector& ficons) {
	HtmlTagAccessor::pull(url, html);

/**/cout << "Effective URL = " << Curler::effective_url() << endl;
	pulledsite_url = Curler::effective_url();

	getIconTags("link", ficons);
}

LinkIconsRetriever::~LinkIconsRetriever() {
}

