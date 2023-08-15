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
#include "xercescpp/InitXerces.hpp"
#include "xercescpp/XmlStrTypes.hpp"
#include <xercesc/util/XMLString.hpp>
#include <iostream>

///// private ////////////////////////////////////////////////////////

void MetaIconsRetriever::procTilesXML (string url, ficonvector& ficons) {
	// TODO: Get IE 11 Tiles for Win 8.1 Start Screen from xml file
			try {
				InitXerces xercescpp;

				// Get the .xml file
//				string tilesxml;
//				Curler::pull(url, tilesxml);

				// TODO: Parse the .xml file into a DOM
				domParser.parse(url);

				// TODO: Retrieve icons referred to in the DOM

			} catch (XMLException& e) {
				string msg = XmlStr(e.getMessage());
				std::cerr << url << " processing error : " << msg << "\n" \
						  << "(skipping file)\n" << std::endl;
			}
}

void MetaIconsRetriever::procIconTag(nodeItr itr, ficonvector& ficons) {
	itr->parseAttributes();
	string name = getAttrText(itr, "name");

	if (names.find(name) != names.end()) {
		string url = getAttrText(itr, "content");

		if( noHttpProtocol(url) ) {
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
	pulledsite_url = Curler::effective_url();
	getIconTags("meta", ficons);
}

