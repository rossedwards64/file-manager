#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

int list_dir(const char* path);

// implement a sort function so that files are listed alphabetically
// this is a good opportunity to use function pointers

int main(int argc, char** argv)
{
	int counter = 1;

	if(argc == 1)
		list_dir(".");

	while(++counter <= argc)
	{
		list_dir(argv[counter - 1]);
	}

	return EXIT_SUCCESS;
}

int list_dir(const char* path)
{
	struct dirent* entry;
	DIR* directory = opendir(path);

	if(readdir(directory) == NULL)
	{
		puts("Failed to open directory!");
		return EXIT_FAILURE;
	}

	while((entry = readdir(directory)))
	{
		puts(entry->d_name);
	}

	closedir(directory);

	return EXIT_SUCCESS;
}
