/*
 * LinkIconsRetriever.h
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

#ifndef SRC_LINKICONSRETRIEVER_HPP_
#define SRC_LINKICONSRETRIEVER_HPP_

#include <htmlcxx/html/ParserDom.h>
#include "IconsRetriever.hpp"
#include "HtmlTagAccessor.hpp"

using namespace htmlcxx;

class LinkIconsRetriever : virtual IconsRetriever, HtmlTagAccessor {
private:
	typedef tree<HTML::Node>::iterator nodeItr;

	string html;

	std::set<string> rels = {
			"icon",																// HTML5 Standard rel value
			"shortcut icon",													// HTML5 Standard rel value acceptable for historical reasons
			"mask-icon", "apple-touch-icon", "apple-touch-icon-precomposed",	// Apple-related rel values
			"alternate icon"													// From https://github.com, rel value referring to a PNG alternate to an SVG
	};

	string siteurl;
	string pulledsite_url;	// may differ from url used in Curler pull call if 3xx redirection was performed

	string	getAttrText		(nodeItr itr, string attr);
	void	procLinkIconTag	(nodeItr itr, ficonvector& ficons);
	void	getLinkIconTags	(ficonvector& ficons);

public:
	LinkIconsRetriever();
	virtual ~LinkIconsRetriever();
	void pull(string url, ficonvector& ficons);
};

#endif /* SRC_LINKICONSRETRIEVER_HPP_ */
