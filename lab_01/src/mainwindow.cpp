#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadFrameBtn, &QPushButton::clicked, this, &MainWindow::onLoadBtnClicked);
    connect(ui->saveFrameBtn, &QPushButton::clicked, this, &MainWindow::onSaveBtnClicked);
    connect(ui->applyShiftBtn, &QPushButton::clicked, this, &MainWindow::onShiftBtnClicked);
    connect(ui->applyScaleBtn, &QPushButton::clicked, this, &MainWindow::onScaleBtnClicked);
    connect(ui->applyRotateBtn, &QPushButton::clicked, this, &MainWindow::onRotateBtnClicked);
}

void MainWindow::onLoadBtnClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выбрать файл", "./models", "*.txt");
    if (filename.isNull())
        return;

    handleAction({.action = LOAD, .io_params = {filename.toStdString().c_str()}});
    handleAction({.action = DRAW, .draw_params = {ui->planeWidget}});
}

void MainWindow::onSaveBtnClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "./models", "*.txt");
    if (filename.isNull())
        return;

    handleAction({.action = SAVE, .io_params = {filename.toStdString().c_str()}});
}

void MainWindow::onShiftBtnClicked()
{
    double dx, dy, dz;
    bool ok;
    action_params_t action_params;
    morph_params_t morph_params;

    dx = ui->dxOffsetInput->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Величина сдвига по оси X должна быть вещественным числом.");
        return;
    }

    dy = ui->dyOffsetInput->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Величина сдвига по оси Y должна быть вещественным числом.");
        return;
    }

    dz = ui->dzOffsetInput->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Величина сдвига по оси Z должна быть вещественным числом.");
        return;
    }

    morph_params.shift_params = {dx, dy, dz};
    action_params.action = SHIFT;
    action_params.morph_params = morph_params;
    handleAction(action_params);

    action_params.action = DRAW;
    action_params.draw_params.plane = ui->planeWidget;
    
    handleAction(action_params);
}

void MainWindow::onScaleBtnClicked()
{
    double kx, ky, kz;
    double cx, cy, cz;
    bool ok;
    action_params_t action_params;
    morph_params_t morph_params;

    cx = ui->centerXScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата X центра масштабирования должна быть вещественным числом.");
        return;
    }

    cy = ui->centerYScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата Y центра масштабирования должна быть вещественным числом.");
        return;
    }

    cz = ui->centerZScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата Z центра масштабирования должна быть вещественным числом.");
        return;
    }

    kx = ui->kXScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Коэффициент масштабирования по оси X должен быть вещественным числом.");
        return;
    }

    ky = ui->kYScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Коэффициент масштабирования по оси Y должен быть вещественным числом.");
        return;
    }

    kz = ui->kZScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Коэффициент масштабирования по оси Z должен быть вещественным числом.");
        return;
    }

    morph_params.scale_params = {cx, cy, cz, kx, ky, kz};
    action_params.action = SCALE;
    action_params.morph_params = morph_params;
    handleAction(action_params);

    action_params.action = DRAW;
    action_params.draw_params.plane = ui->planeWidget;
    
    handleAction(action_params);

}

void MainWindow::onRotateBtnClicked()
{
    double cx, cy, cz;
    double angleX, angleY, angleZ;
    bool ok;
    action_params_t action_params;
    morph_params_t morph_params;

    cx = ui->centerXRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата X центра вращения должна быть вещественным числом.");
        return;
    }

    cy = ui->centerYRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата Y центра вращения должна быть вещественным числом.");
        return;
    }

    cz = ui->centerZRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Координата Z центра вращения должна быть вещественным числом.");
        return;
    }

    angleX = ui->angleXRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Угол вращения по оси X должен быть вещественным числом.");
        return;
    }

    angleY = ui->angleYRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Угол вращения по оси Y должен быть вещественным числом.");
        return;
    }

    angleZ = ui->angleZRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Угол вращения по оси Z должен быть вещественным числом.");
        return;
    }

    morph_params.rotation_params = {cx, cy, cz, angleX, angleY, angleZ};
    action_params.action = ROTATE;
    action_params.morph_params = morph_params;
    handleAction(action_params);

    action_params.action = DRAW;
    action_params.draw_params.plane = ui->planeWidget;
    
    handleAction(action_params);
}

MainWindow::~MainWindow()
{
    delete ui;
}
