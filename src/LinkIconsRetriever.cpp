/*
 * LinkIconsRetriever.cpp
 *
 *  Created on: Jun 27, 2023
 *      Author: David Yockey
 *
 * MIT License
 *
 * Copyright © 2023 David Yockey
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "LinkIconsRetriever.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::flush;

///// private ////////////////////////////////////////////////////////

// The str_tolower method is from an example provided in the description of
// std::tolower at https://en.cppreference.com/w/cpp/string/byte/tolower,
// licensed under Creative Commons Attribution-Sharealike 3.0 Unported
// License (CC-BY-SA) and by the GNU Free Documentation License (GFDL)
// (unversioned, with no invariant sections, front-cover texts, or back-cover
// texts)

//bool LinkIconsRetriever::notSubStr(string str, int pos, int count, string cmp) {
//	return !(str_tolower(str.substr(pos, count)) == cmp);
//}
//
//string LinkIconsRetriever::finishURL(string url) {
//	if ( notSubStr(url,0,8,"https://") && notSubStr(url,0,7,"http://") ) {
//		url = (url.front() == '/') ? url.substr(1,url.length()-1) : url;
//		url = siteurl + url;
//	}
//	return url;
//}

string LinkIconsRetriever::getAttrText(nodeItr itr, string attr) {
	return itr->attribute(attr).second;
}

void LinkIconsRetriever::procLinkIconTag(nodeItr itr, ficonvector& ficons) {
	itr->parseAttributes();
	std::cout << "procLinkIconTag : " << getAttrText(itr, "href") << std::endl;
	string rel = getAttrText(itr, "rel");
	if (rels.find(rel) != rels.end()) {
		string url = getAttrText(itr, "href");
		if( noHttpProtocol(url) ) {
			url = pulledsite_url + clipLeadingSlash(url);
		}
		std::cout << "procLinkIconTag url : " << url << std::endl;
		pullIcon(url, rel, ficons);
	}
}

void LinkIconsRetriever::getLinkIconTags(ficonvector& ficons) {
	HTML::ParserDom parser;

/**/cout << "start html parsing..." << flush;

	tree<HTML::Node> dom = parser.parseTree(html);

/**/cout << "end html parsing" << endl;

	nodeItr domItr = dom.begin();
	nodeItr domEnd = dom.end();



	while (domItr != domEnd ) {



		if ( str_tolower( domItr->tagName().c_str() ) == "link"  ) {
			procLinkIconTag(domItr, ficons);
		}
		++domItr;
	}
}

///// public /////////////////////////////////////////////////////////

LinkIconsRetriever::LinkIconsRetriever() : IconsRetriever() {
}

void LinkIconsRetriever::pull(string url, ficonic::ficonvector& ficons) {
/**/cout << "start pull..." << flush;

	siteurl = url;
	curl.pull(siteurl, html);

/**/cout << "end pull" << endl;
/**/cout << "Effective URL = " << curl.effective_url() << endl;
	pulledsite_url = curl.effective_url();

	getLinkIconTags(ficons);
}

LinkIconsRetriever::~LinkIconsRetriever() {
	// TODO Auto-generated destructor stub
}

