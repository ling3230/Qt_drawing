#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    void draw(QPainter& painter) override {
        painter.setPen(QPen(m_color, m_penWidth));
        painter.drawRect(QRect(m_start, m_end));
    }

    Rectangle* clone() const override {
        Rectangle* newRect = new Rectangle();
        newRect->setStart(m_start);
        newRect->setEnd(m_end);
        newRect->setColor(m_color);
        newRect->setPenWidth(m_penWidth);
        return newRect;
    }
};

#endif // RECTANGLE_H
