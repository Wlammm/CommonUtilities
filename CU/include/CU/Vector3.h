#ifndef CU_VECTOR3_H
#define CU_VECTOR3_H

#include "Vector.h"

namespace cu
{
	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3() :
			Vector<T, 3>{}
		{}

		Vector3(const Vector3& vector) :
			Vector<T, 3>{ vector }
		{}

		Vector3(const T& x, const T& y, const T& z) :
			Vector<T, 3>{ x, y, z }
		{}

		~Vector3() = default;

		#pragma region Elements
		inline T& X()
		{
			return this->Element(0);
		}

		inline const T& X() const
		{
			return this->Element(0);
		}

		inline T& Y()
		{
			return this->Element(1);
		}

		inline const T& Y() const
		{
			return this->Element(1);
		}

		inline T& Z()
		{
			return this->Element(2);
		}

		inline const T& Z() const
		{
			return this->Element(2);
		}
		#pragma endregion

		// Calculates the cross product of this vector and another vector.
		Vector3 Cross(const Vector3& vector)
		{
			return Vector3{ Y() * vector.Z() - Z() * vector.Y(), Z() * vector.X() - X() * vector.Z(), X() * vector.Y() - Y() * vector.X() };
		}
	};

	#pragma region Type aliases
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;
	using Vector3s = Vector3<short>;
	#pragma endregion
}

#endif