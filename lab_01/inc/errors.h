#ifndef ERRORS_H
#define ERRORS_H

#include <QWidget>
#include <QMessageBox>

typedef enum
{
    ERROR_SUCCESS,
    ERROR_READING_FILE,
    ERROR_ALLOCATING_MEM,
    ERROR_INVALID_PTR,
    ERROR_OPENING_FILE,
    ERROR_READING_STRING,
    ERROR_EMPTY_STRING,
    ERROR_NOT_A_NUMBER
} err_code_e;

void handleError(QWidget *parent, err_code_e rc);

#endif /* ERRORS_H */
