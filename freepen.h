#ifndef FREEPEN_H
#define FREEPEN_H

#include "shape.h"
#include <QVector>

class FreePen : public Shape {
public:
    FreePen() = default;

    void addPoint(const QPoint& point) {
        m_points.append(point);
    }

    void draw(QPainter& painter) override {
        painter.setPen(QPen(m_color, m_penWidth));

        if (m_points.size() > 1) {
            for (int i = 1; i < m_points.size(); ++i) {
                painter.drawLine(m_points[i-1], m_points[i]);
            }
        }
    }

    FreePen* clone() const override {
        FreePen* newPen = new FreePen();
        newPen->m_points = this->m_points;
        newPen->setColor(m_color);
        newPen->setPenWidth(m_penWidth);
        return newPen;
    }

private:
    QVector<QPoint> m_points;
};

#endif // FREEPEN_H
