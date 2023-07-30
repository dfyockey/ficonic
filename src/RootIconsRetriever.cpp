/*
 * RootIconsRetriever.cpp
 *
 *  Created on: Jun 16, 2023
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

