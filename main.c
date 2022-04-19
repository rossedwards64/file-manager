#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

int list_all_files_in_dir(char* path);
size_t get_number_of_files(char* path);
int populate_dir_list(char* path, char** dirlist);
void print_list(char** dirlist, size_t file_no);
int sort_dir_list(char** dirlist);
bool compare(char* a, char* b);

// implement a sort function so that files are listed alphabetically
// this is a good opportunity to use function pointers

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		list_all_files_in_dir(".");
	}

	int counter = 1;
	while(++counter <= argc)
	{
		list_all_files_in_dir(argv[counter - 1]);
	}

	return EXIT_SUCCESS;
}

int list_all_files_in_dir(char* path)
{
	size_t file_no = get_number_of_files(path);
	char* dirlist[file_no];

	populate_dir_list(path, &*dirlist);
	print_list(&*dirlist, file_no);

	return EXIT_SUCCESS;
}

size_t get_number_of_files(char* path)
{
	DIR* directory = opendir(path);
	struct dirent* entry;
	size_t n;

	while((entry = readdir(directory)) != NULL)
		n++;

	return n;
}

int populate_dir_list(char* path, char** dirlist)
{
	DIR* directory = opendir(path);
	struct dirent* entry;

	if(readdir(directory) == NULL)
	{
		puts("Failed to open directory!");
		return EXIT_FAILURE;
	}

	int counter = 0;

	while((entry = readdir(directory)) != NULL)
	{
		dirlist[counter] = (char*) malloc(strlen(entry->d_name) + 1);
		strncpy(dirlist[counter], entry->d_name, strlen(entry->d_name));
		counter++;
	}

	closedir(directory);

	return EXIT_SUCCESS;
}

void print_list(char** dirlist, size_t file_no)
{
	for(size_t i = 0; i < file_no - 1; i++)
	{
		printf("%s\n", dirlist[i]);
	}
}

bool compare(char* a, char* b)
{
	return a[0] < b[0];
}
