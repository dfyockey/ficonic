/*
 * DOMParser.cpp
 *
 *  Created on: Aug 11, 2023
 *      Author: David Yockey
 *
 */

#include "DOMParser.hpp"
//#include "XmlStrTypes.hpp"
//#include "xerstr.hpp"
#include <iostream>

///// private ////////////////////////////////////////////////////////

///// protected //////////////////////////////////////////////////////

///// public /////////////////////////////////////////////////////////

// TODO: Create a class derived from HandlerBase to actually handle errors and replace HandlerBase() below
//DOMParser::DOMParser() : parser(new XercesDOMParser()),
//                         errHandler(static_cast<ErrorHandler*>(new HandlerBase())) {
//	parser->setValidationScheme(XercesDOMParser::Val_Never);
//    parser->setErrorHandler(errHandler);
//}

DOMParser::DOMParser() {
	parser = new XercesDOMParser();
	errHandler = (ErrorHandler*) new HandlerBase();

	parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setErrorHandler(errHandler);
}

DOMParser::~DOMParser() {
	delete parser;
	delete errHandler;
}

void DOMParser::parse(std::string url) {
	//XmlCh xmlch(url);
	//parser->parse(XmlCh(url));

	//XMLCh* xurl = s_xerstr(url);

	//parser->parse(xmlch);

//	XMLCh* xstr = XMLString::transcode("/tmp/browserconfig.xml");
//	parser->parse(xstr);
//	XMLString::release(&xstr);

	std::cout << url << std::endl;
	parser->parse(url.c_str());

//	try {
//		InitXerces xercescpp;
//
//		XercesDOMParser* parser = new XercesDOMParser();
//		parser->setValidationScheme(XercesDOMParser::Val_Always);
//
//		ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
//		parser->setErrorHandler(errHandler);
//
//		std::cout << url << std::endl;
//		parser->parse(url.c_str());
//
//		delete parser;
//		delete errHandler;
//	} catch (...) {
//		std::cout << "WTF!" << std::endl;
//	}

}
