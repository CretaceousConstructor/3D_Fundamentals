#pragma once
#include <memory>

class Zbuffer {
public:
	Zbuffer(int width,int height);

	float At(int x, int y) const;
	void Clear();
	void Store(int x, int y, float z);
	std::unique_ptr<float[]> zBuffer;

	int w;
	int h;


};