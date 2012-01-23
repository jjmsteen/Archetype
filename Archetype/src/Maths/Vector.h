#pragma once

#include <string>
#include "libPrefix.h"

namespace AT
{
namespace Maths
{

	class Vector
	{

	public:

		virtual float Length() const = 0;

		virtual float LengthSquared() const = 0;

		virtual void Normalise() = 0;

		//virtual std::string ToString() const = 0;

		Vector();

		//virtual ~Vector();
		
	};

}
}
