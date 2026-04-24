#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape() = default; // конструктор генерируется по умолчанию компилятором
	virtual ~ISolidShape() = default; //для чего здесь виртуальный деструктор?

	virtual std::string GetFillColor() const = 0;
	// устранить дублирование (outlinecolor, fillcolor)
};
