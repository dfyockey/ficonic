/*
 * FaviconGofer.cpp
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

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <exception>

#include <boost/program_options.hpp>

#include "Curler.h"

using std::string;

namespace fs = std::filesystem;
namespace bpo = boost::program_options;



bpo::options_description initDescription() {
	bpo::options_description desc("Utility for retrieving a favicon for a given URL");
	desc.add_options()
		( "help,h", "Generate help message." )
		( "url,u", bpo::value<string>()->required(), "URL from which to retrieve favicon.")
		( "dir,d", bpo::value<fs::path>()->default_value(fs::temp_directory_path()), "Directory to which favicon will be saved." )
	;
	return desc;
}

bpo::variables_map initVariablesMap(int argc, char* argv[], bpo::options_description& desc) {
	bpo::variables_map vm;
	bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
	return vm;
}

void vmProc (bpo::variables_map& vm, string& url, fs::path& dir ) {
	if (vm.count("url")) {
		url = vm["url"].as<string>();
		if ( url.back() != '/') {
			url += "/";
		}
	}

	if (vm.count("dir")) {
		dir = vm["dir"].as<fs::path>();
	}
}

int execMain(bpo::variables_map& vm) {
	string url;
	fs::path dir;

	vmProc (vm, url, dir);

	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, "FaviconGofer"} };
	Curler curl(&httpHeaderFields);

	std::ofstream ofFavicon( dir/"favicon.ico", std::ios::binary );
	curl.pull( url + "favicon.ico", ofFavicon );
	return 0;
}

int main(int argc, char* argv[]) {
	bpo::options_description desc = initDescription();
	bpo::variables_map       vm   = initVariablesMap(argc, argv, desc);

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	bpo::notify(vm);

	return execMain(vm);
}
