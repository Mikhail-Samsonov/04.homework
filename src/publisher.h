#ifndef EDITOR_PUBLISHER_H
#define EDITOR_PUBLISHER_H

#include <list>
#include <memory>

#include "color.h"

class Observer
{
public:
	virtual void update() = 0;

	virtual ~Observer() = default;
};

class Observable
{
public:
	virtual void subscribe(const std::shared_ptr<Observer>& obs) = 0;

	virtual  ~Observable() = default;
};

class BaseObservable : public Observable
{
public:
	void subscribe(const std::shared_ptr<Observer>& obs) override
	{
		_subscribers.emplace_back(obs);
	}

	void notify()
	{
		auto it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			auto ptr = it->lock();
			if (ptr)
			{
				ptr->update();
				++it;
			}
			else
			{
				_subscribers.erase(it++);
			}
		}
	}

private:
	std::list<std::weak_ptr<Observer>> _subscribers;
};

class ColorState : public BaseObservable
{
public:
	void set_color(Color color)
	{
		_color = color;
		notify();
	}

	[[nodiscard]] Color get_color() const
	{
		return _color;
	}

private:
	Color _color{ Color::black };
};

class ZoomState : public BaseObservable
{
public:
	void set_zoom(std::size_t zoom)
	{
		_zoom = zoom;
		notify();
	}

	[[nodiscard]] std::size_t get_zoom() const
	{
		return _zoom;
	}

private:
	std::size_t _zoom{ 100 };
};

class Publisher : public Observer, public std::enable_shared_from_this<Publisher>
{
public:
	explicit Publisher(std::size_t id_doc, std::size_t id_elem, std::string& elem_typename)
			: _id_doc(id_doc), _id_elem(id_elem), _elem_typename(elem_typename)
	{
	};

	std::shared_ptr<Publisher>
	static
	create(std::size_t id_doc, ZoomState* zoom, ColorState* color, std::size_t id_elem,
			std::string& elem_typename)
	{
		auto ptr = std::make_shared<Publisher>(id_doc, id_elem, elem_typename);
		ptr->setZoomState(zoom);
		ptr->setColorState(color);
		return ptr;
	}

	void update() override
	{
		std::size_t zoom = _zoomState->get_zoom();
		if (zoom != _zoom)
		{
			std::cout << "switch zoom for document #" << _id_doc << " object #" << _id_elem << " typename -> "
					  << _elem_typename << " to " << zoom << std::endl;
			_zoom = zoom;
		}

		Color color = _colorState->get_color();
		if (color != _color)
		{
			std::cout << "switch color for document #" << _id_doc << " object #" << _id_elem << " typename -> "
					  << _elem_typename << " to " << color << std::endl;
			_color = color;
		}
	}

private:

	void setZoomState(ZoomState* zoom)
	{
		_zoomState = zoom;
		_zoomState->subscribe(shared_from_this());
	}

	void setColorState(ColorState* color)
	{
		_colorState = color;
		_colorState->subscribe(shared_from_this());
	}

	std::size_t _id_doc;
	std::size_t _id_elem;
	std::string _elem_typename;

	std::size_t _zoom{ 100 };
	Color _color{ Color::black };

	ZoomState* _zoomState{};
	ColorState* _colorState{};
};

#endif //EDITOR_PUBLISHER_H
