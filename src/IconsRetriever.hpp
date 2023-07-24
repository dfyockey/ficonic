/*
 * IconsRetriever.hpp
 *
 *  Created on: Jul 3, 2023
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

#ifndef SRC_ICONSRETRIEVER_HPP_
#define SRC_ICONSRETRIEVER_HPP_

#include "Curler.h"
#include "program_info.h"
#include "ficon.hpp"

using namespace ficonic;

// The `rel` arguments provided in the following class's methods should
// be from or have a meaning equivalent to `rel` attributes in HTML link tags.

class IconsRetriever {
private:
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, PROGNAME} };
	bool	notSubStr	(string str, int pos, int count, string cmp );
	string	finishURL	(string url);
	string	getExt		(string file);
	void	pullImg		(string url, string rel, ficonvector& ficons);
	void	pullImg		(string url, string rel, ficonvector& ficons, string filename);

	void	saveLargerSize		(ficonvector& ficons, sizes& size);
	sizes	push_ico_img_ficons	(string ICOfile, string rel, ficonvector& ficons);
	void	push_ico_ficon		(ostringstream& ossICO, string rel, formats format, sizes size, ficonvector& ficons);
	void	pullICO				(string url, string rel, ficonvector& ficons, string filename);
protected:
	Curler curl;
	string	str_tolower			(string s);
	bool 	noHttpProtocol		(string url);
	string	clipLeadingSlash	(string url);
public:
	IconsRetriever();
	virtual ~IconsRetriever();
	void pullIcon (string url, string rel, ficonvector& ficons, string filename="");
	virtual void pull(string url, ficonvector& ficons) = 0;
};

#endif /* SRC_ICONSRETRIEVER_HPP_ */
