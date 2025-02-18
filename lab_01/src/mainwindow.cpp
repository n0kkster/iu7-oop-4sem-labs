#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadFrameBtn, &QPushButton::clicked, this, &MainWindow::onLoadBtnClicked);
}

void MainWindow::onLoadBtnClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выбрать файл", "", "*.txt");    
    if (filename.isNull())
        return;
    
    handleAction({.action = LOAD, .io_params = {filename.toStdString().c_str()}});
}

MainWindow::~MainWindow()
{
    delete ui;
}
