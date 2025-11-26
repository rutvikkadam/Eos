#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

// A recursive function to list the contents of a directory
void list_directory_recursive(const char *dir_path) {
	DIR *dp = NULL;
	struct dirent *ent;

	// Attempt to open the directory stream
	dp = opendir(dir_path);

	// If opendir fails, print an error and return
	if (dp == NULL) {

		printf("Directory is not opened...\n");
		exit(1);
	}

	printf("Directory content for: %s\n", dir_path);

	// Read entries one by one
	while ((ent = readdir(dp)) != NULL) {
		// Construct the full path of the entry
		char new_path[1024]; // Use a buffer large enough for a path

		// Skip "." (current directory) and ".." (parent directory)
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
			continue;
		}

		snprintf(new_path, sizeof(new_path), "%s/%s", dir_path, ent->d_name);

		// Print the details of the current entry
		printf("%lu %s %u\n", ent->d_ino, new_path, ent->d_type);

		// Check if the entry is a directory and recursively call the function
		if (ent->d_type == DT_DIR) {
			list_directory_recursive(new_path);
		}
	}

	// Close the directory stream
	closedir(dp);
}

int main(int argc, char *argv[]) {
	// Check for the correct number of command-line arguments
	if (argc != 2) {
		printf("directory path is not mentioned..\n");
		printf("Run as : %s <dir path>\n", argv[0]);
		exit(1);
	}

	// Call the recursive function with the initial path
	list_directory_recursive(argv[1]);

	return 0;
}

