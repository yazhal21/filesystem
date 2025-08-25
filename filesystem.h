#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_FILES 100
#define MAX_PATH_LENGTH 100
#define MAX_CONTENT_LENGTH 1000

typedef struct {
    char path[MAX_PATH_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    size_t size;
} FileEntry;

typedef struct {
    FileEntry entries[MAX_FILES];
    size_t count;
} FileSystem;

/* Базовые операции файловой системы */
int initialize_filesystem(FileSystem* fs);
int create_new_file(FileSystem* fs, const char* path, const char* content);
int read_file_content(FileSystem* fs, const char* path, char* buffer);
int modify_file(FileSystem* fs, const char* path, const char* new_content);
int delete_file(FileSystem* fs, const char* path);
void list_files(FileSystem* fs);

/* Загрузка/сохранение/освобождение */
int  fs_load(const char* fname, FileSystem* fs);
int  fs_save(const char* fname, const FileSystem* fs);
void fs_free(FileSystem* fs);

/* CRUD */
int  fs_select(const FileSystem* fs, const char* path, char** out_content);
int  fs_insert(FileSystem* fs, const char* path);
int  fs_update(FileSystem* fs, const char* path, const char* new_content);
int  fs_delete(FileSystem* fs, const char* path);

/* Новые функции */
int    fs_crypto(FileSystem* fs, const char* path, const char* key);
int    fs_decrypto(FileSystem* fs, const char* path, const char* key);
size_t fs_count(const FileSystem* fs);
int    fs_rename(FileSystem* fs, const char* old_path, const char* new_path);

#endif /* FILESYSTEM_H */
