/*
 * RootIconsRetriever.hpp
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

#ifndef SRC_ROOTICONSRETRIEVER_HPP_
#define SRC_ROOTICONSRETRIEVER_HPP_

#include <map>
#include <string>
#include "ficon.hpp"
#include "IconsRetriever.hpp"

using namespace ficonic;
using std::string;

class RootIconsRetriever : virtual IconsRetriever {
private:
	void pullFavicon	(string url, ficonvector& ficons);
	void pullAppleicon	(string url, ficonvector& ficons);
public:
	RootIconsRetriever();
	virtual ~RootIconsRetriever();
	void pull(string url, ficonvector& ficons);
};

#endif /* SRC_ROOTICONSRETRIEVER_HPP_ */
