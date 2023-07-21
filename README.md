# ficonic
Utility for retrieving favicons and other site-related icons for a given URL

## Description
The immediate purpose of _ficonic_ is to enable download of all icons provided for identifying a site at a given URL. This allows the user to select the icon best suited for the medium through which they intend to identify the site. The longer term goal is to provide a library for loading data for all of the aforementioned icons into a C++ application for manipulation and/or use as needed.

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
_(in no particular order...)_
* Handle HTML `meta` tags referring to Microsoft tiles.
* Handle Progressive Web App manifests referring to icons.
* Resolve build warnings about `MAGICKCORE_QUANTUM_DEPTH` and `MAGICKCORE_HDRI_ENABLE`.
* Enable use of `$HOME` and `~` to refer to the home directory in specifying the icon storage directory path.
* Add user-friendly error messages for missing required arguments.
* Update help information to indicate what arguments are required.
* Clean up console output to improve usability.
* Handle `.gif` icon files.
* Add error handling to skip unsupported file types.
* Create and save icons to a different directory for each URL from which icons are retrieved.