#pragma once

#include <vector>
#include "TextureVertex.h"
#include "IndexList.h"
class WaveyPlane {

public:

	static std::vector<TextureVertex> GetTextureVertexList(float side) {

		std::vector<TextureVertex> result;
		//result.emplace_back(TextureVertex(Pointf4{ side,side,      (side) }, Vec2{ 0.5f,0.666f })); //0
		//result.emplace_back(TextureVertex(Pointf4{ side,side,      (-side) }, Vec2{ 0.5f,1.f }));//1
		//result.emplace_back(TextureVertex(Pointf4{ -side,side,     (-side) }, Vec2{ 0.25f,1.f }));//2
		//result.emplace_back(TextureVertex(Pointf4{ -side,side,     (side) }, Vec2{ 0.25f,0.666f }));	 //3


		Pointf4   a  =Pointf4{ side, 0.f,   -3.f +    (side)  }    ;
		Pointf4	  b  =Pointf4{ side, 0.f,   -3.f +    (-side)  }   ;
		Pointf4	  c  =Pointf4{ -side,0.f,   -3.f +   (-side)  }   ;
		Pointf4	  d  =Pointf4{ -side,0.f,   -3.f +   (side)  }    ;
		
			Vec2 aUV = {1.f,0.f};
			Vec2 bUV = {1.f,1.f};
			Vec2 cUV = {0.f,1.f};
			Vec2 dUV = {0.f,0.f};




		//
		float stepInCtoD = (d.z - c.z) / (float)partitions;
		float stepInCtoB = (b.x - c.x) / (float)partitions;

		float stepInCtoDUV = (dUV.y - cUV.y)/ (float)partitions;
		float stepInCtoBUV = (bUV.x - cUV.x)/ (float)partitions;

		




		for (int i = 0; i <= partitions; i++) { //z
			for (int j = 0; j <= partitions; j++) {//x
				result.emplace_back(TextureVertex{ Pointf4{  stepInCtoB * (float)j + c.x,0.f,c.z + (float)i * stepInCtoD }, Vec2{stepInCtoBUV * (float)j + cUV.x,  stepInCtoDUV * (float)i + cUV.y} });
				
			}


		}
		return std::move(result);

	}

	static std::vector<Indexes> GetTextureIndicesList() {
		std::vector<Indexes> result;
		for (int i = 0; i < partitions; i++) {
			for (int j = 0; j < partitions; j++)
			{
				int topleftPoint = j + i * (partitions + 1);

				result.emplace_back(Indexes(topleftPoint + (partitions + 1) + 1,topleftPoint + 1,  topleftPoint));

				result.emplace_back(Indexes(topleftPoint, topleftPoint +(partitions + 1), topleftPoint + ( partitions +1) + 1));

			}
		}


		return std::move(result);
	}


	static constexpr int partitions = 20;


};