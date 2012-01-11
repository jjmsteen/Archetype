#pragma once

#include <cmath>

namespace AT
{
	namespace Maths
	{
		// A constant representing pi
		const double PI = 3.141592653589793238462643383279502884197;

		// Inline functions for converting between radians and degrees
		inline double RadiansToDegrees(double radians) { return radians * (180.0 / PI); }
		inline double DegreesToRadians(double degrees) { return PI * (degrees / 180.0); }

		inline float ZeroSmallFloat(float f) { return (fabs(f) < 0.00001) ? 0.0f : f; }
        
        // Lerping functions
        inline double Lerp(double low, double high, double value) { return low + (high - low) * value; }
	}
}