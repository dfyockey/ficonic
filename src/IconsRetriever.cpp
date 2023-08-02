/*
 * IconsRetriever.cpp
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

#include "IconsRetriever.hpp"
#include <iostream>
#include <string>
#include <filesystem>

using std::vector;
using namespace std::filesystem;

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
	// FIXME: file.substr should get the string from last '.' to end of file
	string ext = file.substr(file.length()-4,4);
	return str_tolower(ext);
}

void IconsRetriever::pullImg(string url, string rel, ficonvector& ficons) {
	try {
		url = finishURL(url);
/**/	std::cout << "Pulling Img " << url << std::endl;
		ostringstream ossLinkIcon;
		Curler::pull( url , ossLinkIcon );
		Blob blob(ossLinkIcon.str().data(), ossLinkIcon.str().length());
		ficons.push_back( ficonfactory::make_ficon(rel, blob) );
	} catch (Exception &e) {
		std::cerr << url << " parsing error : " << e.what() << "\n" \
				  << "(Assuming no valid icon file found; skipping file)\n" << std::endl;
	}
}

void IconsRetriever::pullImg(string url, string rel, ficonvector& ficons, string filename) {
	pullImg(url + filename, rel, ficons);
}

void IconsRetriever::saveLargerSize(ficonvector& ficons, sizes& size) {
	if (!ficons.empty()) {
		ficon& f = ficons.back();
		if (f.ext == "BMP" && std::make_pair(f.width,f.height) > size) {
			size = {f.width,f.height};
		}
	}
}

sizes IconsRetriever::push_ico_img_ficons(string ICOfile, string rel, ficonvector& ficons) {

	///// Pull the favicon.ico file, spliting it into its contained images in the process.
	vector<Image> imgvector;
	readImages( &imgvector, ICOfile );

	sizes size = {0,0};

	///// Store the split images as ficons in both BMP and PNG formats
	for (auto& image : imgvector) {
		for (string filetype : {"BMP", "PNG"}) {
			ficons.push_back( ficonfactory::make_ficon(rel, filetype, image) );
			saveLargerSize(ficons, size);
		}
	}

	return size;
}

void IconsRetriever::push_ico_ficon(ostringstream& ossICO, string rel, formats format, sizes size, ficonvector& ficons) {
	///// Store the ICO file as a ficon
	void* icodata = static_cast<void*>(ossICO.str().data());
	Blob blob( icodata, ossICO.str().length() );
	ficons.push_back( ficonfactory::make_ficon(rel, format, size, blob) );
}

string save_ico_to_sys_temp(string ico_filename, ostringstream& ossICO) {
	string		ico_file	( (temp_directory_path() / ico_filename).string() );
	string		ico_str		( ossICO.str() );
	ofstream	ofICO		( ico_file, std::ios::binary );
	ofICO.write( ico_str.c_str(), ico_str.size() );
	return ico_file;
}

void IconsRetriever::pullICO(string url, string rel, ficonvector& ficons, string ico_filename) {
	try {
		// Pull to an ostringstream rather than a filestream to facilitate later saving to a ficon's blob
		ostringstream ossICO;
		Curler::pull( url + ico_filename, ossICO );

		// Saving an ICO format icon to a file is needed here because Magick::readImages in
		// push_ico_img_ficons can't handle reading an ICO format file from a Magick::Blob.
		string ico_file = save_ico_to_sys_temp(ico_filename, ossICO);
		sizes size		= push_ico_img_ficons( ico_file, rel, ficons );

		formats format = {"Microsoft Windows Icon","ICO"};
		push_ico_ficon( ossICO, rel, format, size, ficons );

	} catch (Exception &e) {
		// Try pulling favicon.ico as a single image rather than a proper ICO formatted file
		std::cerr << (url+ico_filename) << " not recognized as having an ICO format.\n" \
				  << "Attempting to handle as a normal image file." << std::endl;
		pullImg(finishURL(url + ico_filename), rel, ficons);
	}
}

///// public /////////////////////////////////////////////////////////

IconsRetriever::IconsRetriever() : Curler(&httpHeaderFields) {
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
