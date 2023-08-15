/*
 * XmlStr.hpp
 *
 *  Created on: Aug 11, 2023
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

#ifndef SRC_XERCESCPP_XMLSTR_HPP_
#define SRC_XERCESCPP_XMLSTR_HPP_

#include <xercesc/util/XMLString.hpp>
#include <string>
#include "InitXerces.hpp"

using std::string;

class XmlStr {
private:
	InitXerces xercescpp;
	char* message;
public:
	XmlStr(const XMLCh* msg) : message(XMLString::transcode(msg)) {}
	virtual ~XmlStr() { XMLString::release(&message); }
	operator string() { return string(message); }
	// TODO: Add an ostream& operator<<() free function to enable streaming out XmlStr as a std::string
	// 		 (see ~/Cups-PDF/class_StrX.pdf)
};

class XmlCh {
private:
	InitXerces xercescpp;
	XMLCh* message;
public:
	XmlCh(std::string msg) : message(XMLString::transcode(msg.c_str())) {};
	virtual ~XmlCh() { XMLString::release(&message); }
	operator XMLCh*() { return message; }
	// TODO: Add an ostream& operator<<() free function to enable streaming out XmlCh as a std::string
	//		 (see ~/Cups-PDF/class_StrX.pdf)
};

#endif /* SRC_XERCESCPP_XMLSTR_HPP_ */
