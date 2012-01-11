#pragma once
#include "libPrefix.h"

#include "BoundingVolume.h"
#include "Vector3.h"

namespace AT
{
namespace Bounding
{

class BoundingAABB :
	public BoundingVolume
{
	// The minimum point of the axis alinged box
	// (the smallest on the x, y, z axes)
	Maths::Vector3 minPoint;

	// The maximum point of the axis aligned box
	// (the largest on the x, y, z axes)
	Maths::Vector3 maxPoint;

protected:

	DLLEXPORT virtual BoundingType GetBoundingType() const { return BOUNDING_AABB; }

public:

	// The world transform of the box
	Maths::Vector3 transform;

#pragma region Constructors / Destructor

	DLLEXPORT BoundingAABB(const Maths::Vector3 & minPoint = Maths::Vector3(-1,-1,-1), 
		const Maths::Vector3 & maxPoint = Maths::Vector3(1,1,1), const Maths::Vector3 & transform = Maths::Vector3());

	DLLEXPORT virtual ~BoundingAABB(void);

#pragma endregion
    
#pragma region Polymorphic Copying Methods
    
    DLLEXPORT virtual BoundingVolume * Copy() const;
    
#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT Maths::Vector3 GetMin() const { return minPoint + transform; }
	DLLEXPORT Maths::Vector3 GetMax() const { return maxPoint + transform; }

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