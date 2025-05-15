#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../facade/Facade.h"

#include <memory>
#include <QGraphicsScene>
#include <QMainWindow>
#include <vector>

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
    void contextMenuRequested(const QPoint &pos);
    void deleteObjectRequested();
    void setActiveCamRequested();
    void composeRequested();
    void addCameraBtnClicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QGraphicsScene> m_scene;
    Facade m_facade;

    void createScene(QWidget *parent);
    void insertRow(size_t id, const std::string &name, const Vertex &center, const std::string &type);
    void updateCenter(size_t id, const Vertex &center);
    void getSelectedObjects();

    size_t m_objects;
    size_t m_activeCamId;
    std::vector<size_t> m_selected;
};
#endif /* MAINWINDOW_H */
