#pragma once

#include "Vector.h"

namespace CommonUtilities
{
	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3() :
			Vector<T, 3>{}
		{}

		Vector3(const Vector3& aVector) :
			Vector<T, 3>{ aVector }
		{}

		Vector3(const Vector<T, 3>& aVector) :
			Vector<T, 3>{ aVector }
		{}

		Vector3(const T& x, const T& y, const T& z) :
			Vector<T, 3>{ x, y, z }
		{}

		~Vector3() = default;

		inline T& X()
		{
			return Element(0);
		}

		inline const T& X() const
		{
			return Element(0);
		}

		inline T& Y()
		{
			return Element(1);
		}

		inline const T& Y() const
		{
			return Element(1);
		}

		inline T& Z()
		{
			return Element(2);
		}

		inline const T& Z() const
		{
			return Element(2);
		}

		Vector3 Cross(const Vector3& aVector)
		{
			return Vector3{ Y() * vector.Z() - Z() * vector.Y(), Z() * vector.X() - X() * vector.Z(), X() * vector.Y() - Y() * vector.X() };
		}

		static Vector3<float> Reflect(const Vector3<float>& anInDirection, const Vector3<float>& aNormal)
		{
			return (aNormal + anInDirection) * -2.f * aNormal.Dot(anInDirection);
		}
	};

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;
}