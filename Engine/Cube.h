#pragma once
#include <vector>
#include "Vertex.h"
#include "IndexList.h"
class Cube
{
public:
	Cube() = default;
	Cube(float le) :
		length(le)
	{
	}


	static std::vector<Vertex> GetVertexList()  {
		std::vector<Vertex> result;
		result.emplace_back(Vertex(Pointf4{ 0.5f,0.5f,      -4.f+( 0.5f) }, Vec2{ 0.5f,0.666f }));
		result.emplace_back(Vertex(Pointf4{ 0.5f,0.5f,      -4.f+(-0.5f) }, Vec2{ 0.5f,1.f }));
		result.emplace_back(Vertex(Pointf4{ -0.5f,0.5f,     -4.f+(-0.5f) }, Vec2{ 0.25f,1.f }));
		result.emplace_back(Vertex(Pointf4{ -0.5f,0.5f,     -4.f+( 0.5f) }, Vec2{ 0.25f,0.666f }));
		result.emplace_back(Vertex(Pointf4{ 0.5f,-0.5f,     -4.f+( 0.5f) }, Vec2{ 0.5f,0.333f }));
		result.emplace_back(Vertex(Pointf4{ 0.5f,-0.5f,     -4.f+(-0.5f) }, Vec2{ 0.75f,0.333f }));
		result.emplace_back(Vertex(Pointf4{ -0.5f,-0.5f,    -4.f+(-0.5f) }, Vec2{ 1.f,0.333f }));
		result.emplace_back(Vertex(Pointf4{ -0.5f,-0.5f,    -4.f+( 0.5f) }, Vec2{ 0.25f,0.333f }));
		return std::move(result);
	}


	static std::vector<Indexes> GetIndicesList()  {
		std::vector<Indexes> result;
		


		result.emplace_back(Indexes{ 0,1,2 });
		result.emplace_back(Indexes{ 2,3,0 });
		
		result.emplace_back(Indexes{1,0,4 });
		result.emplace_back(Indexes{ 1,4,5 });
		
		
		result.emplace_back(Indexes{ 6,1,5 });
		result.emplace_back(Indexes{ 6,2,1 });
		
		
		result.emplace_back(Indexes{ 3,2,7 });
		
		result.emplace_back(Indexes{ 2,6,7 });
		
		
		result.emplace_back(Indexes{ 0,3,7 });
		result.emplace_back(Indexes{ 0,7,4 });
		
		
		
		result.emplace_back(Indexes{ 5,4,7 });
		
		result.emplace_back(Indexes{ 7,6,5 });



		return std::move(result);
	}
	float length;
};

