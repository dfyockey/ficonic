/*
 * ficon.cpp
 *
 *  Created on: Jun 22, 2023
 *      Author: David Yockey
 */

#include "ficon.hpp"
using namespace ficonic;

ficon ficonfactory::make_ficon(string rel, Image image, Blob& blob) {
	size_t width  = image.columns();
	size_t height = image.rows();
	ficonic::ficon f(rel, image.magick(), std::make_pair(width, height), blob);
	return f;
}

ficon ficonfactory::make_ficon(string rel, Image image) {
	Blob blob;
	image.write(&blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

ficon ficonfactory::make_ficon(string rel, Blob& blob) {
	Image image(blob);
	return ficonfactory::make_ficon(rel, image, blob);
}

ficon ficonfactory::make_ficon(string rel, string type, Image image) {
	image.magick(type);
	return ficonfactory::make_ficon(rel, image);
}
