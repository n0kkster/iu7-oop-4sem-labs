#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../facade/Facade.h"

#include <memory>
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadModelBtnClicked();
    void onShiftBtnClicked();
    void onScaleBtnClicked();
    void onRotateBtnClicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QGraphicsScene> m_scene;
    Facade m_facade;

    void createScene(QWidget *parent);
};
#endif /* MAINWINDOW_H */
