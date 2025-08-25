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
