/*
 * IconsRetriever.cpp
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

#include "IconsRetriever.hpp"
#include <iostream>
#include <string>

///// protected //////////////////////////////////////////////////////

// The str_tolower method is from an example provided in the description of
// std::tolower at https://en.cppreference.com/w/cpp/string/byte/tolower,
// licensed under Creative Commons Attribution-Sharealike 3.0 Unported
// License (CC-BY-SA) and by the GNU Free Documentation License (GFDL)
// (unversioned, with no invariant sections, front-cover texts, or back-cover
// texts)
string IconsRetriever::str_tolower(string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

void IconsRetriever::pullImg(string url, string filename, string rel, ficonic::ficonvector& ficons) {
	try {
		ostringstream ossLinkIcon;
		curl.pull( url + filename, ossLinkIcon );
		Blob blob(ossLinkIcon.str().data(), ossLinkIcon.str().length());
		ficons.push_back( ficonfactory::make_ficon(rel, blob) );
	} catch (Exception &e) {
		std::cout << filename << " parsing error : " << e.what() << "\n" \
				<< "(Assuming no valid or adaptable " << filename \
				<< " icon file was found; ignoring the error)\n" << std::endl;
	}
}

void IconsRetriever::pullICO(string url, string filename, string rel, ficonic::ficonvector& ficons) {
	try {
		// Saving an ICO format icon to a file is needed here because Magick::readImages
		// apparently can't handle reading an ICO format file from a Magick::Blob.
		ofstream ofICO("/tmp/" + filename, std::ios::binary);
		curl.pull(url + filename, ofICO);

		///// Pull the favicon.ico file, spliting it into its contained images in the process.
		std::vector<Image> imgvector;
		readImages( &imgvector, "/tmp/" + filename);

		///// Store the split images as ficons in both BMP and PNG formats
		for (auto& image : imgvector) {
			for (string filetype : {"BMP", "PNG"}) {
				ficons.push_back( ficonfactory::make_ficon(rel, filetype, image) );
			}
		}
	} catch (Exception &e) {
		// Try pulling favicon.ico as a single image rather than a proper ICO formatted file
		pullImg(url, filename, rel, ficons);
	}
}

void IconsRetriever::pullIcon(string url, string filename, string rel, ficonic::ficonvector& ficons) {
	string ext = filename.substr(filename.length()-4,4);

	if ( str_tolower(ext) == ".ico" ) {
		pullICO(url, filename, rel, ficons);
	} else {
		pullImg(url, filename, rel, ficons);
	}
}

///// public /////////////////////////////////////////////////////////

IconsRetriever::IconsRetriever() : curl(&httpHeaderFields) {
	// TODO Auto-generated constructor stub

}

IconsRetriever::~IconsRetriever() {
	// TODO Auto-generated destructor stub
}

