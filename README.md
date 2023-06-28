# FaviconGofer
Utility to retrieve favicons for a given URL

This utility currently only provides icons based on files stored in a site's root directory where those files exist. A site's `favicon.ico` file is retrieved, split into its constituent icon images, and each icon image is provided in both BMP and PNG formats. A site's `apple-touch-icon.png` file is also retrieved and stored. The resultant image files are stored in a user specified directory.

If desired, the retrieved `favicon.ico` file from the last run of the application may be recovered from the system's temporary directory (currently assumed to be `/tmp`; that needs to be fixed...) until the directory is cleared by the system.

Run `FaviconGofer -h` for usage information.

## Dependencies
The following libraries are required:
* Boost version 1.32 or better 
* Boost-Program-Options
* curl
* Magick++ version 6 (C++ Bindings library for ImageMagick)
* htmlcxx

Note: Magick++ for GraphicsMagick _**may**_ work but has not been tested. If you should happen to test it, please post an Issue describing your experience so I can refer to the information here, giving you credit of course. _Thanks!_