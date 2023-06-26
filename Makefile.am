AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = FaviconGofer

FaviconGofer_SOURCES = \
	src/Curler.cpp \
	src/Curler.h \
	src/main.cpp \
	src/ficon.cpp \
	src/ficon.hpp \
	src/program_info.h \
	src/RootIconsRetriever.cpp \
	src/RootIconsRetriever.hpp
	
FaviconGofer_CPPFLAGS =	-I/usr/include/ImageMagick-6

FaviconGofer_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

