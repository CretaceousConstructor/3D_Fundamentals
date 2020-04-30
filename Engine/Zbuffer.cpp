#include "Zbuffer.h"

Zbuffer::Zbuffer(int width, int height)
	:w(width),h(height)
{
	zBuffer = std::make_unique<float[]>((width * height));

}

float Zbuffer::At(int x, int y) const
{
	
		return zBuffer[(y * w + x)];
	

}

void Zbuffer::Clear()
{
	const int nDepths = h * w;
	
	for (int i = 0; i < nDepths; ++i) {
		zBuffer[i] = std::numeric_limits<float>::lowest();
	}


	}
void Zbuffer::Store(int x, int y, float z)
{
	zBuffer[(y * w + x)] = z;
}
