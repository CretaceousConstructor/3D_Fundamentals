#pragma once
#include <vector>
#include "IndexList.h"
#include "Keyboard.h"
#include "Mat4.h"
#include "ChiliMath.h"	
#include "TextureVertex.h"
#include "ColorVertex.h"

class Cube
{
public:

	Cube() = delete;
	
	static std::vector<TextureVertex> GetTextureVertexList(float side)  {
		std::vector<TextureVertex> result;

		result.emplace_back(TextureVertex(Pointf4{ side,side,      ( side) }, Vec2{ 0.5f,0.666f })); //0
		result.emplace_back(TextureVertex(Pointf4{ side,side,      (-side) }, Vec2{ 0.5f,1.f }));//1
		result.emplace_back(TextureVertex(Pointf4{ -side,side,     (-side) }, Vec2{ 0.25f,1.f }));//2
		result.emplace_back(TextureVertex(Pointf4{ -side,side,     ( side) }, Vec2{ 0.25f,0.666f }));	 //3
		result.emplace_back(TextureVertex(Pointf4{ side,-side,     ( side) }, Vec2{ 0.5f,0.333f }));	 //4
		result.emplace_back(TextureVertex(Pointf4{ -side,-side,    ( side) }, Vec2{ 0.25f,0.333f }));	 //5
					
		result.emplace_back(TextureVertex(Pointf4{ side,-side,     (-side) }, Vec2{ 0.75f,0.333f }));//6 
		result.emplace_back(TextureVertex(Pointf4{ -side,-side,    (-side) }, Vec2{ 1.f,0.333f }));//7
						
		result.emplace_back(TextureVertex(Pointf4{ -side,side,      (-side) }, Vec2{ 0.f,0.666f }));//8
		result.emplace_back(TextureVertex(Pointf4{ -side,-side,     (-side) }, Vec2{ 0.f,0.333f }));//9
						
		result.emplace_back(TextureVertex(Pointf4{ side,side,       (-side) }, Vec2{ 0.75f,0.666f }));//10
					
		result.emplace_back(TextureVertex(Pointf4{ -side,side,      (-side) }, Vec2{ 1.f,0.666f }));//11
			
		result.emplace_back(TextureVertex(Pointf4{ -side,-side,     (-side) }, Vec2{ 0.25f,0.f }));//12
				
		result.emplace_back(TextureVertex(Pointf4{ side,-side,      (-side) }, Vec2{ 0.5f,0.f }));//13




		return std::move(result);
	}
	static std::vector<Indexes> GetTextureIndicesList(float side)  {
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
	
	static std::vector<ColorVertex> GetColorVertexList(float side) {
		std::vector<ColorVertex> result;

		result.emplace_back(ColorVertex(Pointf4{ side,side,    (side) },		Vec3{ 100.f,120.f,200.f   })); //0
		result.emplace_back(ColorVertex(Pointf4{ side,side,    (-side) },		Vec3{ 20.f,130.f,200.f }));//1
		result.emplace_back(ColorVertex(Pointf4{ -side,side,   (-side) },		Vec3{ 150.f,120.f,200.f }));//2
		result.emplace_back(ColorVertex(Pointf4{ -side,side,   (side) },		Vec3{ 70.f,125.f,155.f }));	 //3
		result.emplace_back(ColorVertex(Pointf4{ side,-side,    (-side) },		Vec3{ 50.f,120.f,250.f }));// 4
		result.emplace_back(ColorVertex(Pointf4{ side,-side,   (side) },		Vec3{ 100.f,120.f,200.f }));//   5
		result.emplace_back(ColorVertex(Pointf4{ -side,-side,  (side) },		Vec3{ 100.f,120.f,200.f }));//   6
		result.emplace_back(ColorVertex(Pointf4{ -side,-side,   (-side) },		Vec3{ 100.f,120.f,200.f }));// 7

		

		return std::move(result);
	}
	static std::vector<Indexes> GetColorIndicesList(float side) {
		std::vector<Indexes> result;

		result.emplace_back(Indexes{ 0,1,2 });
		result.emplace_back(Indexes{ 2,3,0 });


		result.emplace_back(Indexes{ 0,3,6 });
		result.emplace_back(Indexes{ 5,0,6 });


		result.emplace_back(Indexes{ 5,6,7 });
		result.emplace_back(Indexes{ 5,7,4 });





		result.emplace_back(Indexes{ 3,2,7 });
		result.emplace_back(Indexes{ 3,7,6 });


		result.emplace_back(Indexes{ 1,0,5 });
		result.emplace_back(Indexes{ 1,5,4 });

		result.emplace_back(Indexes{ 7,2,1 });
		result.emplace_back(Indexes{ 4,7,1 });



		return std::move(result);
	}



	/*void update(Keyboard& kbd);*/
	Mat4 RotationMat = Mat4::Identity();
	Mat4 TranslationMat = Mat4::Identity();
	std::vector<Indexes> IndicesList;
	std::vector<ColorVertex>  VertexList;
	float rotateSpeedInRadius = 0.1f;
};

