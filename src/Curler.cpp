/*
 * Curler.cpp
 * - Class Curler method implementations
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

#include "Curler.h"
#include <iostream>

using std::runtime_error;

///// private ////////////////////////////////////////////////////////

void Curler::setCurlOptions(CURL* curl, string url, ostringstream& ossCurlResponse) {
	CURLcode res;

	// set minimal options
	do {
		if( (res = curl_easy_setopt( curl, CURLOPT_URL, url.c_str() )) != CURLE_OK ) break;
		if( (res = curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback )) != CURLE_OK ) break;
		if( (res = curl_easy_setopt( curl, CURLOPT_WRITEDATA, reinterpret_cast<void*>(&ossCurlResponse) )) != CURLE_OK ) break;
	} while (false);

	if ( res != CURLE_OK )
		throw setopt_error(res);
}

void Curler::setHttpHeaderFields(fieldsmap fields) {
	CURLcode res;
	bool customize = false;

	for (const auto& [key,value] : fields) {

		if( key == CURLOPT_HTTPHEADER ) {
			customHeaders = curl_slist_append(customHeaders, value.c_str());
			customize = true;
			continue;
		}

		if( (res = curl_easy_setopt( curl, key, value.c_str() )) != CURLE_OK )
			throw setopt_error(res);
	}

	if ( customize && (res = curl_easy_setopt( curl, CURLOPT_HTTPHEADER, customHeaders)) != CURLE_OK )
		throw setopt_error(res);
}

size_t Curler::write_callback(char* data, size_t size, size_t nmemb, void* userdata) {
	size_t datasize = size * nmemb;

	ostringstream* oss = reinterpret_cast<ostringstream*>(userdata);
	oss->write(data,datasize);

	return datasize;
}

///// public /////////////////////////////////////////////////////////

Curler::Curler(fieldsmap* fields) {
	if ( !(curl = curl_easy_init()) )
		throw std::runtime_error("curl_easy_init() failed");

	customHeaders = 0;

	if (fields)
		setHttpHeaderFields(*fields);
}

ostringstream Curler::pull(string url) {
	CURLcode res;
	ostringstream ossCurlResponse;

	try {
		setCurlOptions(curl, url, ossCurlResponse);

		// Perform the request, where res will get the return code, and then check for errors
		if( (res = curl_easy_perform(curl)) != CURLE_OK)
			throw std::runtime_error(string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	// Return a string containing the retrieved data requested or an empty string
    return ossCurlResponse;
}

Curler::~Curler() {
	if (customHeaders)
		curl_slist_free_all(customHeaders);

    curl_easy_cleanup(curl);
}
