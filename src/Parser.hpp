/*
 * Parser.hpp
 * - Wrapper class for boost::json::parser
 *
 * Copyright 2022 David Yockey
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
 *
 */

#ifndef SRC_PARSER_HPP_
#define SRC_PARSER_HPP_

#include <string>
#include <boost/json.hpp>

namespace bjs = boost::json;

class Parser {
private:
	bjs::parser jsonParser;

public:
	bjs::value parse(std::string json);
};

#endif /* SRC_PARSER_HPP_ */
