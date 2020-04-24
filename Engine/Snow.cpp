#include "Snow.h"

Snow::Snow(Vec2 position, Color c, float rad, Vec2 valoci )
	:
	snowColor(c),
	position(position),
	radius(rad),
	valocity(valoci)
{
}





void Snow::GetDraw(Graphics& GFX) {

	if (offTheScreen) {
		return;
	}

	int r = static_cast<int>(radius + 0.5f);
	int xi = r;
	int yi = 0;

	int xChange = 1 - 2 * r;
	int yChange = 1;
	int RadiusError = 0;


	const int px = static_cast<int>(position.x);
	const int py = static_cast<int>(position.y);

	int screenWidth = (signed)GFX.ScreenWidth;
	int screenHeight = (signed)GFX.ScreenHeight;



	if (screenWidth <= (px - r) || (px + r) < 0 || (py + r) < 0 || (py - r) >= screenHeight) {
		offTheScreen = true;
		return;
	}



	while (xi >= yi) {

		int xLeft = max(0, px - xi);
		int xRight = min(screenWidth - 1, px + xi);

		int y = py + yi;
		if (y >= 0 && y < screenHeight) {
			for (int X = xLeft; X <= xRight; X++) {
				GFX.PutPixel(X, y, snowColor);
			}
		}
		y = py - yi;
		if (y >= 0 && y < screenHeight)
		{
			for (int X = xLeft; X <= xRight; X++) {
				GFX.PutPixel(X, y, snowColor);
			}
		}

		xLeft = max(0, px - yi);
		xRight = min(screenWidth - 1, px + yi);
		y = py + xi;
		if (y >= 0 && y < screenHeight) {

			for (int X = xLeft; X <= xRight; X++) {
				GFX.PutPixel(X, y, snowColor);
			}
		}
		y = py - xi;
		if (y >= 0 && y < screenHeight) {
			for (int X = xLeft; X <= xRight; X++) {
				GFX.PutPixel(X, y, snowColor);
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

void Snow::Move(float timeElapsed )
{
	// 0.0167f;
	position += valocity * timeElapsed;

}

