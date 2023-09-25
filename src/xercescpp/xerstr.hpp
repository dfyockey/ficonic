/*
 * xerstr.hpp
 *
 *  Created on: Aug 16, 2023
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

#ifndef SRC_XERCESCPP_XERSTR_HPP_
#define SRC_XERCESCPP_XERSTR_HPP_

#include <string>
#include "InitXerces.hpp"
#include <xercesc/util/XMLString.hpp>

using std::string;

// 1)
class xerstr {
private:
	InitXerces xercescpp;

	const bool clean_x = true;
	const bool clean_c = false;
	bool cleanup = true;

	string s;
	XMLCh* x;
	char*  c;

	void setfromXMLCh	(const XMLCh* txt);
	void setfromString	(const string txt);

public:
	xerstr(const XMLCh* txt) { setfromXMLCh(txt);  }
	xerstr(const string txt) { setfromString(txt); };

	virtual ~xerstr();

	operator const string() { return s; }
	operator const XMLCh*() { return x; }
	operator const char* () { return c; }

	const string s_str() { return s; }
	const XMLCh* x_str() { return x; }
	const char*  c_str() { return c; }

	// 2)
};

#endif /* SRC_XERCESCPP_XERSTR_HPP_ */

// 1) A class derived from std::string has been considered and disregarded, at least for now.
//    That's because it would require either transcoding every time the Xerces string was accessed
//    or significant complexity so the std::string and Xerces string are kept in sync and so the latter
//    is released before the std::string was changed and at class destruction.
// 2) Apparently, the stream operator '<<' can't be overloaded because C++ can't determine whether it
//    or one of the other operators (string, XMLCh*, or char*) should be applied when an xerstr is
//    provided as an argument to '<<' in, say, a std::cout stream.
