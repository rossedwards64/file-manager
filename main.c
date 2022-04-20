#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// function prototypes
int list_all_files_in_dir(char* path);
size_t get_number_of_files(char* path);
int populate_dir_list(char* path, char** dirlist);
void print_list(char** dirlist, size_t file_no);
int sort_dir_list(char** dirlist);
int is_less_than(const void* a, const void* b);

int main(int argc, char** argv)
{
	if(argc == 1)
		list_all_files_in_dir(".");

	int counter = 1;
	while(++counter <= argc)
		list_all_files_in_dir(argv[counter - 1]);

	return EXIT_SUCCESS;
}

int list_all_files_in_dir(char* path)
{
	size_t file_no = get_number_of_files(path);
	char* dirlist[file_no];

	if(populate_dir_list(path, dirlist))
		return EXIT_FAILURE;

	print_list(dirlist, file_no);

	for(size_t i = 0; i < file_no; i++)
		free(dirlist[i]);

	return EXIT_SUCCESS;
}

size_t get_number_of_files(char* path)
{
	DIR* directory = opendir(path);
	struct dirent* entry;
	size_t n;

	while((entry = readdir(directory)))
		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			n++;

	closedir(directory);
	return n;
}

int populate_dir_list(char* path, char** dirlist)
{
	DIR* directory = opendir(path);
	struct dirent* entry;

	if(directory == NULL)
	{
		perror("Failed to open directory!");
		return EXIT_FAILURE;
	}

	int counter = 0;

	while((entry = readdir(directory)))
	{
		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
		{
			dirlist[counter] = malloc(strlen(entry->d_name) + 1);
			strncpy(dirlist[counter], entry->d_name, strlen(entry->d_name));
			counter++;
		}
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

void print_list(char** dirlist, size_t file_no)
{
	qsort(dirlist, file_no, sizeof(char*), is_less_than);

	for(size_t i = 0; i < file_no; i++)
		printf("%s\n", dirlist[i]);
}

int is_less_than(const void* a, const void* b)
{
	return strcmp(*(const char**) a, *(const char**) b);
}
