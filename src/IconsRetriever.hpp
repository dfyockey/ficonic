/*
 * IconsRetriever.hpp
 *
 *  Created on: Jul 3, 2023
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

#ifndef SRC_ICONSRETRIEVER_HPP_
#define SRC_ICONSRETRIEVER_HPP_

#include "Curler.h"
#include "program_info.h"
#include "ficon.hpp"

using namespace ficonic;

// The `rel` arguments provided in the following class's methods should
// be from or have a meaning equivalent to `rel` attributes in HTML link tags.

class IconsRetriever : protected virtual Curler {
private:
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, PROGNAME} };
	bool	notSubStr	(string str, int pos, int count, string cmp );
	string	finishURL	(string url);
	void	pullImg		(string url, string rel, ficonvector& ficons);
	void	pullImg		(string url, string rel, ficonvector& ficons, string filename);

	void	saveLargerSize		(ficonvector& ficons, sizes& size);
	sizes	push_ico_img_ficons	(string ICOfile, string rel, ficonvector& ficons);
	void	push_ico_ficon		(ostringstream& ossICO, string rel, formats format, sizes size, ficonvector& ficons);
	void	pullICO				(string url, string rel, ficonvector& ficons, string filename);
protected:
	string	str_tolower			(string s);
	string	getExt				(string file);
	bool 	noHttpProtocol		(string url);
	string	clipLeadingSlash	(string url);
	void pullIcon (string url, string rel, ficonvector& ficons, string filename="");
public:
	IconsRetriever();
	virtual ~IconsRetriever();
	virtual void pull(string url, ficonvector& ficons) = 0;
};

#endif /* SRC_ICONSRETRIEVER_HPP_ */
