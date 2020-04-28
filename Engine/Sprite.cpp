#include "Sprite.h"

Sprite::Sprite(std::string bmpFileName)
{
	std::ifstream inFile;
	inFile.open(bmpFileName, std::ios::in | std::ios::binary);
	if (!inFile.is_open())
	{
		std::cout << "error!";
		return;
	}
	char tempArr[20];
	unsigned sizeOfBmp = 0u;
	unsigned offSetOfMap = 0u;
	inFile.read(tempArr, 14);
	if (!inFile) {
		std::cout << "error!";

		return;
	}
	if (tempArr[0] != 'B' || tempArr[1] != 'M') {
		std::cout << "wrong formatting";
		return;
	}
	char* sizePtr = (char*)(&sizeOfBmp);
	for (int i = 0; i < 4; i++) {
		sizePtr[i] = tempArr[2 + i];
	}
	char* offSetPtr = (char*)(&offSetOfMap);
	for (int i = 0; i < 4; i++) {
		offSetPtr[i] = tempArr[10 + i];
	}

	unsigned int sizeOfThisHeader = 0u;
	inFile.read((char*)(&sizeOfThisHeader), 4);

	switch (sizeOfThisHeader) {
		//124	BITMAPV5HEADER
	case 40u:
	case 124u:
	{
		int bitmapWidthInPixel;
		inFile.read((char*)(&bitmapWidthInPixel), 4);
		int bitmapHeightInPixel;
		inFile.read((char*)(&bitmapHeightInPixel), 4);
		if (bitmapHeightInPixel < 0) {
			bitmapHeightInPixel = -bitmapHeightInPixel;
		}



		width = bitmapWidthInPixel;
		height = bitmapHeightInPixel;


		inFile.seekg(2, std::ios::cur);
		int colorDepth = 0;
		inFile.read((char*)(&colorDepth), 2);

		if (colorDepth == 24) {

			inFile.seekg(4, std::ios::cur);

			int rawBitMapSize = 0;
			inFile.read((char*)(&rawBitMapSize), 4);
			int padding = 0;
			if ((bitmapWidthInPixel * (colorDepth / 8)) % 4 != 0) {
				int numberOfBytesPerLine = (((bitmapWidthInPixel * (colorDepth / 8)) / 4) * 4) + 4;
				padding = numberOfBytesPerLine - ((bitmapWidthInPixel * (colorDepth / 8)));
			}


			bitMap = std::make_unique<Color[]>(bitmapWidthInPixel * bitmapHeightInPixel);

			inFile.seekg(offSetOfMap, std::ios::beg);
			int rawBitIndex = 0;
			unsigned char r; unsigned char g; unsigned char b;
			//Color tempArr[bitmapWidthInPixel * bitmapHeightInPixel];
			Color* tempArr = new Color[bitmapWidthInPixel * bitmapHeightInPixel];
			for (int i = 0; i < bitmapHeightInPixel; i++) {
				for (int j = 0; j < bitmapWidthInPixel; j++) {
					inFile.read((char*)&b, 1);
					inFile.read((char*)&g, 1);
					inFile.read((char*)&r, 1);
					tempArr[rawBitIndex++] = Color{ r,g,b };
				}
				inFile.seekg(padding, std::ios::cur);
			}

			int indexOfbitMap = 0;
			for (int i = bitmapHeightInPixel - 1; i >= 0; i--) {
				for (int j = 0; j < bitmapWidthInPixel; j++) {
					bitMap[indexOfbitMap++] = tempArr[i * bitmapWidthInPixel + j];
				}
			}

			delete[] tempArr;
		}
		else if (colorDepth == 32) {

			inFile.seekg(4, std::ios::cur);

			int rawBitMapSize = 0;
			inFile.read((char*)(&rawBitMapSize), 4);
			int padding = 0;
			if ((bitmapWidthInPixel * (colorDepth / 8)) % 4 != 0) {
				int numberOfBytesPerLine = (((bitmapWidthInPixel * (colorDepth / 8)) / 4) * 4) + 4;
				padding = numberOfBytesPerLine - ((bitmapWidthInPixel * (colorDepth / 8)));
			}


			bitMap = std::make_unique<Color[]>(bitmapWidthInPixel * bitmapHeightInPixel);

			inFile.seekg(offSetOfMap, std::ios::beg);
			int rawBitIndex = 0;
			unsigned char x; unsigned char r; unsigned char g; unsigned char b;
			//Color tempArr[bitmapWidthInPixel * bitmapHeightInPixel];
			Color* tempArr = new Color[bitmapWidthInPixel * bitmapHeightInPixel];
			for (int i = 0; i < bitmapHeightInPixel; i++) {
				for (int j = 0; j < bitmapWidthInPixel; j++) {
					inFile.read((char*)&b, 1);
					inFile.read((char*)&g, 1);
					inFile.read((char*)&r, 1);
					inFile.read((char*)&x, 1);
					tempArr[rawBitIndex++] = Color{ x,r,g,b };
				}
				inFile.seekg(padding, std::ios::cur);
			}

			int indexOfbitMap = 0;
			for (int i = bitmapHeightInPixel - 1; i >= 0; i--) {
				for (int j = 0; j < bitmapWidthInPixel; j++) {
					bitMap[indexOfbitMap++] = tempArr[i * bitmapWidthInPixel + j];
				}
			}

			delete[] tempArr;
		}

	}



	default: {
		std::cout << "no supports for current format!"; return;
	}
	}



	inFile.close();

}

//void Sprite::GetDraw(Graphics& GFX)
//{
//
//	//Vei2 locationTopLeft = (Vei2)position;
//	Vei2 locationTopLeft;
//	int height;
//	int width;
//
//
//
//	if (locationTopLeft.y + height <= 0 || locationTopLeft.y >= (int)Graphics::ScreenHeight || locationTopLeft.x >= (int)Graphics::ScreenWidth || locationTopLeft.x + width <= 0) {
//	}
//	else {
//
//
//		int startOfXinSurface = max(0 - locationTopLeft.x, 0);
//		int endOfXinSurface = min((int)Graphics::ScreenWidth - locationTopLeft.x, width);// not include
//		int startOfYinSurface = max(0 - locationTopLeft.y, 0);
//		int endOfYinSurface = min((int)Graphics::ScreenHeight - locationTopLeft.y, height);  // not include
//
//
//		int startOfXinScreen = max(locationTopLeft.x, 0);
//		int startOfYinScreen = max(locationTopLeft.y, 0);
//		int endOfXinScreen = min((int)Graphics::ScreenWidth, locationTopLeft.x + width);   // not include
//		int endOfYinScreen = min((int)Graphics::ScreenHeight, locationTopLeft.y + height); // not include;
//
//
//
//		for (size_t i = startOfYinScreen; i < endOfYinScreen; i++)
//		{
//			for (size_t j = startOfXinScreen; j < endOfXinScreen; j++)
//			{
//				GFX.PutPixel(j, i, bitMap[(startOfYinSurface + (i - startOfYinScreen)) * width + startOfXinSurface + (j - startOfXinScreen)]);
//
//
//			}
//		}
//
//	}
//
//}

void Sprite::GetDraw(Graphics& GFX, rect rec, Vec2 p)
{

	//Vei2 locationTopLeft = (Vei2)position;
	Vei2 locationTopLeft = (Vei2)p;//screen location to draw the spirite
	int heightOfRect = rec.bottom - rec.top;
	int widthOfRect = rec.right - rec.left;



	if (locationTopLeft.y + heightOfRect <= 0 || locationTopLeft.y >= (int)Graphics::ScreenHeight || locationTopLeft.x >= (int)Graphics::ScreenWidth || locationTopLeft.x + widthOfRect <= 0) {
	}
	else {


		int startOfXinSurface = max(0 - locationTopLeft.x, 0) + rec.left;
		int endOfXinSurface = min((int)Graphics::ScreenWidth - locationTopLeft.x, widthOfRect);// not include

		int startOfYinSurface = max(0 - locationTopLeft.y, 0) + rec.top;
		int endOfYinSurface = min((int)Graphics::ScreenHeight - locationTopLeft.y, heightOfRect);  // not include


		int startOfXinScreen = max(locationTopLeft.x, 0);
		int startOfYinScreen = max(locationTopLeft.y, 0);
		int endOfXinScreen = min((int)Graphics::ScreenWidth, locationTopLeft.x + widthOfRect);   // not include
		int endOfYinScreen = min((int)Graphics::ScreenHeight, locationTopLeft.y + heightOfRect); // not include;



		for (int i = startOfYinScreen; i < endOfYinScreen; i++)
		{
			for (int j = startOfXinScreen; j < endOfXinScreen; j++)
			{
				Color c = bitMap[(startOfYinSurface + (i - startOfYinScreen)) * width + startOfXinSurface + (j - startOfXinScreen)];
				//* width of the WHOLE BMP
				if (!(c == Colors::Magenta) && !(c == Colors::Black)) {



					GFX.PutPixel(j, i, c);
				}
			}
		}

	}

}



void Sprite::GetDraw(Graphics& GFX, rect rec, Vec2 p, float scaleFactor)
{

	//Vei2 locationTopLeft = (Vei2)position;
	//subtracat p from all points
	//rect is rectangle selected from bitmap to draw to screen


	Vei2 locationTopLeft = (Vei2)p;//screen location to draw the spirite


	int heightOfRect = rec.bottom - rec.top;
	int widthOfRect = rec.right - rec.left;

	int heightOfScaled = (int)((float)heightOfRect * scaleFactor + 0.5f);
	int widthOfScaled = (int)((float)widthOfRect * scaleFactor + 0.5f);


	if (locationTopLeft.y + heightOfScaled <= 0 || locationTopLeft.y >= (int)Graphics::ScreenHeight || locationTopLeft.x >= (int)Graphics::ScreenWidth || locationTopLeft.x + widthOfScaled <= 0) {


	}
	else {


		int startOfXinScreen = max(locationTopLeft.x, 0);
		int startOfYinScreen = max(locationTopLeft.y, 0);
		int endOfXinScreen = min((int)Graphics::ScreenWidth, locationTopLeft.x + widthOfScaled);   // not include
		int endOfYinScreen = min((int)Graphics::ScreenHeight, locationTopLeft.y + heightOfScaled); // not include;

		for (int i = startOfYinScreen; i < endOfYinScreen; i++) {
			int _i = (int)((float)(i - locationTopLeft.y) * (1.f / scaleFactor));
			for (int j = startOfXinScreen; j < endOfXinScreen; j++) {
				int _j = (int)((float)(j - locationTopLeft.x) * (1.f / scaleFactor));
				Color c = bitMap[((_i + rec.top) * width) + (rec.left + _j)];
				if ((c == Colors::Magenta) || (c == Colors::Black)) {
					continue;
				}
				GFX.PutPixel(j, i, c);
			}
		}
	}

}



void Sprite::GetDrawWithoutClipping(Graphics& GFX, rect rec, Vec2 p, float scaleFactor)
{

	int heightOfRect = rec.bottom - rec.top;
	int widthOfRect = rec.right - rec.left;

	for (int i = rec.top; i < rec.bottom; i++) {
		for (int j = rec.left; j < rec.right; j++) {
			Color c = bitMap[i * width + j];
			if (c == Colors::Magenta) {
				continue;
			}

			int xOffSetFromOrigin = (j - rec.left);
			int yOffSetFromOrigin = (i - rec.top);
			Vec2 position = { (float)xOffSetFromOrigin ,(float)yOffSetFromOrigin };

			Mat2 transmationMatrix = Mat2::Rotation(1.f);


			//Mat2 transmationMatrix =  Mat2::Identity() * scaleFactor;



			position = position * transmationMatrix;
			position += p;
			GFX.PutPixel((int)(position.x), (int)(position.y), c);

		}
	}



}
