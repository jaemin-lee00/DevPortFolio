# define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class SpriteTransforms : public olc::PixelGameEngine {

public :
	SpriteTransforms() {
		
		sAppName = "Sprtie Transfomrs";
	}

private :
	olc::Sprite* sprCar;

public :
	bool OnUserCreate() override {
	
		sprCar = new olc::Sprite("car_top1.png");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		
		Clear(olc::DARK_CYAN);

		SetPixelMode(olc::Pixel::ALPHA);
		DrawSprite(0, 0, sprCar);
		
		SetPixelMode(olc::Pixel::NORMAL);

		return true;
	}

};

int main() {

	SpriteTransforms demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}