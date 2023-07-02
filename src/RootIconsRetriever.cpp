/*
 * RootIconsRetriever.cpp
 *
 *  Created on: Jun 16, 2023
 *      Author: David Yockey
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

RootIconsRetriever::RootIconsRetriever() {
	// TODO Auto-generated constructor stub

}

void RootIconsRetriever::pull(string url, ficonvector& ficons) {
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, PROGNAME} };
	Curler curl(&httpHeaderFields);

	pullFavicon	  (url, ficons, curl);
	pullAppleicon (url, ficons, curl);
}

RootIconsRetriever::~RootIconsRetriever() {
	// TODO Auto-generated destructor stub
}

