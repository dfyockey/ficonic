/*
 * ficon.hpp
 *
 *  Created on: Jun 16, 2023
 *      Author: David Yockey
 */

#ifndef SRC_FICON_HPP_
#define SRC_FICON_HPP_

#include <map>
#include <string>
#include <Magick++.h>

using namespace Magick;
using std::string;

namespace ficonic {

	struct ficon {
		ficon(string rel, string type, std::pair<size_t, size_t> size, Blob data)
			: rel(rel), type(type), width(size.first), height(size.second), data(data) {};
		string	rel;
		string	type;
		size_t	width;
		size_t	height;
		Blob	data;
	};

	typedef std::vector<struct ficon> ficonvector;

	class ficonfactory {
	private:
		static ficon make_ficon(string rel, Image image, Blob& blob);
	public:
		static ficon make_ficon(string rel, Image image);
		static ficon make_ficon(string rel, Blob& blob);
		static ficon make_ficon(string rel, string type, Image image);
	};
}

#endif /* SRC_FICON_HPP_ */
