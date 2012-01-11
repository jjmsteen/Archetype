#pragma once

#include "libPrefix.h"

#include "BoundingVolume.h"
#include "Vector3.h"

namespace AT
{
namespace Bounding
{

class BoundingSphere
	: public BoundingVolume
{

	Maths::Vector3 centre;

	float radius;

protected:

	DLLEXPORT virtual BoundingType GetBoundingType() const { return BOUNDING_SPHERE; }

public:

#pragma region Constructors / Destructor

	DLLEXPORT BoundingSphere(const Maths::Vector3 & centre = Maths::Vector3(), float radius = 1.0f);

	DLLEXPORT virtual ~BoundingSphere(void);

#pragma endregion
    
#pragma region Polymorphic Copying Methods
    
    DLLEXPORT virtual BoundingVolume * Copy() const;
    
#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetCentre() const { return centre; }
    DLLEXPORT void SetCentre(const Maths::Vector3 & centre) { this->centre = centre; }
    
	DLLEXPORT float GetRadius() const { return radius; }
    DLLEXPORT void SetRadius(float radius) { this->radius = radius; }

	DLLEXPORT virtual float GetVolume() const;

#pragma endregion

#pragma region Overridden Intersection Methods

	DLLEXPORT virtual IntersectResult Intersects(const BoundingVolume * bv);

	DLLEXPORT virtual bool DoesRayIntersect(const Ray & ray) const;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingAABB & box) const;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingFrustum & frustum) const;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingSphere & sphere) const;

	DLLEXPORT virtual IntersectResult Intersects(const Maths::Vector3 & point) const;

	DLLEXPORT virtual IntersectResult Intersects(const Plane & plane) const;

#pragma endregion

};

}
}