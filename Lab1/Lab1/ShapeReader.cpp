#include "stdafx.h"
#include "ShapeReader.h"

std::string CShapeReader::ReadRightPart(std::ifstream &inpStream)
{
	std::string fullPointString;
	inpStream >> fullPointString;

	size_t eqPos = fullPointString.find("=");

	return fullPointString.substr(eqPos + 1);
}

ShapePoint CShapeReader::ReadPoint(std::ifstream &inpStream)
{
	std::istringstream iss(ReadRightPart(inpStream));

	std::string firstNum, secondNum;
	std::getline(iss, firstNum, ',');
	std::getline(iss, secondNum, ';');

	return ShapePoint(std::stoll(firstNum), std::stoll(secondNum));
}

long long CShapeReader::ReadNumber(std::ifstream &inpStream)
{
	std::istringstream iss(ReadRightPart(inpStream));

	std::string number;
	std::getline(iss, number, ';');

	return std::stoll(number);
}

std::unique_ptr<CRectangle> CShapeReader::ReadRectangle(std::ifstream &inpStream)
{
	return std::unique_ptr<CRectangle>(new CRectangle(ReadPoint(inpStream), ReadPoint(inpStream)));
}

std::unique_ptr<CTriangle> CShapeReader::ReadTriangle(std::ifstream &inpStream)
{
	return std::unique_ptr<CTriangle>(new CTriangle(ReadPoint(inpStream), ReadPoint(inpStream), ReadPoint(inpStream)));
}

std::unique_ptr<CCircle> CShapeReader::ReadCircle(std::ifstream &inpStream)
{
	ReadPoint(inpStream);
	return std::unique_ptr<CCircle>(new CCircle(ReadNumber(inpStream)));
}

std::unique_ptr<IShape> CShapeReader::ReadShape(std::ifstream &inpStream, const std::string &shapeType)
{
	if (shapeType == "RECTANGLE:") return ReadRectangle(inpStream);
	if (shapeType == "TRIANGLE:") return ReadTriangle(inpStream);
	if (shapeType == "CIRCLE:") return ReadCircle(inpStream);

	std::cerr << "Wrong type: " << shapeType << std::endl;
	//throw std::invalid_argument("Wrong shape type");
	return nullptr;
}