#pragma once

#include "libPrefix.h"

namespace AT
{
namespace Model
{

class Colour
{

	float r, g, b, a;

public:

#pragma region Constructors / Destructor

	DLLEXPORT Colour();

	DLLEXPORT Colour(float red, float green, float blue, float alpha);

	DLLEXPORT Colour(float red, float green, float blue);

	DLLEXPORT Colour(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

	DLLEXPORT ~Colour(void);

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT void SetRed(float red);
	DLLEXPORT void SetRed(unsigned char red);
	DLLEXPORT float GetRed() const;

	DLLEXPORT void SetGreen(float green);
	DLLEXPORT void SetGreen(unsigned char green);
	DLLEXPORT float GetGreen() const;

	DLLEXPORT void SetBlue(float blue);
	DLLEXPORT void SetBlue(unsigned char blue);
	DLLEXPORT float GetBlue() const;
	
	DLLEXPORT void SetAlpha(float alpha);
	DLLEXPORT void SetAlpha(unsigned char alpha);
	DLLEXPORT float GetAlpha() const;

#pragma endregion

};

}
}