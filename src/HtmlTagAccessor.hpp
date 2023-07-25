/*
 * HtmlTagAccessor.hpp
 *
 *  Created on: Jul 25, 2023
 *      Author: David Yockey
 *
 * MIT License
 *
 * Copyright © 2023 David Yockey
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
