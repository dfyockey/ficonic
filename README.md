# ficonic
Utility for retrieving favicons and other site-related icons for a given URL

## Description
The purpose of _ficonic_ is to download all icons intended for use in identifying a site at a given URL. This allows the user to select the icon best suited for the medium through which they intend to identify the site.

_ficonic_ downloads `favicon.ico` and `apple-touch-icon.png` files where found in the site's root directory and any icons identified in HTML `link` tags having recognized `rel` values.

Any properly formatted `.ico` files are split into their contained icons and saved in as both `.bmp` and `.png` format files. Therefore, if a `.ico` file contains three different sized icons, for example, _ficonic_ will save seven icons for the one file: three `.bmp` files, three `.png` files, and a copy of the original `.ico` file. An attempt is made to determine the actual format of an improperly formatted `.ico` file, e.g. where a `.png` file has simply been renamed `favicon.ico`. If successful, the icon is saved in that format with the proper extension.

The icons are saved to a user-specified directory.

Run `ficonic -h` for usage information.

## Dependencies
The following libraries are required:
* Boost version 1.32 or better 
* Boost-Program-Options
* curl
* Magick++ version 6 (C++ Bindings library for ImageMagick)
* htmlcxx

## To Do
* Handle HTML `meta` tags referring to Microsoft tiles.
* Handle Progressive Web App manifests referring to icons.
* Resolve build warnings about `MAGICKCORE_QUANTUM_DEPTH` and `MAGICKCORE_HDRI_ENABLE`.
* Enable use of `$HOME` and `~` to refer to the home directory in specifying the icon storage directory path.