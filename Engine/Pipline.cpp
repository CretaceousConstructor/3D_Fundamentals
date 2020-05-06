#include "Pipline.h"


Pipline::Pipline(Graphics& GFX)
	:NSTmer((int)Graphics::ScreenWidth, (int)Graphics::ScreenHeight),
	gfx(GFX),
	camera({ 0.f,0.f,0.f }, { 0.f,0.f,-1.f }, { 0.f,1.f,0.f }),
	tx(std::make_unique<texture>("D:\\CS\\ChiliEngine\\Bmp\\tex.bmp"))
{ 
	//(cubnoid space)orthographicSpce -> (NDC space [-1,1]^3)
	ScaleMa = Mat4::Identity();
	ScaleMa.elements[0][0] = 2.f / (Spectrum::r - Spectrum::l);
	ScaleMa.elements[1][1] = 2.f / (Spectrum::t - Spectrum::b);
	ScaleMa.elements[2][2] = 2.f / (Spectrum::n - Spectrum::f);
	TransMa = Mat4::Translation((Spectrum::r + Spectrum::l) / -2.f, (Spectrum::t + Spectrum::b) / -2.f, (Spectrum::n + Spectrum::f) / -2.f);
	orthographicPro = ScaleMa * TransMa;
	//worldspace to (cubnoid space)orthographicSpce
	Mat4 perspectiveToOrtho = {
		 Spectrum::n  ,   0.f        ,              0.f  ,  0.f,
		 0.f          ,  Spectrum::n ,              0.f  ,  0.f,
		 0.f          ,   0.f        ,     Spectrum::n + Spectrum::f,-Spectrum::n * Spectrum::f,
		 0.f          ,   0.f        ,              1.f  ,  0.f
	};
	perspectiveProjection = perspectiveToOrtho;


}

void Pipline::SeparateIndexesListAndVertex(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes)
{

	GoThroughVertexTransformation(IndexesList, vertexes);

}

void Pipline::GoThroughVertexTransformation(const std::vector<Indexes>& IndexesList, const std::vector<Vertex>& vertexes)
{
	std::vector<Vertex> verticesOut;
	verticesOut = vertexes;

	for (auto& v : verticesOut) {
		camera.cameraTransformation *= v.p;
	}




	

	AssembleTriangle(IndexesList, verticesOut);
}

void Pipline::AssembleTriangle(const std::vector<Indexes> IndexesList, const std::vector<Vertex>& vertexes)
{

	for (auto& indexes : IndexesList) {
		const auto& v0 = vertexes[indexes[0]];
		const auto& v1 = vertexes[indexes[1]];
		const auto& v2 = vertexes[indexes[2]];


		if ((Vec4::dot((v1.p - v0.p), (v2.p - v0.p)) * Vec4(v0.p)) < 0.f) {
			ProcessTriangle(v0, v1, v2);
		}
	}
}

void Pipline::ProcessTriangle( const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	

	PostProcessTriangle( _Pangle<Vertex>{v0,v1,v2} );

}

void Pipline::PostProcessTriangle(_Pangle<Vertex> triangle)
{
	



	perspectiveProjection *=triangle.v0.p;
	perspectiveProjection *=triangle.v1.p;
	perspectiveProjection *=triangle.v2.p;


	//to NDC
	orthographicPro *= triangle.v0.p;
	orthographicPro *= triangle.v1.p;
	orthographicPro *= triangle.v2.p;



	NSTmer.Transform(triangle.v0);
	NSTmer.Transform(triangle.v1);
	NSTmer.Transform(triangle.v2);

	DrawTriangle(triangle);

}

void Pipline::DrawTriangle(const _Pangle<Vertex>& tr)
{

	//sort them so that v0 at top,v2 at the bottom 
	const Vertex* pv0 = &tr.v0;
	const Vertex* pv1 = &tr.v1;
	const Vertex* pv2 = &tr.v2;
	//sort
	if (pv0->p.y > pv1->p.y)  std::swap(pv0, pv1);
	if (pv0->p.y > pv2->p.y)  std::swap(pv0, pv2);
	if (pv1->p.y > pv2->p.y)  std::swap(pv1, pv2);


	if (pv0->p.y == pv1->p.y)  //flat top tri 
	{
		if (pv0->p.x > pv1->p.x) {
			std::swap(pv0, pv1);
		}

		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
	}

	else if (pv1->p.y == pv2->p.y)  //flat bottom tri 
	{
		if (pv1->p.x > pv2->p.x) {
			std::swap(pv1, pv2);
		}

		DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
	}

	else { //general tir

		const float alpha = (pv1->p.y - pv0->p.y) / (pv2->p.y - pv0->p.y);

		Vertex vi = *pv0 + (*pv2 - *pv0) * alpha;





		if (vi.p.x > pv1->p.x) //major right
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(*pv0, *pv1, vi);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle(*pv1, vi, *pv2);
		}
		else//major left
		{
			//counterclockwise order
				//          v0
				//         /  \ 
				//        /    \
				//       v1----v2

			DrawFlatBottomTriangle(*pv0, vi, *pv1);
			//clockwise order
				// v0--------v1
				//   \      /
				// v' \    / v''
				//      v2

			DrawFlatTopTriangle( vi, *pv1, *pv2);
		}
	}



}

void Pipline::DrawFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

	// v0--------v1
	//   \      /
	// v' \    / v''
	//      v2
	// z negtive

	if (v2.p.y < 0.f || v1.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	//run over rise ,avoid vertical fuck up
	float m0 = (v2.p.x - v0.p.x) / (v2.p.y - v0.p.y);
	float m1 = (v2.p.x - v1.p.x) / (v2.p.y - v1.p.y);


	//scanline start and end
	const int yStart = max((int)ceil(v0.p.y - 0.5f), 0);
	const int yEnd =   min((int)ceil(v2.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive this last one
	Vertex vPrime;
	Vertex vPrimePrime;
	Vertex finalPoint;
	for (int y = yStart; y < yEnd; y++)
	{
		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v1.p.y) + v1.p.x;
		const int xStart = max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));//exclusive

		for (int x = xStart; x < xEnd; x++) {
			float alpha = (float(y) + 0.5f - v0.p.y) / (v2.p.y - v0.p.y);
			 vPrime = v0 + (v2 - v0) * alpha;
			 vPrimePrime = v1 + (v2 - v1) * alpha;
			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			 finalPoint = vPrime + (vPrimePrime - vPrime) * beta;
			float recipicalOfz = finalPoint.p.w;
			float z = (1.f / recipicalOfz);

			//if (recipicalOfz > pzBuffer.At(x, y)) {
				//pzBuffer.Store(x, y, z);
			gfx.PutPixel(x, y, GetColorFromTexture((finalPoint.uvCoordinate * z), *tx) );
					//GetColorFromTexture(finalPoint.uvCoordinate * z, *tr.surf));
			//}

		}
	}

}

void Pipline::DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	//          v0
	//         /  \ 
	//        /    \
	//       v1----v2


	if (v2.p.y < 0.f || v2.p.x < 0.f || v0.p.y >= float(Graphics::ScreenHeight)) return;

	float m0 = (v0.p.x - v1.p.x) / (v0.p.y - v1.p.y);
	float m1 = (v0.p.x - v2.p.x) / (v0.p.y - v2.p.y);





	int yStart = max((int)ceil(v0.p.y - 0.5f), 0);
	int yEnd = min((int)ceil(v1.p.y - 0.5f), (int)(Graphics::ScreenHeight)); //exclusive


	Vertex vPrime;
	Vertex vPrimePrime;
	Vertex finalPoint;
	for (int y = yStart; y < yEnd; y++) {
		const float px0 = m0 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const float px1 = m1 * (float(y) + 0.5f - v0.p.y) + v0.p.x;
		const int xStart = max((int)ceil(px0 - 0.5f), 0);
		const int xEnd = min((int)ceil(px1 - 0.5f), (int)(Graphics::ScreenWidth));
		for (int x = xStart; x < xEnd; x++) {
			//          v0
			//         /  \ 
			//    v'  /    \ v''
			//       v1----v2

			float alpha = (float(y) + 0.5f - v0.p.y) / (v1.p.y - v0.p.y);

			 vPrime = v0 + (v1 - v0) * alpha;
			 vPrimePrime = v0 + (v2 - v0) * alpha;

			float beta = (float(x) + 0.5f - vPrime.p.x) / (vPrimePrime.p.x - vPrime.p.x);
			 finalPoint = vPrime + (vPrimePrime - vPrime) * beta;


			float recipicalOfz = finalPoint.p.w;
			float z = 1.f / recipicalOfz;

			//if (recipicalOfz > pzBuffer.At(x, y)) {
			//	pzBuffer.Store(x, y, z);

				gfx.PutPixel(x, y, GetColorFromTexture(finalPoint.uvCoordinate * z, *tx));
				std::cout << "fuck you!!";
				//GetColorFromTexture(finalPoint.uvCoordinate * z, *tx)
			//}

		}

	}


}

Color Pipline::GetColorFromTexture(Vec2 uv, const texture& tex)
{

	const int w = tex.GetWidth();
	const int h = tex.GetHeight();
	const float u = uv.x; // u
	const float v = uv.y; // v

	int x = (int)(w * fmod(u, 1.f));
	int y = (int)(h * fmod(v, 1.f));
	
	if (x >= w || x < 0 || y > h || y < 0) {

		return Colors::White;
		
	}
	return tex.GetColor(x, y);

}






