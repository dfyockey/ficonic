/*
 * DOMParser.hpp
 *
 *  Created on: Aug 11, 2023
 *      Author: David Yockey
 *
 */

#ifndef SRC_XERCESCPP_DOMPARSER_HPP_
#define SRC_XERCESCPP_DOMPARSER_HPP_

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <string>
#include "InitXerces.hpp"

using namespace xercesc;

class DOMParser {
private:
	InitXerces		 xercescpp;
	XercesDOMParser* parser;
	ErrorHandler*	 errHandler;
public:
	DOMParser();
	virtual ~DOMParser();
	void parse(std::string xmlfileurl);
	DOMDocument* getDocument() { return parser->getDocument(); }
};

#endif /* SRC_XERCESCPP_DOMPARSER_HPP_ */
