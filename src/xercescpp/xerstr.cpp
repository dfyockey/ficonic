/*
 * xerstr.cpp
 *
 *  Created on: Aug 16, 2023
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

#include "xerstr.hpp"

///// private ////////////////////////////////////////////////////////

///// protected //////////////////////////////////////////////////////

xerstr::xerstr() {
}

void xerstr::setfromXMLCh(const XMLCh* txt) {
	c = XMLString::transcode(txt);
	cleanup = clean_c;
	s = string(c);
	x = const_cast<XMLCh*>(txt);
}

void xerstr::setfromString(string txt) {
	s = txt;
	x = XMLString::transcode(txt.c_str());
	cleanup = clean_x;
	c = const_cast<char*>(s.c_str());
}

///// public /////////////////////////////////////////////////////////

xerstr::~xerstr() {
	cleanup ? XMLString::release(&x) : XMLString::release(&c);
}

