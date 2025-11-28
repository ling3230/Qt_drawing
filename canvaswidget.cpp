#include "canvaswidget.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "freepen.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setAutoFillBackground(true);

    // 设置背景自动填充为false，让样式表背景显示
    setAutoFillBackground(false);

    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground, false);
}

void CanvasWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;

        // 根据当前选择的形状类型创建对应的形状对象
        switch (m_currentShapeType) {
        case 0: m_currentShape = std::make_shared<Line>(); break;
        case 1: m_currentShape = std::make_shared<Rectangle>(); break;
        case 2: m_currentShape = std::make_shared<Circle>(); break;
        case 3: m_currentShape = std::make_shared<FreePen>(); break;
        }

        m_currentShape->setStart(event->pos());
        m_currentShape->setEnd(event->pos());
        m_currentShape->setColor(m_currentColor);
        m_currentShape->setPenWidth(m_penWidth);

        // 如果是自由画笔，添加第一个点
        if (m_currentShapeType == 3) {
            if (auto freePen = std::dynamic_pointer_cast<FreePen>(m_currentShape)) {
                freePen->addPoint(event->pos());
            }
        }
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent* event) {
    if (m_isDrawing && m_currentShape) {
        if (m_currentShapeType == 3) {
            // 自由画笔：持续添加点
            if (auto freePen = std::dynamic_pointer_cast<FreePen>(m_currentShape)) {
                freePen->addPoint(event->pos());
            }
        } else {
            // 其他形状：更新终点
            m_currentShape->setEnd(event->pos());
        }
        update(); // 触发重绘
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isDrawing && m_currentShape) {
        // 自由画笔：添加最后一个点
        if (m_currentShapeType == 3) {
            if (auto freePen = std::dynamic_pointer_cast<FreePen>(m_currentShape)) {
                freePen->addPoint(event->pos());
            }
        }

        m_isDrawing = false;

        // 创建并执行命令
        auto command = std::make_unique<AddShapeCommand>(m_currentShape, m_shapes);
        command->execute();
        m_commands.push_back(std::move(command));

        // 清空重做栈
        m_undoneCommands.clear();

        // 发出信号通知形状数量变化
        emit shapeCountChanged(m_shapes.size());

        m_currentShape = nullptr;
        update();
    }
}

void CanvasWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // 绘制所有已完成的形状
    for (const auto& shape : m_shapes) {
        shape->draw(painter);
    }

    // 绘制当前正在绘制的形状
    if (m_currentShape) {
        m_currentShape->draw(painter);
    }
}

void CanvasWidget::undo() {
    if (!m_commands.empty()) {
        auto command = std::move(m_commands.back());
        m_commands.pop_back();
        command->undo();
        m_undoneCommands.push_back(std::move(command));

        // 发出信号通知形状数量变化
        emit shapeCountChanged(m_shapes.size());

        update();
    }
}

bool CanvasWidget::saveImage(const QString& fileName) {
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    return pixmap.save(fileName, "PNG");
}
