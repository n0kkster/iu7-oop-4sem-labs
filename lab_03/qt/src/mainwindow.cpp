#include "../inc/mainwindow.h"

#include "../../commands/camera/CameraCommand.h"
#include "../../commands/load/LoadCommand.h"
#include "../../commands/object/ObjectCommand.h"
#include "../../commands/scene/SceneCommand.h"
#include "../../facade/Facade.h"
#include "../../factories/draw/DrawSolution.h"
#include "../../factories/draw/qt/QtDrawFactory.h"
#include "../../ids/ids.h"
#include "../../managers/ManagerSolution.h"
#include "../../out/ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <filesystem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->applyShiftBtn, &QPushButton::clicked, this, &MainWindow::onShiftBtnClicked);
    connect(ui->applyScaleBtn, &QPushButton::clicked, this, &MainWindow::onScaleBtnClicked);
    connect(ui->applyRotateBtn, &QPushButton::clicked, this, &MainWindow::onRotateBtnClicked);
    connect(ui->loadModelBtn, &QPushButton::clicked, this, &MainWindow::onLoadModelBtnClicked);

    createScene(ui->planeWidget);

    m_objects = 0;

    CameraId id = CameraId::DefaultCameraId;
    std::shared_ptr<BaseCommand> addCameraCommand = std::make_shared<AddCameraCommand>(id);
    m_facade.execute(addCameraCommand);

    std::shared_ptr<BaseCommand> setActiveCameraCommand = std::make_shared<SetActiveCameraCommand>(id);
    m_facade.execute(setActiveCameraCommand);

    insertRow(m_objects++, "Камера", {0, 0, 0}, "Обыкновенная");
}

void MainWindow::onLoadModelBtnClicked()
{
    QString qFilename = QFileDialog::getOpenFileName(
        this, "Открыть файл", "", "Текстовые файлы (*.txt);;CSV файлы (*.csv);;OBJ файлы (*.obj)");

    if (qFilename.isEmpty())
        return;

    std::string filename = qFilename.toStdString();

    InternalRepresentationId repr = static_cast<InternalRepresentationId>(ui->modelReprList->currentIndex());

    try
    {
        std::shared_ptr<BaseCommand> loadCommand = std::make_shared<CarcassLoadCommand>(repr, filename);
        m_facade.execute(loadCommand);
        std::shared_ptr<BaseCommand> drawCommand = std::make_shared<DrawSceneCommand>();
        m_facade.execute(drawCommand);
        insertRow(m_objects++, std::filesystem::path(filename).filename(), {0, 0, 0}, "Каркас");
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
}

void MainWindow::onShiftBtnClicked()
{
    double dx, dy, dz;
    bool ok;

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

    MoveParams params{dx, dy, dz};

    getSelectedObjects();

    for (const auto id : m_selected)
    {
        std::shared_ptr<BaseCommand> moveCommand = std::make_shared<MoveObjectCommand>(id, params);
        m_facade.execute(moveCommand);
    }

    std::shared_ptr<BaseCommand> drawCommand = std::make_shared<DrawSceneCommand>();
    m_facade.execute(drawCommand);
}

void MainWindow::onScaleBtnClicked()
{
    double kx, ky, kz;
    double cx, cy, cz;
    bool ok;

    cx = ui->centerXScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата X центра масштабирования должна быть вещественным числом.");
        return;
    }

    cy = ui->centerYScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата Y центра масштабирования должна быть вещественным числом.");
        return;
    }

    cz = ui->centerZScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата Z центра масштабирования должна быть вещественным числом.");
        return;
    }

    kx = ui->kXScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Коэффициент масштабирования по оси X должен быть вещественным числом.");
        return;
    }

    ky = ui->kYScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Коэффициент масштабирования по оси Y должен быть вещественным числом.");
        return;
    }

    kz = ui->kZScale->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Коэффициент масштабирования по оси Z должен быть вещественным числом.");
        return;
    }

    ScaleParams params{kx, ky, kz};

    getSelectedObjects();

    for (const auto id : m_selected)
    {
        std::shared_ptr<BaseCommand> scaleCommand = std::make_shared<ScaleObjectCommand>(id, params);
        m_facade.execute(scaleCommand);
    }

    std::shared_ptr<BaseCommand> drawCommand = std::make_shared<DrawSceneCommand>();
    m_facade.execute(drawCommand);
}

void MainWindow::onRotateBtnClicked()
{
    double cx, cy, cz;
    double angleX, angleY, angleZ;
    bool ok;

    cx = ui->centerXRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата X центра вращения должна быть вещественным числом.");
        return;
    }

    cy = ui->centerYRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата Y центра вращения должна быть вещественным числом.");
        return;
    }

    cz = ui->centerZRotate->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, "Ошибка",
                              "Координата Z центра вращения должна быть вещественным числом.");
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

    angleX = qDegreesToRadians(angleX);
    angleY = qDegreesToRadians(angleY);
    angleZ = qDegreesToRadians(angleZ);

    RotationParams params{angleX, angleY, angleZ};

    getSelectedObjects();

    for (const auto id : m_selected)
    {
        std::shared_ptr<BaseCommand> rotateCommand = std::make_shared<RotateObjectCommand>(id, params);
        m_facade.execute(rotateCommand);
    }

    std::shared_ptr<BaseCommand> drawCommand = std::make_shared<DrawSceneCommand>();
    m_facade.execute(drawCommand);
}

#include <QDebug>

void MainWindow::createScene(QWidget *parent)
{
    const int w = ui->planeWidget->width();
    const int h = ui->planeWidget->height();

    auto m_scene = std::make_shared<QGraphicsScene>(0, 0, w, h, parent);
    m_scene->setSceneRect(QRect{ 0, 0, w, h });
    m_scene->setBackgroundBrush(QColor::fromRgb(39, 40, 41));

    ui->planeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->planeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->planeWidget->setScene(m_scene.get());

    std::unique_ptr<BasePainter> painter = DrawSolution::createPainter<QtDrawFactory>(m_scene);
    auto drawManager = ManagerSolution::getDrawManager();

    drawManager->setPainter(std::move(painter));
}

void MainWindow::getSelectedObjects()
{
    auto selected = ui->tableWidget->selectedItems();

    m_selected.clear();

    for (const auto el : selected)
    {
        if (el->column() == 0)
        {
            m_selected.push_back(el->text().toULong());
        }
    }
}

void MainWindow::insertRow(size_t id, const std::string &name, const Vertex &center, const std::string &type)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem{ QString::number(id) });
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem{ QString(name.c_str()) });
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2,
                             new QTableWidgetItem{ "(" + QString::number(center.getX()) + "; "
                                                   + QString::number(center.getY()) + "; "
                                                   + QString::number(center.getZ()) + ")" });
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem{ QString(type.c_str()) });
}

MainWindow::~MainWindow()
{
    delete ui;
}
