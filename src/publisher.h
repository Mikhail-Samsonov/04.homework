#ifndef EDITOR_PUBLISHER_H
#define EDITOR_PUBLISHER_H

#include <list>
#include <memory>

#include "color.h"

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;
};

class Observable {
public:
    virtual  ~Observable() = default;

    virtual void subscribe(const std::shared_ptr<Observer> &obs) = 0;
};

class BaseObservable : public Observable {
public:
    void subscribe(const std::shared_ptr<Observer> &obs) override {
        m_subscribers.emplace_back(obs);
    }

    void notify() {
        auto it = m_subscribers.begin();
        while (it != m_subscribers.end()) {
            auto ptr = it->lock();
            if (ptr) {
                ptr->update();
                ++it;
            } else {
                m_subscribers.erase(it++);
            }
        }
    }

private:
    std::list<std::weak_ptr<Observer>> m_subscribers;
};

class ColorState : public BaseObservable {
public:
    void set_color(Color color) {
        m_color = color;
        notify();
    }

    [[nodiscard]] Color get_color() const {
        return m_color;
    }

private:
    Color m_color{Color::black};
};

class ZoomState : public BaseObservable {
public:
    void set_zoom(std::size_t zoom) {
        m_zoom = zoom;
        notify();
    }

    [[nodiscard]] std::size_t get_zoom() const {
        return m_zoom;
    }

private:
    std::size_t m_zoom{100};
};

class Publisher : public Observer, public std::enable_shared_from_this<Publisher> {
public:
    explicit Publisher(std::size_t id_doc_, std::size_t id_elem_, std::string &elem_typename_)
            : id_doc(id_doc_), id_elem(id_elem_), elem_typename(elem_typename_) {
    };

    std::shared_ptr<Publisher>
    static
    create(std::size_t id_doc_, ZoomState *zoom_, ColorState *color_, std::size_t id_elem_,
           std::string &elem_typename_) {
        auto ptr = std::make_shared<Publisher>(id_doc_, id_elem_, elem_typename_);
        ptr->setZoomState(zoom_);
        ptr->setColorState(color_);
        return ptr;
    }

    void update() override {
        std::size_t zoom = m_zoomState->get_zoom();
        if (zoom != m_zoom) {
            std::cout << "switch zoom for document #" << id_doc << " object #" << id_elem << " typename -> "
                      << elem_typename << " to " << zoom << std::endl;
            m_zoom = zoom;
        }

        Color color = m_colorState->get_color();
        if (color != m_color) {
            std::cout << "switch color for document #" << id_doc << " object #" << id_elem << " typename -> "
                      << elem_typename << " to " << color << std::endl;
            m_color = color;
        }
    }

private:

    void setZoomState(ZoomState *zoom) {
        m_zoomState = zoom;
        m_zoomState->subscribe(shared_from_this());
    }

    void setColorState(ColorState *color) {
        m_colorState = color;
        m_colorState->subscribe(shared_from_this());
    }

    std::size_t id_doc;
    std::size_t id_elem;
    std::string elem_typename;

    std::size_t m_zoom{100};
    Color m_color{Color::black};

    ZoomState *m_zoomState{};
    ColorState *m_colorState{};
};

#endif //EDITOR_PUBLISHER_H
