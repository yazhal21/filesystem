#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"

int main() {
    printf("=== Демонстрация файловой системы ===\n\n");
    
    // 1. Открываем/создаем файловую систему
    FILE* fs_file = open_filesystem("pseudofs.disk");
    if (fs_file == NULL) {
        printf("Ошибка открытия файловой системы!\n");
        return 1;
    }
    
    // 2. Инициализируем систему в памяти
    FileSystem fs;
    initialize_filesystem(&fs);
    
    // 3. Создаем файлы
    printf("\n1. Создаем файлы...\n");
    create_new_file(&fs, "document.txt", "Это содержимое документа");
    create_new_file(&fs, "readme.txt", "Инструкция по использованию");
    create_new_file(&fs, "config.cfg", "setting=value\nmode=debug");
    
    // 4. Просматриваем список файлов
    printf("\n2. Список файлов:\n");
    list_files(&fs);
    
    // 5. Просматриваем содержимое файла
    printf("\n3. Просмотр содержимого:\n");
    char* content = view_file("document.txt");
    if (content != NULL) {
        printf("Содержимое document.txt: %s\n", content);
        free(content); // Не забываем освободить память
    }
    
    // 6. Изменяем файл
    printf("\n4. Изменяем файл...\n");
    modify_file(&fs, "document.txt", "Обновленное содержимое документа");
    
    // 7. Проверяем изменение
    content = view_file("document.txt");
    if (content != NULL) {
        printf("Новое содержимое: %s\n", content);
        free(content);
    }
    
    // 8. Удаляем файл
    printf("\n5. Удаляем файл...\n");
    int result = delete_file("config.cfg");
    if (result == 0) {
        printf("Файл config.cfg успешно удален\n");
    }
    
    // 9. Финальный список
    printf("\n6. Финальный список файлов:\n");
    list_files(&fs);
    
    // 10. Закрываем файловую систему
    printf("\n7. Закрываем систему...\n");
    close_filesystem(fs_file);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_PARAMS 10
#define MAX_PARAM_LENGTH 50

// Функция для разделения строки на параметры
int parse_command(char* input, char params[][MAX_PARAM_LENGTH]) {
    int count = 0;
    char* token = strtok(input, " \n");
    
    while (token != NULL && count < MAX_PARAMS) {
        strncpy(params[count], token, MAX_PARAM_LENGTH - 1);
        params[count][MAX_PARAM_LENGTH - 1] = '\0';
        count++;
        token = strtok(NULL, " \n");
    }
    
    return count;
}

// 1.1 Создание файла
void create_new_file(char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        printf("Файл '%s' создан успешно\n", filename);
        fclose(file);
    } else {
        printf("Ошибка при создании файла '%s'\n", filename);
    }
}

// 1.2 Удаление файла
void delete_file(char* filename) {
    if (remove(filename) == 0) {
        printf("Файл '%s' удален успешно\n", filename);
    } else {
        printf("Ошибка при удалении файла '%s'\n", filename);
    }
}

// 1.3 Изменение файла
void modify_file(char* filename) {
    printf("Введите содержимое файла (Ctrl+D для завершения):\n");
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла '%s'\n", filename);
        return;
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        fputs(buffer, file);
    }
    
    fclose(file);
    printf("Файл '%s' изменен успешно\n", filename);
}

// 1.4 Просмотр файла
void view_file(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла '%s'\n", filename);
        return;
    }
    
    printf("Содержимое файла '%s':\n", filename);
    printf("----------------------------------------\n");
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    printf("----------------------------------------\n");
    fclose(file);
}

// Функция помощи
void show_help() {
    printf("\nДоступные команды:\n");
    printf("создать <путь_до_файла>    - Создать файл\n");
    printf("удалить <путь_до_файла>    - Удалить файл\n");
    printf("изменить <путь_до_файла>   - Изменить файл\n");
    printf("посмотреть <путь_до_файла> - Просмотреть файл\n");
    printf("помощь                     - Показать справку\n");
    printf("выход                      - Выйти из программы\n\n");
}

int main() {
    printf("========================================\n");
    printf("    Файловая система FSCmd v1.0\n");
    printf("========================================\n");
    show_help();
    
    char input[MAX_COMMAND_LENGTH];
    char params[MAX_PARAMS][MAX_PARAM_LENGTH];
    
    while (1) {
        printf("> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Удаляем символ новой строки
        input[strcspn(input, "\n")] = 0;
        
        int param_count = parse_command(input, params);
        
        if (param_count == 0) {
            continue;
        }
        
        // Обработка команд
        if (strcmp(params[0], "выход") == 0) {
            printf("Завершение работы...\n");
            break;
        }
        else if (strcmp(params[0], "помощь") == 0) {
            show_help();
        }
        else if (strcmp(params[0], "создать") == 0) {
            if (param_count >= 2) {
                create_new_file(params[1]);
            } else {
                printf("Ошибка: укажите путь к файлу\n");
            }
        }
        else if (strcmp(params[0], "удалить") == 0) {
            if (param_count >= 2) {
                delete_file(params[1]);
            } else {
                printf("Ошибка: укажите путь к файлу\n");
            }
        }
        else if (strcmp(params[0], "изменить") == 0) {
            if (param_count >= 2) {
                modify_file(params[1]);
            } else {
                printf("Ошибка: укажите путь к файлу\n");
            }
        }
        else if (strcmp(params[0], "посмотреть") == 0) {
            if (param_count >= 2) {
                view_file(params[1]);
            } else {
                printf("Ошибка: укажите путь к файлу\n");
            }
        }
        else {
            printf("Неизвестная команда: '%s'\n", params[0]);
            printf("Введите 'помощь' для списка команд\n");
        }
    }
    
    return 0;
}
