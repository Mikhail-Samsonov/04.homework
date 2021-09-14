#ifndef EDITOR_SHAPE_H
#define EDITOR_SHAPE_H

#include "publisher.h"

class IShape {
public:
    IShape() {
        ++id;
        set_id();
    }

    virtual ~IShape() = default;

    virtual void draw(std::ostream &out) = 0;

    void set_id() {
        id_elem = id;
    }

protected:
    static std::size_t id;
    std::size_t id_elem;
    std::shared_ptr<Publisher> publisher;
};

std::size_t IShape::id = 0;

class Line : public IShape {
public:
    Line(std::size_t id_doc, ZoomState *zoom, ColorState *color)
            : IShape() {
        publisher = publisher->create(id_doc, zoom, color, id_elem, m_name);
    };

    void draw(std::ostream &out) override {
        out << "I'm a " << m_name << " #" << id_elem << std::endl;
    }

private:
    std::string m_name = "line";
};

class Circle : public IShape {
public:
    Circle(std::size_t id_doc, ZoomState *zoom, ColorState *color)
            : IShape() {
        publisher = publisher->create(id_doc, zoom, color, id_elem, m_name);
    };


    void draw(std::ostream &out) override {
        out << "I'm a " << m_name << " #" << id_elem << std::endl;
    }

private:
    std::string m_name = "circle";
};

class Square : public IShape {
public:
    Square(std::size_t id_doc, ZoomState *zoom, ColorState *color)
            : IShape() {
        publisher = publisher->create(id_doc, zoom, color, id_elem, m_name);
    };

    void draw(std::ostream &out) override {
        out << "I'm a " << m_name << " #" << id_elem << std::endl;
    }

private:
    std::string m_name = "square";
};

#endif //EDITOR_SHAPE_H
