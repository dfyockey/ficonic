/*
 * ficon.cpp
 *
 *  Created on: Jun 22, 2023
 *      Author: David Yockey
 */

#include "ficon.hpp"

ficonic::ficon ficonic::make_ficon(string rel, string type, Image image) {
	size_t width  = image.columns();
	size_t height = image.rows();
	Blob blob;
	image.magick(type);
	image.write(&blob);
	ficonic::ficon f(rel, type, std::make_pair(width, height), blob);
	return f;
}
