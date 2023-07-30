/*
 * ficon.hpp
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

#ifndef SRC_FICON_HPP_
#define SRC_FICON_HPP_

#include <map>
#include <string>
#include <Magick++.h>

using namespace Magick;
using std::string;

namespace ficonic {
	typedef std::pair<string, string> formats;
	typedef std::pair<size_t, size_t> sizes;

	struct ficon {
		ficon(string rel, formats format, sizes size, Blob data)
			: rel(rel), type(format.first), ext(format.second), width(size.first), height(size.second), data(data) {};
		string	rel;	// from HTML link or ficonic-defined for root directory icons
		string	type;	// long form icon format	// FIXME: Change to type from HTML link
		string	ext;	// short form icon format (i.e. extension)
		size_t	width;	// icon width
		size_t	height; // icon height
		Blob	data;	// icon data
	};

	typedef std::vector<struct ficon> ficonvector;

	class ficonfactory {
	private:
		static ficon make_ficon(string rel, Image image, Blob& blob);
	public:
		static ficon make_ficon(string rel, Image image);
		static ficon make_ficon(string rel, Blob& blob);
		static ficon make_ficon(string rel, formats format, sizes size, Blob& blob);	// 1,2
		static ficon make_ficon(string rel, string type, Image image);					// 3
	};
}

// 1 - Call directly only for multiple frame files (e.g. ICO format), which Magick::Image can't handle.
// 2 - Otherwise, call indirectly through the private ficonfactory::make_ficon method.
// 3 - Call to generate ficons of different types (e.g. BMP, PNG) for images in a multiple frame file (e.g. ICO).

#endif /* SRC_FICON_HPP_ */
