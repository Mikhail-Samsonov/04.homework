#ifndef EDITOR_DISPLAY_H
#define EDITOR_DISPLAY_H

#include "shape.h"

class IDisplay
{
public:
	virtual void display(IShape& shape) = 0;

	virtual ~IDisplay() = default;
};

class DefaultDisplay : public IDisplay
{
public:
	void display(IShape& shape) override
	{
		shape.draw(std::cout);
	}
};

#endif //EDITOR_DISPLAY_H
