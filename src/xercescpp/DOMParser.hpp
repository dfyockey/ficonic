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
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <string>

using namespace xercesc;

class DOMParser {
private:
	XercesDOMParser* parser;
	ErrorHandler*	 errHandler;
public:
	DOMParser();
	virtual ~DOMParser();
	DOMDocument* parse(std::string xmlfileurl);
};

#endif /* SRC_XERCESCPP_DOMPARSER_HPP_ */
