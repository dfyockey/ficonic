/*
 * RootIconsRetriever.cpp
 *
 *  Created on: Jun 16, 2023
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

#include "RootIconsRetriever.hpp"

#include "program_info.h"
#include <fstream>
#include <Magick++.h>
#include <iostream>

///// private ////////////////////////////////////////////////////////

void RootIconsRetriever::pullFavicon(string url, ficonvector& ficons) {
	pullIcon(url, "root favicon", ficons, "favicon.ico");
}

void RootIconsRetriever::pullAppleicon(string url, ficonvector& ficons) {
	pullIcon(url, "root apple-touch-icon", ficons, "apple-touch-icon.png");
}

///// public /////////////////////////////////////////////////////////

RootIconsRetriever::RootIconsRetriever() : IconsRetriever() {
}

void RootIconsRetriever::pull(string url, ficonvector& ficons) {
	pullFavicon	  (url, ficons);
	pullAppleicon (url, ficons);
}

RootIconsRetriever::~RootIconsRetriever() {
}

