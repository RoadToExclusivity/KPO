#include "stdafx.h"
#include "IShape.h"
#include "ShapePoint.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

ShapePoint ReadPoint(std::ifstream &inpStream)
{
	std::string fullPointString;
	inpStream >> fullPointString;
	
	size_t eqPos = fullPointString.find("=");
	std::istringstream iss(fullPointString.substr(eqPos + 1));

	std::string firstNum, secondNum;
	std::getline(iss, firstNum, ',');
	std::getline(iss, secondNum, ';');

	return ShapePoint(std::stoll(firstNum), std::stoll(secondNum));
}

long long ReadNumber(std::ifstream &inpStream)
{
	std::string fullPointString;
	inpStream >> fullPointString;

	size_t eqPos = fullPointString.find("=");
	std::istringstream iss(fullPointString.substr(eqPos + 1));

	std::string number;
	std::getline(iss, number, ';');

	return std::stoll(number);
}

std::unique_ptr<CRectangle> ReadRectangle(std::ifstream &inpStream)
{
	return std::unique_ptr<CRectangle>(new CRectangle(ReadPoint(inpStream), ReadPoint(inpStream)));
}

std::unique_ptr<CTriangle> ReadTriangle(std::ifstream &inpStream)
{
	return std::unique_ptr<CTriangle>(new CTriangle(ReadPoint(inpStream), ReadPoint(inpStream), ReadPoint(inpStream)));
}

std::unique_ptr<CCircle> ReadCircle(std::ifstream &inpStream)
{
	ReadPoint(inpStream);
	return std::unique_ptr<CCircle>(new CCircle(ReadNumber(inpStream)));
}

std::unique_ptr<IShape> ReadShape(std::ifstream &inpStream, const std::string &shapeType)
{
	if (shapeType == "RECTANGLE:") return ReadRectangle(inpStream);
	if (shapeType == "TRIANGLE:") return ReadTriangle(inpStream);
	if (shapeType == "CIRCLE:") return ReadCircle(inpStream);

	std::cerr << "Wrong type: " << shapeType << std::endl;
	throw std::invalid_argument("Wrong shape type");
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	std::string type;
	while (fin >> type)
	{
		auto shape = ReadShape(fin, type);
		fout << type << " " << "P=" << std::setprecision(6) << shape->GetPerimeter() << "; S=" << shape->GetArea() << std::endl;
	}

	return 0;
}