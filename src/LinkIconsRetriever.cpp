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
#include <algorithm>
#include <iostream>
#include <Magick++.h>
#include <filesystem>

using namespace std;
using namespace htmlcxx;

///// private ////////////////////////////////////////////////////////

// The str_tolower method is from an example provided in the description of
// std::tolower at https://en.cppreference.com/w/cpp/string/byte/tolower,
// licensed under Creative Commons Attribution-Sharealike 3.0 Unported
// License (CC-BY-SA) and by the GNU Free Documentation License (GFDL)
// (unversioned, with no invariant sections, front-cover texts, or back-cover
// texts)
string LinkIconsRetriever::str_tolower(string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

bool LinkIconsRetriever::notSubStr(string str, int pos, int count, string cmp) {
	return str_tolower(str.substr(pos, count)).compare(cmp);
}

string LinkIconsRetriever::finishURL(string url) {
	if ( notSubStr(url,0,8,"https://") && notSubStr(url,0,7,"http://") ) {
		url = (url.front() == '/') ? url.substr(1,url.length()-1) : url;
		url = siteurl + url;
	}
	cout << url << endl;
	return url;
}

Blob& LinkIconsRetriever::pullImage(string url, Blob& blob) {
	ostringstream ossLinkIcon;
	curl.pull( finishURL(url), ossLinkIcon );

	blob.update(ossLinkIcon.str().data(), ossLinkIcon.str().length());

	return blob;
}

string LinkIconsRetriever::getAttrText(nodeItr itr, string attr) {
	return itr->attribute(attr).second;
}

void LinkIconsRetriever::procLinkIconTag(nodeItr itr, ficonvector& ficons) {
	itr->parseAttributes();
	string reltext = getAttrText(itr, "rel");
	if (rels.find(reltext) != rels.end()) {

		string hreftext = getAttrText(itr, "href");										// Temporary Test Code
		cout << hreftext << endl;														// ( to block .ico file processing
		cout << hreftext.substr(hreftext.length()-4,4) << endl;							// ( until RootIconsReciever code
		if (str_tolower(hreftext.substr(hreftext.length()-4,4)).compare(".ico")) {		// ( to handle it can be accessed

			Blob blob;
			ficon f = ficonfactory::make_ficon( reltext, pullImage( getAttrText(itr, "href"), blob ) );
			ficons.push_back(f);

		}																				// Temporary Test Code
	}
}

void LinkIconsRetriever::getLinkIconTags(ficonvector& ficons) {
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

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
	siteurl = url;
	curl.pull(siteurl, html);

	getLinkIconTags(ficons);
}

LinkIconsRetriever::~LinkIconsRetriever() {
	// TODO Auto-generated destructor stub
}

