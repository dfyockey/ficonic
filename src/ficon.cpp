/*
 * ficon.cpp
 *
 *  Created on: Jun 22, 2023
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

#include "ficon.hpp"
using namespace ficonic;

ficon ficonfactory::make_ficon(string rel, Image image, Blob& blob) {
	size_t width  = image.columns();
	size_t height = image.rows();
	ficon f(
			rel,
			std::make_pair(image.format(), image.magick()),
			std::make_pair(width, height),
			blob
	);
	return f;
}

ficon ficonfactory::make_ficon(string rel, Image image) {
	Blob blob;
	image.write(&blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

ficon ficonfactory::make_ficon(string rel, Blob& blob) {
	Image image(blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

// Use to generate ficons of different types for images in a multiple frame image (e.g. ICO, GIF)
ficon ficonfactory::make_ficon(string rel, string type, Image image) {
	image.magick(type);
	return ficonfactory::make_ficon(rel, image);
}
