AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = ficonic

ficonic_SOURCES = \
	src/Curler.cpp \
	src/Curler.h \
	src/main.cpp \
	src/ficon.cpp \
	src/ficon.hpp \
	src/program_info.h \
	src/IconsRetriever.cpp \
	src/IconsRetriever.hpp \
	src/RootIconsRetriever.cpp \
	src/RootIconsRetriever.hpp \
	src/LinkIconsRetriever.cpp \
	src/LinkIconsRetriever.hpp \
	src/MetaIconsRetriever.cpp \
	src/MetaIconsRetriever.hpp \
	src/HtmlTagAccessor.cpp \
	src/HtmlTagAccessor.hpp
	
	
ficonic_CPPFLAGS =	\
	-I/usr/include/ImageMagick-6 \
	-I/usr/include/htmlcxx/html

ficonic_LDFLAGS = \
	`Magick++-config --cppflags --cxxflags --ldflags --libs`
