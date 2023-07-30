/*
 * main.cpp
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

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <exception>

#include <boost/program_options.hpp>

#include <Magick++.h>
#include "RootIconsRetriever.hpp"
#include "LinkIconsRetriever.hpp"
#include "program_info.h"
#include "ficon.hpp"

using namespace Magick;

using std::string;
using std::cout;
using std::endl;
using std::to_string;

namespace fs = std::filesystem;
namespace bpo = boost::program_options;

///// Initialization and Processing of Program Options ///////////////

bpo::options_description initDescription() {
	bpo::options_description desc("Utility for retrieving favicons for a given URL");
	desc.add_options()
		( "help,h", "Generate help message." )
		( "url,u", bpo::value<string>()->required(), "URL from which to retrieve favicons.")
		( "dir,d", bpo::value<fs::path>()->default_value(fs::temp_directory_path()), "Directory to which to save favicons." )
	;
	return desc;
}

bpo::variables_map initVariablesMap(int argc, char* argv[], bpo::options_description& desc) {
	bpo::variables_map vm;
	bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
	return vm;
}

void set_url(bpo::variables_map& vm, string& url) {
	if (vm.count("url")) {
		url = vm["url"].as<string>();
		if ( url.back() != '/') {
			url += "/";
		}
	}
}

void set_dir(bpo::variables_map& vm, fs::path& dir) {
	if (vm.count("dir")) {
		dir = vm["dir"].as<fs::path>();
	}
}

void parseVariablesMap (bpo::variables_map& vm, string& url, fs::path& dir) {
	set_url(vm, url);
	set_dir(vm, dir);
}

//////////////////////////////////////////////////////////////////////

inline string fill_spaces (string s) { std::replace(s.begin(), s.end(), ' ', '_'); return s; }

void save_icons (ficonic::ficonvector ficons, fs::path dir) {
	std::array<unsigned int, 2> index = {1,1};
	string favicon = dir/"favicon";
	for (auto& ficon : ficons) {
		if (ficon.ext != "ICO") {
			Image image(ficon.data);
			image.write(favicon + to_string(index[0]++) + "." + fill_spaces(ficon.rel) + "." + image.magick());
		} else {
			Blob ico_blob(ficon.data);
			const char* ico_data = static_cast<const char*>(ico_blob.data());
			ofstream ofICO( favicon + to_string(index[1]++) + "." + fill_spaces(ficon.rel) + "." + ficon.ext, std::ios::binary);
			ofICO.write(ico_data, ico_blob.length());
		}
	}
}

int execMain (bpo::variables_map& vm) {
	string url;
	fs::path dir;
	parseVariablesMap (vm, url, dir);

	ficonic::ficonvector ficons;

	RootIconsRetriever rooticonsRetriever;
	rooticonsRetriever.pull(url, ficons);

	LinkIconsRetriever linkiconsRetriever;
	linkiconsRetriever.pull(url, ficons);

	save_icons(ficons, dir);

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
