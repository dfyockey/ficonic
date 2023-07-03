/*
 * RootIconsRetriever.cpp
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

#include "RootIconsRetriever.hpp"

#include "program_info.h"
#include <fstream>
#include <Magick++.h>
#include <iostream>

///// private ////////////////////////////////////////////////////////

void RootIconsRetriever::pullIcon(string url, string filename, ficonvector& ficons, Curler& curl) {
	try {
		ostringstream ossLinkIcon;
		curl.pull( url + filename, ossLinkIcon );
		Blob blob(ossLinkIcon.str().data(), ossLinkIcon.str().length());
		ficons.push_back( ficonfactory::make_ficon(filename, blob) );
	} catch (Exception &e) {
		std::cout << filename << " parsing error : " << e.what() << "\n" \
				<< "(Assuming no valid or adaptable " << filename << " icon file was found; ignoring the error)\n" << std::endl;
	}
}

void RootIconsRetriever::pullFavicon(string url, ficonvector& ficons, Curler& curl) {
	try {
		// Saving favicon.ico to a file is needed here because Magick::readImages
		// apparently can't handle reading an ICO format file from a Magick::Blob.
		ofstream ofFavicon("/tmp/favicon.ico", std::ios::binary);
		curl.pull(url + "favicon.ico", ofFavicon);

		///// Pull the favicon.ico file, spliting it into its contained images in the process.
		std::vector<Image> imgvector;
		readImages( &imgvector, "/tmp/favicon.ico");

		///// Store the split images as ficons in both BMP and PNG formats
		for (auto& image : imgvector) {
			for (string filetype : {"BMP", "PNG"}) {
				ficons.push_back( ficonfactory::make_ficon("favicon", filetype, image) );
			}
		}
	} catch (Exception &e) {
		// Try pulling favicon.ico as a single image rather than a proper ICO formatted file
		pullIcon(url, "favicon.ico", ficons, curl);
	}
}

void RootIconsRetriever::pullAppleicon(string url, ficonvector& ficons, Curler& curl) {
	pullIcon(url, "apple-touch-icon.png", ficons, curl);
}

///// public /////////////////////////////////////////////////////////

RootIconsRetriever::RootIconsRetriever() : IconsRetriever() {
	// TODO Auto-generated constructor stub

}

void RootIconsRetriever::pull(string url, ficonvector& ficons) {
	pullFavicon	  (url, ficons, curl);
	pullAppleicon (url, ficons, curl);
}

RootIconsRetriever::~RootIconsRetriever() {
	// TODO Auto-generated destructor stub
}

