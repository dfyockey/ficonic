# ficonic
Utility for retrieving favicons and other site-related icons for a given URL

## Description
The purpose of _ficonic_ is to download all icons intended for use in identifying a site at a given URL. This allows the user to select the icon best suited for the medium through which they intend to identify the site.

_ficonic_ downloads `favicon.ico` and `apple-touch-icon.png` files where found in the site's root directory and any icons identified in HTML `link` tags having recognized `rel` values. Any properly formatted `.ico` files are split into their contained icons and saved in as both `.bmp` and `.png` format files. Therefore, if a `.ico` file contains three different sized icons, for example, _ficonic_ will save six icons for the one file: three `.bmp` files and three `.png` files. An attempt is made to determine the actual format of an improperly formatted `.ico` file, e.g. where a `.png` file has simply been renamed `favicon.ico`; if successful, the icon is saved in that format with the proper extension.

The downloaded icons are saved to a user-specified directory. While their contained icons are saved, `.ico` files themselves are not currently saved.

If desired, the retrieved `favicon.ico` file from the last run of the application may be recovered from the system's temporary directory until the directory is cleared by the system.

Run `ficonic -h` for usage information.

## Dependencies
The following libraries are required:
* Boost version 1.32 or better 
* Boost-Program-Options
* curl
* Magick++ version 6 (C++ Bindings library for ImageMagick)
* htmlcxx

## To Do
* Save `.ico` files along with icon files.
* Handle HTML `meta` tags referring to Microsoft tiles.
* Handle Progressive Web App manifests referring to icons.
* Resolve build warnings about `MAGICKCORE_QUANTUM_DEPTH` and `MAGICKCORE_HDRI_ENABLE`.
* Enable use of `$HOME` and `~` to refer to the home directory in specifying the icon storage directory path.