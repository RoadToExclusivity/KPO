#include "stdafx.h"
#include "IShape.h"
#include "ShapeReader.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	std::string type;
	while (fin >> type)
	{
		auto shape = CShapeReader::ReadShape(fin, type);
		fout << type << " " << "P=" << std::setprecision(6) << shape->GetPerimeter() << "; S=" << shape->GetArea() << std::endl;
	}

	return 0;
}