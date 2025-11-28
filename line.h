#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape {
public:
    void draw(QPainter& painter) override {
        painter.setPen(QPen(m_color, m_penWidth));
        painter.drawLine(m_start, m_end);
    }

    Line* clone() const override {
        Line* newLine = new Line();
        newLine->setStart(m_start);
        newLine->setEnd(m_end);
        newLine->setColor(m_color);
        newLine->setPenWidth(m_penWidth);
        return newLine;
    }
};

#endif // LINE_H
