/*
 * DOMParser.cpp
 *
 *  Created on: Aug 11, 2023
 *      Author: David Yockey
 *
 */

#include "DOMParser.hpp"

///// private ////////////////////////////////////////////////////////

///// protected //////////////////////////////////////////////////////

///// public /////////////////////////////////////////////////////////

// TODO: Create a class derived from HandlerBase to actually handle errors and replace HandlerBase() below

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
	parser->parse(url.c_str());
}
