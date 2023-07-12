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
#include <filesystem>

///// private ////////////////////////////////////////////////////////

bool IconsRetriever::notSubStr(string str, int pos, int count, string cmp) {
	return !(str_tolower(str.substr(pos, count)) == cmp);
}

bool IconsRetriever::noHttpProtocol(string url) {
	return ( notSubStr(url,0,8,"https://") && notSubStr(url,0,7,"http://") );
}

string IconsRetriever::clipLeadingSlash (string url) {
	return ( (url.front() == '/') ? url.substr(1,url.length()-1) : url );
}

string IconsRetriever::finishURL(string url) {
	if( noHttpProtocol(url) ) {
		url = clipLeadingSlash(url);
	}

/**/std::cout << "finished URL = " << url << std::endl;

	return url;
}

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

string IconsRetriever::getExt(string file) {
	string ext = file.substr(file.length()-4,4);
	return str_tolower(ext);
}

void IconsRetriever::pullImg(string url, string rel, ficonic::ficonvector& ficons) {
	try {
		url = finishURL(url);
/**/	std::cout << "Pulling Img " << url << std::endl;
		ostringstream ossLinkIcon;
		curl.pull( url , ossLinkIcon );
		Blob blob(ossLinkIcon.str().data(), ossLinkIcon.str().length());
		ficons.push_back( ficonfactory::make_ficon(rel, blob) );
	} catch (Exception &e) {
		std::cout << url << " parsing error : " << e.what() << "\n" \
				<< "(Assuming no valid or adaptable icon file was found;" \
				<< " ignoring the error)\n" << std::endl;
	}
}

void IconsRetriever::pullImg(string url, string rel, ficonic::ficonvector& ficons, string filename) {
	pullImg(url + filename, rel, ficons);
}

void IconsRetriever::pullICO(string url, string rel, ficonic::ficonvector& ficons, string filename) {
	try {
		std::filesystem::path ICOfile = std::filesystem::temp_directory_path() / filename;

		// Saving an ICO format icon to a file is needed here because Magick::readImages
		// apparently can't handle reading an ICO format file from a Magick::Blob.
		ofstream ofICO( ICOfile.string(), std::ios::binary );
		curl.pull( url + filename, ofICO );

		///// Pull the favicon.ico file, spliting it into its contained images in the process.
		std::vector<Image> imgvector;
		readImages( &imgvector, ICOfile.string() );

		///// Store the split images as ficons in both BMP and PNG formats
		for (auto& image : imgvector) {
			for (string filetype : {"BMP", "PNG"}) {
				ficons.push_back( ficonfactory::make_ficon(rel, filetype, image) );
			}
		}
	} catch (Exception &e) {
		// Try pulling favicon.ico as a single image rather than a proper ICO formatted file
/**/	std::cout << "pullICO : " << url << " : " << filename << std::endl;

		pullImg(finishURL(url + filename), rel, ficons);
	}
}

///// public /////////////////////////////////////////////////////////

IconsRetriever::IconsRetriever() : curl(&httpHeaderFields) {
}

IconsRetriever::~IconsRetriever() {
}

void IconsRetriever::pullIcon (string url, string rel, ficonvector& ficons, string filename/*=""*/) {
	string file = ( filename.length()>4 ) ? filename : url;

	if ( getExt(file) == ".ico" ) {
		// Split url into filename and url if needed
		if ( filename.empty() ) {
			size_t filename_start	= url.find_last_of('/') + 1;
			filename				= url.substr( filename_start, url.length()-1 );	// e.g. `favicon.ico`
			url						= url.substr( 0, filename_start );				// e.g. `https://curl.se/`
		}
		pullICO( url, rel, ficons, filename );
	} else {
		pullImg( url, rel, ficons, filename );
	}
}
