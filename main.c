#include <stdio.h>
#include "filesystem.h"

int main() {
    FileSystem fs;
    
    // Инициализация файловой системы
    if (initialize_filesystem(&fs) != 0) {
        printf("Ошибка инициализации файловой системы!\n");
        return 1;
    }
    
    printf("Демонстрация работы файловой системы:\n\n");
    
    // Создание файлов
    printf("1. Создаем файлы...\n");
    create_new_file(&fs, "readme.txt", "Это файл с инструкциями");
    create_new_file(&fs, "config.cfg", "setting=value\nmode=debug");
    create_new_file(&fs, "hello.txt", "Hello, World!");
    
    // Вывод списка файлов
    list_files(&fs);
    printf("\n");
    
    // Чтение содержимого файла
    printf("2. Читаем содержимое файла hello.txt:\n");
    char buffer[MAX_CONTENT_LENGTH];
    if (read_file_content(&fs, "hello.txt", buffer) == 0) {
        printf("Содержимое: %s\n", buffer);
    } else {
        printf("Файл не найден!\n");
    }
    printf("\n");
    
    // Изменение файла
    printf("3. Изменяем файл hello.txt...\n");
    modify_file(&fs, "hello.txt", "Hello, Modified World!");
    
    // Проверяем изменение
    printf("Проверяем изменение:\n");
    if (read_file_content(&fs, "hello.txt", buffer) == 0) {
        printf("Новое содержимое: %s\n", buffer);
    }
    printf("\n");
    
    // Удаление файла
    printf("4. Удаляем файл config.cfg...\n");
    delete_file(&fs, "config.cfg");
    
    // Финальный список файлов
    printf("Финальный список файлов:\n");
    list_files(&fs);
    
    return 0;
}
