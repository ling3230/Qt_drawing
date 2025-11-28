#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include <memory>
#include "shape.h"
#include "drawcommand.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    // 设置当前绘图工具
    void setCurrentShapeType(int type) { m_currentShapeType = type; }
    void setCurrentColor(const QColor& color) { m_currentColor = color; }
    void setPenWidth(int width) { m_penWidth = width; }

    // 操作函数
    void undo();
    bool saveImage(const QString& fileName);

signals:
    // 用于通知主窗口更新状态
    void shapeCountChanged(int count);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<std::shared_ptr<Shape>> m_shapes;
    std::vector<std::unique_ptr<DrawCommand>> m_commands;
    std::vector<std::unique_ptr<DrawCommand>> m_undoneCommands;

    std::shared_ptr<Shape> m_currentShape = nullptr;
    bool m_isDrawing = false;

    QColor m_currentColor = Qt::black;
    int m_penWidth = 2;
    int m_currentShapeType = 0; // 0: Line, 1: Rectangle, 2: Circle, 3: FreePen
};

#endif // CANVASWIDGET_H
