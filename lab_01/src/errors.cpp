#include "errors.h"

void handleError(QWidget *parent, err_code_e rc)
{
    switch (rc)
    {
        case ERROR_READING_FILE:
            QMessageBox::critical(parent, "Ошибка", "Ошибка чтения файла!");
            break;
        case ERROR_ALLOCATING_MEM:
            QMessageBox::critical(parent, "Ошибка", "Ошибка выделения памяти!");
            break;
        case ERROR_INVALID_PTR:
            QMessageBox::critical(parent, "Ошибка", "Некорректный указатель!");
            break;
        case ERROR_OPENING_FILE:
            QMessageBox::critical(parent, "Ошибка", "Ошибка открытия файла!");
            break;
        case ERROR_EMPTY_STRING:
            QMessageBox::critical(parent, "Ошибка", "Файл не должен содержать пустых строк!");
            break;
        case ERROR_READING_STRING:
            QMessageBox::critical(parent, "Ошибка", "Ошибка чтения строки!");
            break;
        case ERROR_NOT_A_NUMBER:
            QMessageBox::critical(parent, "Ошибка", "Ошибка парсинга числа из строки!");
            break;
        case ERROR_INVALID_POINTS_COUNT:
            QMessageBox::critical(parent, "Ошибка", "Некорректное количество точек!");
            break;
        case ERROR_INVALID_EDGES_COUNT:
            QMessageBox::critical(parent, "Ошибка", "Некорректное количество ребер!");
            break;
        default:
            break;
    }
}