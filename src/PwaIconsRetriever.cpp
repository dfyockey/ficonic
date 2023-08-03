/*
 * PwaIconsRetriever.cpp
 *
 *  Created on: Aug 3, 2023
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

/*
 * Note:
 * PwaIconsRetriever applies to all W3C web application manifests,
 * not just to PWA manifests. However, "WamIconsRetriever" seemed
 * somehow confusing to me, and "ManifestIconsRetriever" was hard
 * to distinguish from "MetaIconsRetriever". So I decided to just
 * stick with "PwaIconsRetriever" as the name of the class. - DY
 */

#include "PwaIconsRetriever.hpp"

///// private ////////////////////////////////////////////////////////

void PwaIconsRetriever::procIconTag(nodeItr itr, ficonvector& ficons) {
	// TODO: Implement procIconTag method
}

///// public /////////////////////////////////////////////////////////

PwaIconsRetriever::PwaIconsRetriever() : HtmlTagAccessor() {
}

PwaIconsRetriever::~PwaIconsRetriever() {
}

void PwaIconsRetriever::pull(string url, ficonic::ficonvector& ficons) {
	// TODO: Implement pull method
}
