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
//#include "xercescpp/XmlStrTypes.hpp"
#include "xercescpp/xerstr.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

///// private ////////////////////////////////////////////////////////

//string MetaIconsRetriever::getRootFromUrl (string url) {
//	string root = url;
//
//	string::size_type lastSlash   = url.find_last_of('/');
//
//	string::size_type httpSlashes = url.find("://");
//	if (httpSlashes != string::npos) {
//		httpSlashes += 3;
//	}
//
//	if ( (noHttpProtocol(url) && lastSlash != string::npos) || lastSlash > httpSlashes) {
//		root = url.substr(0, lastSlash-1);
//	}
//
//	// Need a slash so a filename can be appended...
//	return root + "/";
//}

string MetaIconsRetriever::getFilenameFromUrl (string url, size_t filename_start) {
	return url.substr( filename_start, url.length()-1 );
}

//// recursive...
//DOMElement* MetaIconsRetriever::getTileElement (DOMElement* curElem, int index/*=0*/) {
//	DOMElement* finElem = 0;
//	//const XMLCh* x = curElem->getTagName();
//	//xerstr zxc(x);
//	if ( x_xerstr(curElem->getTagName()).s_str() == nestedtags.at(index++) ) {
//		DOMElement* nxtElem = curElem->getFirstElementChild();
//		if (nxtElem == 0 || index >= nestedtags.size()) {
//			finElem = nxtElem;
//		} else {
//			finElem = getTileElement (nxtElem, index);
//		}
//	}
//	return finElem;
//}

void fauxPullIcon (string imgurl) {
	std::cout << "faux " << imgurl << " retrieval" << std::endl;
}

void MetaIconsRetriever::procTileChildNodes (DOMNodeList* childNodes, ficonvector& ficons) {
	if ( childNodes ) {
		for (int c = childNodes->getLength(), i = 0; i < c; i++) {
			DOMElement* childElement = static_cast<DOMElement*>(childNodes->item(i));

			if ( childElement && nestedtiles.find( x_xerstr(childElement->getTagName()).s_str() ) != nestedtiles.end() ) {
				x_xerstr imgfile( childElement->getAttribute(s_xerstr("src")) );
				string imgurl = pulledsite_url + clipLeadingSlash(imgfile);
				//fauxPullIcon(imgurl);
				pullIcon(imgurl, "msapplication", ficons);
			}
		}
	}
}

void MetaIconsRetriever::procTilesXMLfile (string tilesxmlfile, ficonvector& ficons) {
	parser.parse(tilesxmlfile);
	DOMDocument* doc = parser.getDocument();
	DOMNodeList* tiletags = doc->getElementsByTagName(s_xerstr("tile"));

	if (tiletags && tiletags->getLength() > 0) {

		DOMNodeList* childNodes = tiletags->item(0)->getChildNodes();

		procTileChildNodes (childNodes, ficons);
	}
}

void MetaIconsRetriever::procTilesXML (string tilesxmlurl, ficonvector& ficons) {
	// TODO: Get IE 11 Tiles for Win 8.1 Start Screen from xml file
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

				std::cout << "filename: " << filename << std::endl;

				string tilesxmlfile = (fs::temp_directory_path() / filename);
				std::cout << "temp XML file: " << tilesxmlfile << std::endl;

				std::cout << "Tiles XML URL: " << tilesxmlurl << std::endl;

				ofstream ofs(tilesxmlfile, std::ios::trunc);

				//procTilesXMLfile("/home/David/tmp/browserconfig.xml", ficons);

				string tilesxml;
				Curler::pull(tilesxmlurl, tilesxml);
				ofs << tilesxml;

				// MUST close file before passing it on for further processing
				// so that it can be opened later by the Xerces parser for reading!
				// Otherwise — AARGGH! :) — an exception will be thrown!
				ofs.close();

				//std::cout << "temp XML file (2): " << tilesxmlfile << " length = " << tilesxml.length() << std::endl;
				//procTilesXMLfile("/home/David/tmp/browserconfig.xml", ficons);
				procTilesXMLfile(tilesxmlfile, ficons);

//				///////////////////////////////////////////////////////////////
//				///// Temporary stuff to read XML file to test fix of file
//
//					std::ifstream ifs(tilesxmlfile);
//					if (!ifs) throw std::runtime_error( string("cannot open " + tilesxmlfile).c_str() );
//
//					std::array<char,1024> buffer;
//					char* buf = buffer.begin();
//					do {
//						ifs.getline(buf, 1024);
//						tilesxml += string(buf);
//						buffer.fill('\0');
//					} while (!ifs.fail() && !ifs.eof());
//
//				///////////////////////////////////////////////////////////////
//				///////////////////////////////////////////////////////////////

//				/*
//				 * Iterate from end to beginning through tilesxml looking for the characters "./>"
//				 * (where . is anything but a space); where found, insert a space to change it to
//				 * ". />".
//				 */
//
//				clrmem(sm);
//				for (int i = tilesxml.length()-1; i >= 0; --i) {
//					char c = tilesxml[i];
//					switch (c) {
//						case '>' : sm.tag = true;                           continue;
//						case '/' : sm.tag ? (sm.slash = true) : clrmem(sm); continue;
//						case '\r': tilesxml[i]='\n'; clrmem(sm);			continue;
//						default  :                                          break;
//					}
//
//					// When considering the following if statement, keep in mind that nothing will happen with it
//					// when a '>' is read or when a subsequent '/' is read because the loop is continued in these
//					// events by the cases in the case statement above.
//					if (sm.tag)
//					{
//						if (sm.slash && c != ' ') {
//							tilesxml.insert(i+1, 1, ' ');	// i+1 since we want to insert just after the slash, not the non-space char
//						}
//						clrmem(sm);
//					}
//				}
//
////				clrmem(sm);
////				for (auto c_itr = tilesxml.rbegin(); c_itr == tilesxml.rend(); --c_itr) {
////					switch (*c_itr) {
////						case '>' : sm.tag = true;                           continue;
////						case '/' : sm.tag ? (sm.slash = true) : clrmem(sm); continue;
////						default  :                                          break;
////					}
////
////					if (sm.tag && sm.slash) {
////						if (*c_itr != ' ') {
////							c_itr = tilesxml.insert(c_itr, ' ');
////						}
////						clrmem(sm);
////					}
////				}

				//ofstream ofs(tilesxmlfile, std::ios::trunc);
			//	ofs << tilesxml;
/*
				std::cout << tilesxmlfile << std::endl;
				parser.parse(tilesxmlfile);
				std::cout << "Presumably parsed successfully." << std::endl;
				DOMDocument* doc = parser.getDocument();

				// TODO: Retrieve icons referred to in the DOM
				DOMElement* tile;
				DOMElement* childElement;
				if ( (tile = getTileElement(doc->getDocumentElement())) && (childElement = tile->getFirstElementChild()) ) {
					for (int c = tile->getChildElementCount(), i = 0; i < c; i++) {
						// TODO: Process tile nodes
						if (childElement) {
							if ( nestedtiles.find( x_xerstr(childElement->getTagName()).s_str() ) != names.end() ) {
								x_xerstr imgfile( childElement->getAttribute(s_xerstr("src")) );
								string imgurl = pulledsite_url + clipLeadingSlash(imgfile);
								pullIcon(imgurl, "msapplication", ficons);
							}
						}
					}
				}
*/

//				DOMElement* root = doc->getDocumentElement();
//				if (root->getTagName() == "browserconfig") {
//					DOMElement* msapp = root->getFirstElementChild();
//					if (msapp->getTagName() == "msapplication") {
//						DOMElement* tile = msapp->getFirstElementChild();
//						if (tile->getTagName() == "tile") {
//							for (int ce = tile->getChildElementCount(); ce > 0; --ce) {
//							}
//						}
//					}
//				}

			} catch (XMLException& e) {
				string msg = x_xerstr(e.getMessage());
				std::cerr << tilesxmlurl << " : XMLException : " << msg << "\n" \
				          << "(skipping file)\n" << std::endl;
			} catch (SAXParseException &e) {
				string msg = x_xerstr(e.getMessage());
				std::cerr << tilesxmlurl << " : SAXParseException : " << msg << "\n" \
				          << "(skipping file)\n" << std::endl;
			} catch (std::exception &e) {
				std::cerr << tilesxmlurl << " : std::exception : " << e.what() << "\n" \
						  << "(skipping file)\n" << std::endl;
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
	std::cout << "pulledsite_url: " << pulledsite_url << std::endl;
	getIconTags("meta", ficons);
	//procTilesXMLfile("/home/David/tmp/browserconfig.xml", ficons);
//	procTilesXML("images/icons/browserconfig.xml", ficons);
}

