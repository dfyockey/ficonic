# FaviconGofer
Utility to retrieve favicons for a given URL

This utility currently only provides icons based on files stored in a site's root directory where those files exist. A site's `favicon.ico` file is retrieved, split into its constituent icon images, and each icon image is provided in both BMP and PNG formats. A site's `apple-touch-icon.png` file is also retrieved and stored. The resultant image files are stored in a user specified directory.

If desired, the retrieved `favicon.ico` file from the last run of the application may be recovered from the system's temporary directory (currently assumed to be `/tmp`; that needs to be fixed...) until the directory is cleared by the system.

Run `FaviconGofer -h` for usage information.
