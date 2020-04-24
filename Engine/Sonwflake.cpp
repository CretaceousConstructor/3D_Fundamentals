#include "Sonwflake.h"




void SnowFlake::GetDraw(Graphics& GFX) {

	int r = static_cast<int>(radius + 0.5f);

	int xi = r;
	int yi = 0;

	int xChange = 1 - 2 * r;
	int yChange = 1;
	int RadiusError = 0;

	while (xi > yi) {
		{

			int px = static_cast<int>(position.x);
			int py = static_cast<int>(position.y);
			for (int X = px - xi; X <= px + xi; X++) {

				GFX.PutPixel(X, py + yi, snowColor);
			}

			for (int X = px - xi; X <= px + xi; X++) {

				GFX.PutPixel(X, py - yi, snowColor);
			}


		}
		yi += 1;
		RadiusError += yChange;
		yChange += 2;
		if (2 * RadiusError + xChange > 0) {
			xi -= 1;
			RadiusError += xChange;
			xChange += 2;
		}
	}
}

