/*
 * Curler.h
 * - Class to retrieve data from the internet via curl
 *
 * MIT License
 *
 * Copyright © 2022,2023 David Yockey
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
 *
 */

#ifndef SRC_CURLER_H_
#define SRC_CURLER_H_

#include <cstdio>
#include <map>
#include <sstream>

#include <curl/curl.h>

using std::string;
using std::ostringstream;

const int null = 0;

typedef std::multimap<CURLoption,string> fieldsmap;

// Curler : Manages pulling resources from URLs using the libcurl Easy interface

class Curler {
private:
	CURL* curl;
	struct curl_slist *customHeaders;

	void setCurlOptions(CURL* curl, string url, ostringstream& ossCurlResponse);
	void setHttpHeaderFields(fieldsmap fields);

	static size_t write_callback(char* data, size_t size, size_t nmemb, void* userdata);

public:
	Curler(fieldsmap* fields=0);	// key-value pairs passed to the constructor in the fieldsmap
									// are persistently stored in the CURL object

	ostringstream pull(string url);

	virtual ~Curler();				// curl_easy_cleanup is executed in the dtor,
									// so the user doesn't need to remember to call it
};

class setopt_error : public std::runtime_error {
	public:
		setopt_error(CURLcode res) : std::runtime_error(string("curl_easy_setopt() failed: ") + curl_easy_strerror(res) ) {}
};

#endif /* SRC_CURLER_H_ */
