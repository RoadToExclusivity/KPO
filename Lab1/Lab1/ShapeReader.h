#pragma once
#include "stdafx.h"
#include "IShape.h"
#include "ShapePoint.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

class CShapeReader
{
public:
	static std::unique_ptr<IShape> ReadShape(std::ifstream &inpStream, const std::string &shapeType);

private:
	static std::unique_ptr<CCircle> ReadCircle(std::ifstream &inpStream);
	static std::unique_ptr<CTriangle> ReadTriangle(std::ifstream &inpStream);
	static std::unique_ptr<CRectangle> ReadRectangle(std::ifstream &inpStream);
	static long long ReadNumber(std::ifstream &inpStream);
	static ShapePoint ReadPoint(std::ifstream &inpStream);
	static std::string ReadRightPart(std::ifstream &inpStream);
};

