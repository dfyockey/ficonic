/*
 * HtmlTagAccessor.hpp
 *
 *  Created on: Jul 25, 2023
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

#ifndef SRC_HTMLTAGACCESSOR_HPP_
#define SRC_HTMLTAGACCESSOR_HPP_

#include "Curler.h"
#include <string>

using std::string;

class HtmlTagAccessor : protected virtual Curler {
private:
	string html;
	string prev_url;
public:
	HtmlTagAccessor();
	virtual ~HtmlTagAccessor();
	void pull(string url, string& htmlref);
};

//string HtmlTagAccessor::html = "";
//string HtmlTagAccessor::prev_url = "";

#endif /* SRC_HTMLTAGACCESSOR_HPP_ */
