# List Code Files

This program searches a specified directory for files with the ".h" extension and writes their names (without the extension) to a CSV file in the same directory.


## Usage

To use this program, compile it and run it from the command line, passing the directory to search as a command-line argument. For example:


    $ ./program /path/to/directory

If the program is successful, it will create a CSV file named after the directory (with a `.csv` extension) in the same directory, and write the names of the ".h" files it finds to that file.


## Requirements

This program uses the `stdio.h`, `dirent.h`, and `wchar.h` headers, so these headers must be available on your system. It also uses the `_wopendir`, `_wreaddir`, `_wclosedir`, `_wperror`, and `_wfopen_s` functions, so the corresponding libraries must be linked when compiling the program.
