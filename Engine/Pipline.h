#pragma once

#include "Graphics.h"
#include "Vertex.h"
#include "Triangle.h"
#include <vector>
#include "IndexList.h"
#include "Mat4.h"
#include "Spectrum.h"
#include "Pangle.h"
#include "ChiliMath.h"
#include "Camera.h"
#include "Sprite.h"
#include "iostream"
class Pipline
{
public:
	Pipline() = delete;
	Pipline(Graphics& GFX);
	void SeparateIndexesListAndVertex(const std::vector<Indexes>& IndexesList,const std::vector<Vertex>& vertexes);
	void GoThroughVertexTransformation(const std::vector<Indexes>& IndexesList,const std::vector<Vertex>& vertexes);
	void AssembleTriangle(const std::vector<Indexes> IndexesList,const std::vector<Vertex>& vertexes);
	void ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void PostProcessTriangle( _Pangle<Vertex> triangle);

	void DrawTriangle(const _Pangle<Vertex>& tr);
	void DrawFlatTopTriangle(const Vertex& v0,const Vertex& v1, const Vertex& v2);//draw in clockwise order 
	void DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);//draw in counterclockwise order 


	Color GetColorFromTexture(Vec2 uv, const texture& tex);



	Mat4 orthographicPro;
	Mat4 perspectiveProjection;
	Mat4 ScaleMa;
	Mat4 TransMa;
	NDCScreenTransformer NSTmer;
	Camera camera;
	Graphics& gfx;
	std::unique_ptr<texture> tx;

};

