/*
 * RootIconsRetriever.cpp
 *
 *  Created on: Jun 16, 2023
 *      Author: David Yockey
 */

#include "RootIconsRetriever.hpp"

#include "Curler.h"
#include "program_info.h"
#include <fstream>
#include <Magick++.h>
#include <iostream>

///// private ////////////////////////////////////////////////////////


///// public /////////////////////////////////////////////////////////

RootIconsRetriever::RootIconsRetriever() {
	// TODO Auto-generated constructor stub

}

void RootIconsRetriever::pull(string url, ficonvector& ficons) {

	try {
		fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, PROGNAME} };
		Curler curl(&httpHeaderFields);
		ofstream ofFavicon("/tmp/favicon.ico", std::ios::binary);
		curl.pull(url + "favicon.ico", ofFavicon);

		///// Pull the favicon.ico file, spliting it into its contained images in the process.
		std::vector<Image> imgvector;
		readImages( &imgvector, "/tmp/favicon.ico");

		///// Store the split images as ficons in both BMP and PNG formats
		for (auto& image : imgvector) {
			ficons.push_back( make_ficon("favicon", "BMP", image) );
			ficons.push_back( make_ficon("favicon", "PNG", image) );
		}
	} catch (Exception &e) {
		std::cout << "favicon parsing error : " << e.what() << std::endl;
		// assume no favicon.ico file was found and ignore exception
	}

	try {
		Image image(url + "apple-touch-icon.png");
		ficons.push_back( make_ficon("appleicon", image.magick(), image) );
	} catch (Exception &e) {
		std::cout << "appleicon parsing error : " << e.what() << std::endl;
		// assume no apple-touch-icon.png was found and ignore exception
	}
}

RootIconsRetriever::~RootIconsRetriever() {
	// TODO Auto-generated destructor stub
}

