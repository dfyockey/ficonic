/*
 * PwaIconsRetriever.hpp
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

#ifndef SRC_PWAICONSRETRIEVER_HPP_
#define SRC_PWAICONSRETRIEVER_HPP_

#include <string>
#include "ficon.hpp"
#include "HtmlTagAccessor.hpp"
#include "Parser.hpp"

class PwaIconsRetriever : private virtual HtmlTagAccessor {
private:
	string html;
	string pulledsite_url;	// may differ from url used in Curler pull call if 3xx redirection was performed

	/*
	 * If other `rel` values are later found to be used, it is recommended to reimplement the following
	 * as `std::set<std::string> rels` in the same manner as in other IconsRetriever derivatives and to
	 * modify procIconTag accordingly.
	 */
	const string rel = "manifest";

	Parser parser;

	void pullManifestIcons	(string manifest, string rel, ficonvector& ficons);
	void procIconTag		(nodeItr itr, ficonvector& ficons);

public:
	PwaIconsRetriever();
	virtual ~PwaIconsRetriever();
	void pull(string url, ficonvector& ficons);
};

#endif /* SRC_PWAICONSRETRIEVER_HPP_ */
