#pragma once

#include "Plane.hpp"
#include "AABB3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

namespace CommonUtilities
{
	// If the ray is parallel to the plane, aOutIntersectionPoint remains unchanged. If
	// the ray is in the plane, true is returned, if not, false is returned. If the ray
	// isn't parallel to the plane, the intersection point is stored in
	// aOutIntersectionPoint and true returned.
	template <typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint);

	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// A ray in one of the AABB's sides is counted as intersecting it.
	template <typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay);

	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// A rat intersecting the surface of the sphere is considered as intersecting it.
	template <typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay);

	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		const T dnDot = aRay.GetDirection().Dot(aPlane.GetNormal());

		bool isInside = aPlane.IsInside(aRay.GetOrigin());
		if ((isInside && dnDot <= 0) || (!isInside && dnDot >= 0))
		{
			return false; // Parallel
		}

		T planeD = aPlane.GetPoint().Dot(aPlane.GetNormal());
		T length = (planeD - aRay.GetOrigin().Dot(aPlane.GetNormal())) / dnDot;

		aOutIntersectionPoint = aRay.GetOrigin() + aRay.GetDirection() * length;
		return true;
	}

	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{
		Plane<T> planes[6];
		// Right
		planes[0] = Plane<T>(
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMaxPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMinPoint.y, aAABB.myMinPoint.z));
		// Front
		planes[1] = Plane<T>(
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMaxPoint.y, aAABB.myMinPoint.z),
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMinPoint.y, aAABB.myMinPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMinPoint.z));
		// Left
		planes[2] = Plane<T>(
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMaxPoint.y, aAABB.myMinPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMinPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z));
		// Back
		planes[3] = Plane<T>(
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMaxPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z));
		// Up
		planes[4] = Plane<T>(
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMaxPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMaxPoint.y, aAABB.myMinPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMaxPoint.y, aAABB.myMinPoint.z));
		// Down
		planes[5] = Plane<T>(
			Vector3<T>(aAABB.myMaxPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMaxPoint.z),
			Vector3<T>(aAABB.myMinPoint.x, aAABB.myMinPoint.y, aAABB.myMinPoint.z));


		for (int i = 0; i < 6; i++)
		{
			const T dnDot = aRay.GetDirection().Dot(planes[i].GetNormal());
			bool isInside = planes[i].IsInside(aRay.GetOrigin());

			if ((isInside && dnDot <= 0) || (!isInside && dnDot >= 0))
			{
				continue; // Parallel or wrong side
			}

			T planeD = planes[i].GetPoint().Dot(planes[i].GetNormal());
			T length = (planeD - aRay.GetOrigin().Dot(planes[i].GetNormal())) / dnDot;

			CU::Vector3<T> hit = aRay.GetOrigin() + aRay.GetDirection() * length;

			bool hitSucceed = true;
			for (int x = 0; x < 6; x++)
			{
				if (x != i)
				{
					if (!planes[x].IsInside(hit))
					{
						hitSucceed = false;
						break;
					}
				}
			}
			if (hitSucceed)
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> e = aSphere.GetCenter() - aRay.GetOrigin();

		T a = e.Dot(aRay.GetDirection().GetNormalized());
		T eSqr = e.LengthSqr();
		T rSqr = aSphere.GetRadiusSqr();
		T aSqr = a * a;
		T fSqr = rSqr - (eSqr + aSqr);
		if (rSqr - (eSqr - aSqr) < 0.0f)
		{
			return false; // INVALID
		}
		if (eSqr < aSqr)
		{
			return true; // INSIDE
		}
		return true;
	}
}

namespace CU = CommonUtilities;