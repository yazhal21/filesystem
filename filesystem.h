#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50
#define MAX_CONTENT_LENGTH 1000

// Структура файла
typedef struct {
    char name[MAX_FILENAME_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    size_t size;
} File;

// Структура файловой системы
typedef struct {
    File files[MAX_FILES];
    int file_count;
} FileSystem;

/* Функции работы с файловой системой */
FILE* open_filesystem(const char* filename);
int close_filesystem(FILE* fs_file);

/* Функции работы с файлами внутри системы */
char* view_file(const char* target_filename);
int delete_file(const char* target_filename);
int create_new_file(FileSystem* fs, const char* filename, const char* content);
int modify_file(FileSystem* fs, const char* filename, const char* new_content);

/* Вспомогательные функции */
int initialize_filesystem(FileSystem* fs);
int read_file_content(FileSystem* fs, const char* filename, char* buffer);
void list_files(FileSystem* fs);

#endif /* FILESYSTEM_H */
