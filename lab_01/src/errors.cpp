#include <QMessageBox>
#include "errors.h"

void handleError(err_code_e rc)
{
    switch (rc)
    {
        case ERROR_READING_FILE:
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка чтения файла!");
            break;
        case ERROR_ALLOCATING_MEM:
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка выделения памяти!");
            break;
        case ERROR_INVALID_PTR:
            QMessageBox::critical(nullptr, "Ошибка", "Некорректный указатель!");
            break;
        case ERROR_OPENING_FILE:
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка открытия файла!");
            break;
        case ERROR_EMPTY_STRING:
            QMessageBox::critical(nullptr, "Ошибка", "Файл не должен содержать пустых строк!");
            break;
        case ERROR_READING_STRING:
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка чтения строки!");
            break;
        case ERROR_NOT_A_NUMBER:
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка парсинга числа из строки!");
            break;
        case ERROR_INVALID_POINTS_COUNT:
            QMessageBox::critical(nullptr, "Ошибка", "Некорректное количество точек!");
            break;
        case ERROR_INVALID_EDGES_COUNT:
            QMessageBox::critical(nullptr, "Ошибка", "Некорректное количество ребер!");
            break;
        case ERROR_INVALID_EDGE:
            QMessageBox::critical(nullptr, "Ошибка", "Модель содержит некорректные ребра!");
            break;
        case ERROR_INVALID_ACTION:
            QMessageBox::critical(nullptr, "Ошибка", "Выбрано некорректное действие!");
            break;
        default:
            break;
    }
}