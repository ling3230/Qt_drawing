#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include "shape.h"
#include <memory>
#include <vector>

class DrawCommand {
public:
    virtual ~DrawCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddShapeCommand : public DrawCommand {
public:
    AddShapeCommand(std::shared_ptr<Shape> shape,
                    std::vector<std::shared_ptr<Shape>>& shapes)
        : m_shape(shape), m_shapes(shapes) {}

    void execute() override {
        m_shapes.push_back(m_shape);
    }

    void undo() override {
        if (!m_shapes.empty() && m_shapes.back() == m_shape) {
            m_shapes.pop_back();
        }
    }

private:
    std::shared_ptr<Shape> m_shape;
    std::vector<std::shared_ptr<Shape>>& m_shapes;
};

#endif // DRAWCOMMAND_H
