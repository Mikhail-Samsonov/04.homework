#ifndef EDITOR_DOCUMENT_H
#define EDITOR_DOCUMENT_H

#include "publisher.h"
#include <unordered_set>
#include "shape.h"
#include "display.h"

class Document
{
public:
	Document()
	{
		++_id;
		set_id();
	}

	void set_color(Color color)
	{
		_color.set_color(color);
	}

	void set_zoom(std::size_t zoom)
	{
		_zoom.set_zoom(zoom);
	}

	const std::unique_ptr<IShape>& add_line()
	{
		auto [it, inserted] = _shapes.emplace(std::make_unique<Line>(_id_doc, &_zoom, &_color));
		assert(inserted);
		return *it;
	}

	const std::unique_ptr<IShape>& add_circle()
	{
		auto [it, inserted] = _shapes.emplace(std::make_unique<Circle>(_id_doc, &_zoom, &_color));
		assert(inserted);
		return *it;
	}

	const std::unique_ptr<IShape>& add_square()
	{
		auto [it, inserted] = _shapes.emplace(std::make_unique<Square>(_id_doc, &_zoom, &_color));
		assert(inserted);
		return *it;
	}

	bool remove_shape(const std::unique_ptr<IShape>& shape)
	{
		std::size_t removed = _shapes.erase(shape);
		if (removed == 0)
			return false;
		return true;
	}

	void draw(IDisplay& d)
	{
		for (const auto& i: _shapes)
		{
			d.display(*i);
		}
	}

	std::size_t get_id() const
	{
		return _id_doc;
	}

	void set_id()
	{
		_id_doc = _id;
	}

private:
	static std::size_t _id;
	std::size_t _id_doc;
	ZoomState _zoom;
	ColorState _color;
	std::unordered_set<std::unique_ptr<IShape> > _shapes;
};

std::size_t Document::_id = 0;

#endif //EDITOR_DOCUMENT_H
