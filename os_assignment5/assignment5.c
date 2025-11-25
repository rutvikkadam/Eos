#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/**
 * Lists the contents of a specified directory.
 * @param path The path of the directory to list.
 */
void list_directory_contents(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        // Print error message if the directory cannot be opened
        fprintf(stderr, "Error opening directory '%s': %s\n", path, strerror(errno));
        return;
    }

    printf("Contents of directory: %s\n", path);
    printf("----------------------------------------\n");

    // Read entries from the directory one by one
    while ((entry = readdir(dir)) != NULL) {
        // Print the name of the file or subdirectory
        printf("%s\n", entry->d_name);
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
        fprintf(stderr, "Example: %s /home\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Call the function to list the directory contents using the provided path
    list_directory_contents(argv[1]);

    return EXIT_SUCCESS;
}

