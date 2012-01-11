#pragma once

#include "libPrefix.h"

#include "Matrix4x4.h"
#include "Ray.h"

namespace AT
{
namespace Bounding
{

// An enum to declare results that can be 
// given by bounding tests
typedef enum 
{
	NO_OVERLAP,
	INTERSECTS,
	CONTAINS
} IntersectResult;

// Forward declarations of classes
class BoundingAABB;
class BoundingFrustum;
class BoundingSphere;
class Plane;

class BoundingVolume
{
public:

	// An enum to keep track of the way the 
	// bounding volume should be interpreted
	// (the fastest cross platform way of doing so)
	enum BoundingType
	{
		BOUNDING_AABB,
		BOUNDING_SPHERE,
		BOUNDING_FRUSTUM
	};

	// A protected function to access this bounding type without 
	// using typeid() and expensive string comparisons
	DLLEXPORT virtual BoundingType GetBoundingType() const = 0;

	DLLEXPORT BoundingVolume();

	DLLEXPORT virtual ~BoundingVolume(void);
    
#pragma region Polymorphic Copying Methods
    
    DLLEXPORT virtual BoundingVolume * Copy() const = 0;
    
#pragma endregion

	// Get the 'volume' or spatial displacement of the volume
	DLLEXPORT virtual float GetVolume() const = 0;

#pragma region Abstract Intersection Methods

	DLLEXPORT virtual IntersectResult Intersects(const BoundingVolume * bv) const;

	DLLEXPORT virtual bool DoesRayIntersect(const Ray & ray) const = 0;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingAABB & box) const = 0;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingFrustum & frustum) const = 0;

	DLLEXPORT virtual IntersectResult Intersects(const BoundingSphere & sphere) const = 0;

	DLLEXPORT virtual IntersectResult Intersects(const Maths::Vector3 & point) const = 0;

	DLLEXPORT virtual IntersectResult Intersects(const Plane & plane) const = 0;

#pragma endregion

};

}
}