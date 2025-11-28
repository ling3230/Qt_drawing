#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QPen>
#include <QLineF>
#include <QRect>

class Shape {
public:
    virtual ~Shape() = default;

    void setStart(const QPoint& start) { m_start = start; }
    void setEnd(const QPoint& end) { m_end = end; }
    void setColor(const QColor& color) { m_color = color; }
    void setPenWidth(int width) { m_penWidth = width; }

    virtual void draw(QPainter& painter) = 0;
    virtual Shape* clone() const = 0;

protected:
    QPoint m_start;
    QPoint m_end;
    QColor m_color = Qt::black;
    int m_penWidth = 2;
};

#endif // SHAPE_H
