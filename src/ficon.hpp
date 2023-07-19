/*
 * ficon.hpp
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
