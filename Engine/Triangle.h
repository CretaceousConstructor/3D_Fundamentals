#pragma once

#include <vector>
#include "Sprite.h"
#include "Vertex.h"


class Triangle
{
public:
	Triangle();
	Triangle(std::vector<Vertex> vertexs, std::vector<int> index, const texture& t);

	std::vector<int> index;
	std::vector<Vertex> vertexs;
	const texture* surf;

};

