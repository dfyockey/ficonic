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
#include "program_info.h"
#include <htmlcxx/html/ParserDom.h>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace htmlcxx;

///// private ////////////////////////////////////////////////////////

void LinkIconsRetriever::pullHTML(string url) {
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, PROGNAME} };
	Curler curl(&httpHeaderFields);
	curl.pull(url, html);
}

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

void LinkIconsRetriever::dumpLinkTags() {
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

	tree<HTML::Node>::iterator domItr = dom.begin();
	tree<HTML::Node>::iterator domEnd = dom.end();

	while (domItr != domEnd ) {

		if ( str_tolower( domItr->tagName().c_str() ) == "link") {
			std::cout << domItr->text() << "\n";
			// parse link tag!
		}

		++domItr;
	}
}

///// public /////////////////////////////////////////////////////////

LinkIconsRetriever::LinkIconsRetriever() {
	// TODO Auto-generated constructor stub
	pullHTML("https://www.wikipedia.org");
}

LinkIconsRetriever::~LinkIconsRetriever() {
	// TODO Auto-generated destructor stub
}

