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

void RootIconsRetriever::pullFavicon(string url, ficonvector& ficons, Curler& curl) {
	try {
		ofstream ofFavicon("/tmp/favicon.ico", std::ios::binary);
		curl.pull(url + "favicon.ico", ofFavicon);

		///// Pull the favicon.ico file, spliting it into its contained images in the process.
		std::vector<Image> imgvector;
		readImages( &imgvector, "/tmp/favicon.ico");

		///// Store the split images as ficons in both BMP and PNG formats
		for (auto& image : imgvector) {
#define     add_ficon(T)     ficons.push_back( ficonfactory::make_ficon("favicon", T, image) )
			add_ficon("BMP");
			add_ficon("PNG");
		}
	} catch (Exception &e) {
		std::cout << "favicon parsing error : " << e.what() << std::endl;
		// assume no favicon.ico file was found and ignore exception
	}
}

void RootIconsRetriever::pullAppleicon(string url, ficonvector& ficons, Curler& curl) {
	try {
		ostringstream ossLinkIcon;
		curl.pull( url + "apple-touch-icon.png", ossLinkIcon );
		Blob blob(ossLinkIcon.str().data(), ossLinkIcon.str().length());
		ficons.push_back( ficonfactory::make_ficon("appleicon", blob) );
	} catch (Exception &e) {
		std::cout << "appleicon parsing error : " << e.what() << std::endl;
		// assume no apple-touch-icon.png was found and ignore exception
	}
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

