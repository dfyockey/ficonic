/*
 * DOMParser.cpp
 *
 *  Created on: Aug 11, 2023
 *      Author: David Yockey
 *
 */

#include "DOMParser.hpp"
#include "XmlStrTypes.hpp"

///// private ////////////////////////////////////////////////////////

///// protected //////////////////////////////////////////////////////

///// public /////////////////////////////////////////////////////////

// TODO: Create a class derived from HandlerBase to actually handle errors and replace HandlerBase() below
DOMParser::DOMParser() : parser(new XercesDOMParser()),
                         errHandler(static_cast<ErrorHandler*>(new HandlerBase())) {
	parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setErrorHandler(errHandler);
}

DOMParser::~DOMParser() {
	delete parser;
	delete errHandler;
}

DOMDocument* DOMParser::parse(std::string url) {
	parser->parse(XmlCh(url));
	return parser->getDocument();
}
