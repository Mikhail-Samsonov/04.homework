#ifndef EDITOR_DOCUMENT_H
#define EDITOR_DOCUMENT_H

#include "publisher.h"
#include <unordered_set>
#include "shape.h"
#include "display.h"

class Document {
public:
    Document() {
        ++id;
        set_id();
    }

    void set_color(Color color) {
        m_color.set_color(color);
    }

    void set_zoom(std::size_t zoom) {
        m_zoom.set_zoom(zoom);
    }

    const std::unique_ptr<IShape> &add_line() {
        auto[it, inserted] = m_shapes.emplace(std::make_unique<Line>(id_doc, &m_zoom, &m_color));
        assert(inserted);
        return *it;
    }

    const std::unique_ptr<IShape> &add_circle() {
        auto[it, inserted] = m_shapes.emplace(std::make_unique<Circle>(id_doc, &m_zoom, &m_color));
        assert(inserted);
        return *it;
    }

    const std::unique_ptr<IShape> &add_square() {
        auto[it, inserted] = m_shapes.emplace(std::make_unique<Square>(id_doc, &m_zoom, &m_color));
        assert(inserted);
        return *it;
    }

    bool remove_shape(const std::unique_ptr<IShape> &shape) {
        std::size_t removed = m_shapes.erase(shape);
        if (removed == 0)
            return false;
        return true;
    }

    void draw(IDisplay &d) {
        for (const auto &i: m_shapes) {
            d.display(*i);
        }
    }

    std::size_t get_id() const {
        return id_doc;
    }

    void set_id() {
        id_doc = id;
    }

private:
    static std::size_t id;
    std::size_t id_doc;
    ZoomState m_zoom;
    ColorState m_color;
    std::unordered_set<std::unique_ptr<IShape> > m_shapes;
};

std::size_t Document::id = 0;

#endif //EDITOR_DOCUMENT_H
