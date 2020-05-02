#include "Triangle.h"

Triangle::Triangle(std::vector<Vertex> ver, std::vector<int> inde, const texture& t)
	:
	surf(&t),
	vertexs(ver),
	index(inde)
{
}


Triangle::Triangle()
	:surf(nullptr)
{
	vertexs.resize(3);
	index.resize(3);
}

