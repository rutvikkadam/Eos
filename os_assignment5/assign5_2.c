#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

// Define MAX_PATH if it's not already defined by your system headers
#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

/**
 * Lists the contents of a specified directory recursively.
 * @param path The path of the directory to list.
 * @param indent The current indentation level for display formatting.
 */
void recursive_dir_list(const char *path, int indent) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        // Print error message if the directory cannot be opened
        fprintf(stderr, "Error opening directory '%s': %s\n", path, strerror(errno));
        return;
    }

    // Read entries from the directory one by one
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." (current directory) and ".." (parent directory) to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Print the name with appropriate indentation
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("%s\n", entry->d_name);

        // Check if the entry is a directory (using the hint: ent->d_type == DT_DIR)
        if (entry->d_type == DT_DIR) {
            char sub_path[MAX_PATH];
            // Construct the full path to the subdirectory
            snprintf(sub_path, sizeof(sub_path), "%s/%s", path, entry->d_name);
            
            // Recursively call the function for the subdirectory
            recursive_dir_list(sub_path, indent + 1);
        }
    }

    // Close the directory stream
    closedir(dir);
}

/**
 * Main function to handle command-line arguments.
 */
int main(int argc, char *argv[]) {
    // Check if exactly one directory path was provided as an argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        fprintf(stderr, "Example: %s /tmp\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Recursive listing of: %s\n", argv[1]);
    printf("----------------------------------------\n");

    // Call the recursive function with initial indentation level of 0
    recursive_dir_list(argv[1], 0);

    return EXIT_SUCCESS;
}

