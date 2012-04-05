#pragma once
#include "BoundingVolume.h"
#include "libPrefix.h"

#include "Matrix4x4.h"
#include "Plane.h"

namespace AT
{
namespace Bounding
{

class BoundingFrustum :
	public BoundingVolume
{

	// Planes of the frustum for intersection testing
	Plane left;
	Plane right; 
	Plane top; 
	Plane bottom;
	Plane zNear;
	Plane zFar;

	// An array of pointers to the six planes (so looping is possible)
	Plane * planes[6];

protected:

	DLLEXPORT virtual BoundingType GetBoundingType() const { return BOUNDING_FRUSTUM; }

public:

#pragma region Constructors / Destructor

	// The frustum matrix usually comprises the View x Projection matrices
	DLLEXPORT BoundingFrustum(const Maths::Matrix4x4 & frustum = Maths::Matrix4x4());

	DLLEXPORT virtual ~BoundingFrustum(void);

#pragma endregion
    
#pragma region Polymorphic Copying Methods
    
    DLLEXPORT virtual BoundingVolume * Copy() const;
    
#pragma endregion

#pragma region OAO / Copy Constructor

	DLLEXPORT BoundingFrustum(const BoundingFrustum & bf);

	DLLEXPORT BoundingFrustum & operator= (const BoundingFrustum & bf);

private:
	DLLEXPORT void PopulatePointerArray();
public:

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Plane & GetLeft() const { return left; }
	DLLEXPORT const Plane & GetRight() const { return right; }
	DLLEXPORT const Plane & GetTop() const { return top; }
	DLLEXPORT const Plane & GetBottom() const { return bottom; }
	DLLEXPORT const Plane & GetNear() const { return zNear; }
	DLLEXPORT const Plane & GetFar() const { return zFar; }

	DLLEXPORT virtual float GetVolume() const;

	DLLEXPORT virtual AT::Maths::Vector3 GetCentroid() const;

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