/*
 * ficon.cpp
 *
 *  Created on: Jun 22, 2023
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

#include "ficon.hpp"
using namespace ficonic;

///// private ////////////////////////////////////////////////////////

ficon ficonfactory::make_ficon(string rel, Image image, Blob& blob) {
	return ficonfactory::make_ficon(
									rel,
									std::make_pair(image.format(), image.magick()),
									std::make_pair(image.columns(), image.rows()),
									blob
						 );
}

///// public /////////////////////////////////////////////////////////

ficon ficonfactory::make_ficon(string rel, Image image) {
	Blob blob;
	image.write(&blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

ficon ficonfactory::make_ficon(string rel, Blob& blob) {
	Image image(blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

// Call directly only for multiple frame files (e.g. ICO format), which Magick::Image can't handle.
// Otherwise, call indirectly through the private ficonfactory::make_ficon method.
ficon ficonfactory::make_ficon(string rel, formats format, sizes size, Blob& blob) {
	ficon f( rel, format, size,	blob );
	return f;
}

// Call to generate ficons of different types (e.g. BMP, PNG) for images in a multiple frame image (e.g. ICO).
ficon ficonfactory::make_ficon(string rel, string type, Image image) {
	image.magick(type);
	return ficonfactory::make_ficon(rel, image);
}
