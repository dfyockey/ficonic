/*
 * RootIconsRetriever.hpp
 *
 *  Created on: Jun 16, 2023
 *      Author: David Yockey
 */

#ifndef SRC_ROOTICONSRETRIEVER_HPP_
#define SRC_ROOTICONSRETRIEVER_HPP_

#include <map>
#include <string>
#include "ficon.hpp"

using namespace ficonic;
using std::string;

class RootIconsRetriever {
public:
	RootIconsRetriever();

	void pull(string url, ficonvector& ficons);

	virtual ~RootIconsRetriever();
};

#endif /* SRC_ROOTICONSRETRIEVER_HPP_ */
