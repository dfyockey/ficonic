/*
 * MetaIconsRetriever.cpp
 *
 *  Created on: Jul 24, 2023
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

#include "MetaIconsRetriever.hpp"
#include "xercescpp/xerstr.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using std::cerr;
using std::endl;

///// private ////////////////////////////////////////////////////////

string MetaIconsRetriever::getFilenameFromUrl (string url, size_t filename_start) {
	return url.substr( filename_start, url.length()-1 );
}

void MetaIconsRetriever::procTileChildNodes (DOMNodeList* childNodes, ficonvector& ficons) {
	if ( childNodes ) {
		for (int c = childNodes->getLength(), i = 0; i < c; i++) {
			DOMElement* childElement = static_cast<DOMElement*>(childNodes->item(i));

			if ( childElement && nestedtiles.find( xerstr(childElement->getTagName()).s_str() ) != nestedtiles.end() ) {
				xerstr imgfile( childElement->getAttribute(xerstr("src")) );
				string imgurl = pulledsite_url + clipLeadingSlash(imgfile);
				pullIcon(imgurl, "msapplication", ficons);
			}
		}
	}
}

void MetaIconsRetriever::procTilesXMLfile (string tilesxmlfile, ficonvector& ficons) {
	parser.parse(tilesxmlfile);
	DOMDocument* doc = parser.getDocument();
	DOMNodeList* tiletags = doc->getElementsByTagName(xerstr("tile"));

	if (tiletags && tiletags->getLength() > 0) {

		DOMNodeList* childNodes = tiletags->item(0)->getChildNodes();

		procTileChildNodes (childNodes, ficons);
	}
}

void MetaIconsRetriever::procTilesXML (string tilesxmlurl, ficonvector& ficons) {
	// Get IE 11 Tiles for Win 8.1 Start Screen from xml file
	try {
		string filename;
		size_t filename_start = tilesxmlurl.find_last_of('/') + 1;
		if (noHttpProtocol(tilesxmlurl)) {
			if (filename_start == string::npos) {
				filename = tilesxmlurl;
			} else {
				filename = getFilenameFromUrl(tilesxmlurl, filename_start);
			}

			tilesxmlurl = pulledsite_url + clipLeadingSlash(tilesxmlurl);
		} else {
			filename = getFilenameFromUrl(tilesxmlurl, filename_start);
		}

		string tilesxmlfile = (fs::temp_directory_path() / filename);

		ofstream ofs(tilesxmlfile, std::ios::trunc);

		string tilesxml;
		Curler::pull(tilesxmlurl, tilesxml);
		ofs << tilesxml;

		// MUST close file before passing it on for further processing
		// so that it can be opened later by the Xerces parser for reading!
		// Otherwise — AARGGH! :) — an exception will be thrown!
		ofs.close();

		procTilesXMLfile(tilesxmlfile, ficons);

	} catch (XMLException& e) {
		string msg = xerstr(e.getMessage());
		cerr << tilesxmlurl << " : XMLException : " << msg << "\n" \
				  << "(skipping file)\n" << endl;
	} catch (SAXParseException &e) {
		string msg = xerstr(e.getMessage());
		cerr << tilesxmlurl << " : SAXParseException : " << msg << "\n" \
				  << "(skipping file)\n" << endl;
	} catch (std::exception &e) {
		cerr << tilesxmlurl << " : std::exception : " << e.what() << "\n" \
				  << "(skipping file)\n" << endl;
	}
}

void MetaIconsRetriever::procIconTag(nodeItr itr, ficonvector& ficons) {
	itr->parseAttributes();
	string name = getAttrText(itr, "name");

	if (names.find(name) != names.end()) {
		string url = getAttrText(itr, "content");

		if( noHttpProtocol(url) ) {
			// TODO: Add something here to remove all but root
			//       from pulledsite_url before the following concat
			url = pulledsite_url + clipLeadingSlash(url);
		}

		if (getExt(url) != ".xml") {
			pullIcon(url, name, ficons);
		} else {
			procTilesXML(url, ficons);
		}
	}
}

///// public /////////////////////////////////////////////////////////

MetaIconsRetriever::MetaIconsRetriever() : HtmlTagAccessor() {
}

MetaIconsRetriever::~MetaIconsRetriever() {
}

void MetaIconsRetriever::pull(string url, ficonic::ficonvector& ficons) {
	HtmlTagAccessor::pull(url, html);
	pulledsite_url = effective_url();
	getIconTags("meta", ficons);
}
