#include <stdio.h>
#include <dirent.h>
#include <wchar.h>

void search_dir(const wchar_t* dir_name) {
    _WDIR* dir;
    struct _wdirent* ent;
    wchar_t csv_file_name[256];

    // Open the directory specified by dir_name
    dir = _wopendir(dir_name);

    // Check if the directory was successfully opened
    if (dir != NULL) {
        // Read all the entries in the directory
        while ((ent = _wreaddir(dir)) != NULL) {
            // Check if the entry is a directory
            if (ent->d_type == DT_DIR) {
                // Skip the "." and ".." directories
                if (wcscmp(ent->d_name, L".") == 0 || wcscmp(ent->d_name, L"..") == 0) {
                    continue;
                }

                // Recursively search the sub-directory
                wchar_t path[1024];
                swprintf(path, sizeof(path) / sizeof(wchar_t), L"%ls/%ls", dir_name, ent->d_name);
                search_dir(path);
            }
            else {
                // Check if the entry is a file with the ".h" extension
                if (wcsstr(ent->d_name, L".h") != NULL) {
                    // Open the CSV file for writing
                    swprintf(csv_file_name, sizeof(csv_file_name) / sizeof(wchar_t), L"%ls.csv", dir_name);
                    FILE* csv_file;
                    errno_t error = _wfopen_s(&csv_file, csv_file_name, L"a");

                    // Check if the CSV file was successfully opened
                    if (error != 0) {
                        // Print an error message if the CSV file could not be opened
                        _wperror(L"");
                        return;
                    }

                    // Write the file name (without the extension) to the CSV file
                    wchar_t file_name[256];
                    wcscpy_s(file_name, sizeof(file_name) / sizeof(wchar_t), ent->d_name);
                    file_name[wcslen(file_name) - 2] = L'\0';
                    fwprintf(csv_file, L"%ls\n", file_name);

                    // Close the CSV file
                    fclose(csv_file);
                }
            }
        }

        // Close the directory
        _wclosedir(dir);
    }
    else {
        // Print an error message if the directory could not be opened
        _wperror(L"");
    }
}

int wmain(int argc, wchar_t* argv[]) {
    // Check if the user provided a directory name
    if (argc < 2) {
        wprintf(L"Usage: %ls <directory>\n", argv[0]);
        return 1;
    }

    // Search the specified directory for files with the ".h" extension
    search_dir(argv[1]);

    return 0;
}
