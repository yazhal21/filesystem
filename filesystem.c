#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "filesystem.h"

/* 1.1. Открыть или создать файл файловой системы */
FILE* open_filesystem(const char* filename) {
    FILE* file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Error: Cannot open filesystem '%s'\n", filename);
        return NULL;
    }
    printf("Filesystem '%s' opened successfully\n", filename);
    return file;
}

/* 1.2. Посмотреть содержимое файла */
char* view_file(const char* target_filename) {
    FILE* fs = fopen(FILESYSTEM_NAME, "r");
    if (fs == NULL) {
        printf("Error: Filesystem not found\n");
        return NULL;
    }

    char line[256];
    bool found = false;
    static char content[MAX_CONTENT_LEN] = {0};
    content[0] = '\0';

    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = '\0';

        if (!found) {
            if (strcmp(line, target_filename) == 0) {
                found = true;
            }
        } else {
            if (line[0] == '/') {
                break;
            }
            strcat(content, line);
            strcat(content, "\n");
        }
    }

    fclose(fs);
    
    if (!found) {
        printf("Error: File '%s' not found\n", target_filename);
        return NULL;
    }
    
    return content;
}

/* 1.3. Удалить файл из файловой системы */
int delete_file(const char* target_filename) {
    FILE* fs = fopen(FILESYSTEM_NAME, "r");
    if (fs == NULL) {
        printf("Error: Filesystem not found\n");
        return -1;
    }

    // Читаем все строки
    char** lines = NULL;
    char line[256];
    int line_count = 0;
    int start_index = -1;
    int end_index = -1;

    while (fgets(line, sizeof(line), fs)) {
        lines = realloc(lines, (line_count + 1) * sizeof(char*));
        lines[line_count] = strdup(line);
        
        if (start_index == -1) {
            char temp[256];
            strcpy(temp, line);
            temp[strcspn(temp, "\n")] = '\0';
            if (strcmp(temp, target_filename) == 0) {
                start_index = line_count;
            }
        }
        
        line_count++;
    }
    fclose(fs);

    if (start_index == -1) {
        printf("Error: File '%s' not found\n", target_filename);
        for (int i = 0; i < line_count; i++) free(lines[i]);
        free(lines);
        return -1;
    }

    // Ищем конец файла
    for (end_index = start_index + 1; end_index < line_count; end_index++) {
        if (lines[end_index][0] == '/') {
            break;
        }
    }

    // Перезаписываем файл
    fs = fopen(FILESYSTEM_NAME, "w");
    if (fs == NULL) {
        printf("Error: Cannot write to filesystem\n");
        for (int i = 0; i < line_count; i++) free(lines[i]);
        free(lines);
        return -1;
    }

    for (int i = 0; i < line_count; i++) {
        if (i < start_index || i > end_index) {
            fputs(lines[i], fs);
        }
        free(lines[i]);
    }
    free(lines);

    fclose(fs);
    printf("File '%s' deleted successfully\n", target_filename);
    return 0;
}

// Дополнительные функции для удобства
int create_file(const char* filename, const char* content) {
    FILE* fs = fopen(FILESYSTEM_NAME, "a");
    if (fs == NULL) {
        return -1;
    }
    
    fprintf(fs, "%s\n", filename);
    fprintf(fs, "%s\n", content);
    fprintf(fs, "/\n");
    
    fclose(fs);
    return 0;
}

void list_files() {
    FILE* fs = fopen(FILESYSTEM_NAME, "r");
    if (fs == NULL) {
        printf("No files found\n");
        return;
    }

    char line[256];
    printf("Files in filesystem:\n");
    
    while (fgets(line, sizeof(line), fs)) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] != '/' && strlen(line) > 0) {
            // Проверяем, что это не содержимое файла
            char next_line[256];
            if (fgets(next_line, sizeof(next_line), fs) != NULL) {
                if (next_line[0] != '/') {
                    printf("  - %s\n", line);
                }
                fseek(fs, -strlen(next_line), SEEK_CUR);
            }
        }
    }
    
    fclose(fs);
}
