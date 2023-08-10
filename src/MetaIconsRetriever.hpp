/*
 * MetaIconsRetriever.hpp
 *
 *  Created on: Jul 24, 2023
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

#ifndef SRC_METAICONSRETRIEVER_HPP_
#define SRC_METAICONSRETRIEVER_HPP_

#include "IconsRetriever.hpp"
#include "HtmlTagAccessor.hpp"

class MetaIconsRetriever : virtual private HtmlTagAccessor {
private:
	string html;

	std::set<string> names = {
			"msapplication-TileImage",
			"msapplication-square70x70logo",
			"msapplication-square150x150logo",
			"msapplication-wide310x150logo",
			"msapplication-square310x310logo",
			"msapplication-config"
	};

	string pulledsite_url;	// may differ from url used in Curler pull call if 3xx redirection was performed

	void procIconTag(nodeItr itr, ficonvector& ficons);

public:
	MetaIconsRetriever();
	virtual ~MetaIconsRetriever();
	void pull(string url, ficonvector& ficons);
};

#endif /* SRC_METAICONSRETRIEVER_HPP_ */
