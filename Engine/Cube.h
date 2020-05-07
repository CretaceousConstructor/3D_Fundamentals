#pragma once
#include <vector>
#include "Vertex.h"
#include "IndexList.h"
#include "Keyboard.h"
#include "Mat4.h"
#include "ChiliMath.h"
class Cube
{
public:
	Cube()
		:
	IndicesList(GetIndicesList()),
	VertexList(GetVertexList())
	{

		TranslationMat = {
		1.f,         0.f,         0.f,               0.f,
		0.f,         1.f,         0.f,               0.f,
		0.f,         0.f,         1.f  ,             -4.f,
		0.f,         0.f,         0.f  ,             1.f
		};
		for (auto& Vertex : VertexList) {
			TranslationMat *= Vertex.p;
		}

	};
	static std::vector<Vertex> GetVertexList()  {
		std::vector<Vertex> result;

		result.emplace_back(Vertex(Pointf4{ side,side,      ( side) }, Vec2{ 0.5f,0.666f })); //0
		result.emplace_back(Vertex(Pointf4{ side,side,      (-side) }, Vec2{ 0.5f,1.f }));//1
		result.emplace_back(Vertex(Pointf4{ -side,side,     (-side) }, Vec2{ 0.25f,1.f }));//2
		result.emplace_back(Vertex(Pointf4{ -side,side,     ( side) }, Vec2{ 0.25f,0.666f }));	 //3
		result.emplace_back(Vertex(Pointf4{ side,-side,     ( side) }, Vec2{ 0.5f,0.333f }));	 //4
		result.emplace_back(Vertex(Pointf4{ -side,-side,    ( side) }, Vec2{ 0.25f,0.333f }));	 //5


		result.emplace_back(Vertex(Pointf4{ side,-side,     (-side) }, Vec2{ 0.75f,0.333f }));//6 
		result.emplace_back(Vertex(Pointf4{ -side,-side,    (-side) }, Vec2{ 1.f,0.333f }));//7

		result.emplace_back(Vertex(Pointf4{ -side,side,      (-side) }, Vec2{ 0.f,0.666f }));//8
		result.emplace_back(Vertex(Pointf4{ -side,-side,     (-side) }, Vec2{ 0.f,0.333f }));//9

		result.emplace_back(Vertex(Pointf4{ side,side,       (-side) }, Vec2{ 0.75f,0.666f }));//10


		result.emplace_back(Vertex(Pointf4{ -side,side,      (-side) }, Vec2{ 1.f,0.666f }));//11

		result.emplace_back(Vertex(Pointf4{ -side,-side,     (-side) }, Vec2{ 0.25f,0.f }));//12

		result.emplace_back(Vertex(Pointf4{ side,-side,      (-side) }, Vec2{ 0.5f,0.f }));//13




		return std::move(result);
	}
	static std::vector<Indexes> GetIndicesList()  {
		std::vector<Indexes> result;
		


		result.emplace_back(Indexes{ 0,1,2 });
		result.emplace_back(Indexes{ 2,3,0 });
		
		result.emplace_back(Indexes{ 4,0,3 });
		result.emplace_back(Indexes{ 3,5,4 });
		
		
		result.emplace_back(Indexes{ 13,4,5 } );
		result.emplace_back(Indexes{ 5,12,13 });
		
		
		result.emplace_back(Indexes{ 5,3,8 });
		result.emplace_back(Indexes{ 8,9,5 });
		
		
		result.emplace_back(Indexes{ 6,10,0 });
		result.emplace_back(Indexes{ 0,4,6 });
		
		
		
		result.emplace_back(Indexes{ 7,11,10 });
		result.emplace_back(Indexes{ 10,6,7});



		return std::move(result);
	}
	void update(Keyboard& kbd);

	Mat4 RotationMat = Mat4::Identity();
	Mat4 TranslationMat = Mat4::Identity();

	static constexpr float side = 0.5f;




	std::vector<Indexes> IndicesList;
	std::vector<Vertex>  VertexList;

	float rotateSpeedInRadius = 0.1f;
};

