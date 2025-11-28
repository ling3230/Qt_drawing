#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"  // 新增

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void onLineButtonClicked();
    void onRectButtonClicked();
    void onCircleButtonClicked();
    void onFreePenButtonClicked();
    void onColorButtonClicked();
    void onUndoButtonClicked();
    void onSaveButtonClicked();
    void onShapeCountChanged(int count);  // 新增：响应形状数量变化
    // ... 其他的槽函数 ...
    void onPenWidthChanged(int width);  // 新增

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::MainWindow *ui;
    QPixmap m_background;
    CanvasWidget* m_canvasWidget;  // 新增：画布控件指针
};

#endif // MAINWINDOW_H
