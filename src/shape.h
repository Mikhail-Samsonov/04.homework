#ifndef EDITOR_SHAPE_H
#define EDITOR_SHAPE_H

#include "publisher.h"

class IShape
{
public:
	IShape()
	{
		++_id;
		set_id();
	}

	virtual ~IShape() = default;

	virtual void draw(std::ostream& out) = 0;

	void set_id()
	{
		_id_elem = _id;
	}

protected:
	static std::size_t _id;
	std::size_t _id_elem;
	std::shared_ptr<Publisher> _publisher;
};

std::size_t IShape::_id = 0;

class Line : public IShape
{
public:
	Line(std::size_t id_doc, ZoomState* zoom, ColorState* color)
			: IShape()
	{
		_publisher = _publisher->create(id_doc, zoom, color, _id_elem, _name);
	};

	void draw(std::ostream& out) override
	{
		out << "I'm a " << _name << " #" << _id_elem << std::endl;
	}

private:
	std::string _name = "line";
};

class Circle : public IShape
{
public:
	Circle(std::size_t id_doc, ZoomState* zoom, ColorState* color)
			: IShape()
	{
		_publisher = _publisher->create(id_doc, zoom, color, _id_elem, _name);
	};


	void draw(std::ostream& out) override
	{
		out << "I'm a " << _name << " #" << _id_elem << std::endl;
	}

private:
	std::string _name = "circle";
};

class Square : public IShape
{
public:
	Square(std::size_t id_doc, ZoomState* zoom, ColorState* color)
			: IShape()
	{
		_publisher = _publisher->create(id_doc, zoom, color, _id_elem, _name);
	};

	void draw(std::ostream& out) override
	{
		out << "I'm a " << _name << " #" << _id_elem << std::endl;
	}

private:
	std::string _name = "square";
};

#endif //EDITOR_SHAPE_H
