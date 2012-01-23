 
#include "stdafx.h"

#include "Colour.h"

using namespace AT;
using namespace Model;

float Clamp(float value)
{
	// Clamp the value to between 1.0 and 0.0
	if (value > 1.0f) value = 1.0f;
	else if (value < 0.0f) value = 0.0f;

	return value;
}

Colour::Colour()
	: r(0), g(0), b(0), a(1)
{
}

Colour::Colour(float red, float green, float blue, float alpha)
	: r(Clamp(red)),g(Clamp(green)), 
	b(Clamp(blue)), a(Clamp(alpha)) 
{
}

Colour::Colour(float red, float green, float blue)
	: r(Clamp(red)),g(Clamp(green)), b(Clamp(blue)), a(1.0)
{
}

Colour::Colour(unsigned char red, unsigned char green, 
	unsigned char blue, unsigned char alpha)
	: r(red / 255.0), g(green / 255.0), 
	b(blue / 255.0), a(alpha / 255.0)
{
}

Colour::~Colour(void)
{
}

void Colour::SetRed(float red)
{
	// Set the clamped value
	r = Clamp(red);
}

void Colour::SetRed(unsigned char red)
{
	r = red / 255.0f;
}

float Colour::GetRed() const { return r; }

void Colour::SetGreen(float green)
{
	// Set the clamped value
	g = Clamp(green);
}

void Colour::SetGreen(unsigned char green)
{
	g = green / 255.0f;
}

float Colour::GetGreen() const { return g; }

void Colour::SetBlue(float blue)
{
	// Set the clamped value
	b = Clamp(blue);
}

void Colour::SetBlue(unsigned char blue)
{
	b = blue / 255.0f;
}

float Colour::GetBlue() const { return b; }
	
void Colour::SetAlpha(float alpha)
{
	// Set the clamped value
	a = Clamp(alpha);
}

void Colour::SetAlpha(unsigned char alpha)
{
	a = alpha / 255.0f;
}

float Colour::GetAlpha() const { return a; }