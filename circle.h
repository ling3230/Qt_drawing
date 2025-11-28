#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    void draw(QPainter& painter) override {
        painter.setPen(QPen(m_color, m_penWidth));
        int radius = QLineF(m_start, m_end).length();
        painter.drawEllipse(m_start, radius, radius);
    }

    Circle* clone() const override {
        Circle* newCircle = new Circle();
        newCircle->setStart(m_start);
        newCircle->setEnd(m_end);
        newCircle->setColor(m_color);
        newCircle->setPenWidth(m_penWidth);
        return newCircle;
    }
};

#endif // CIRCLE_H
