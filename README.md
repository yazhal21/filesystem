# Халикова 0907-32

# Документация

`open_filesystem` — открыть или создать файл файловой системы.

**Параметры:** const char* filename — имя файла файловой системы.

**Возвращаемое значение:**
- FILE* — указатель на открытый файл.
- NULL — в случае ошибки.

**Пример:**
`FILE* fs = open_filesystem("pseudofs.disk");`

`view_file` — просмотреть содержимое файла.

**Параметры:** const char* target_filename — имя искомого файла.

**Возвращаемое значение:**
- char* — содержимое файла.
- NULL — если файл не найден.

**Пример:** `char* content = view_file("document.txt");`

`delete_file` — удалить файл из файловой системы.

**Параметры:** const char* target_filename — имя файла для удаления.

**Возвращаемое значение:**
- int — 0 при успехе.
- -1 — при ошибке.

**Пример:** `int result = delete_file("old_file.txt");`

`create_new_file` — создает новый файл в файловой системе.

**Параметры:**
- FileSystem* fs — указатель на структуру файловой системы.
- const char* filename — имя создаваемого файла.
- const char* content — содержимое файла.

**Возвращаемое значение:** int — 0 при успешном создании, -1 при ошибке.

**Пример использования:**
```
FileSystem fs;
initialize_filesystem(&fs);
create_new_file(&fs, "test.txt", "Hello World!");
