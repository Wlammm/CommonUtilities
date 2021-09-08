#pragma once

#include "Vector.h"

namespace CommonUtilities
{
	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3() :
			Vector<T, 3>{}, x{ this->Element(0) }, y{ this->Element(1) }, z{ this->Element(2) }
		{}

		Vector3(const Vector3& aVector) :
			Vector<T, 3>{ aVector }, x{ this->Element(0) }, y{ this->Element(1) }, z{ this->Element(2) }
		{}

		Vector3(const Vector<T, 3>& aVector) :
			Vector<T, 3>{ aVector }, x{ this->Element(0) }, y{ this->Element(1) }, z{ this->Element(2) }
		{}

		Vector3(const T& x, const T& y, const T& z) :
			Vector<T, 3>{ x, y, z }, x{ this->Element(0) }, y{ this->Element(1) }, z{ this->Element(2) }
		{}

		~Vector3() = default;

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

		Vector3 Cross(const Vector3& aVector)
		{
			return Vector3{ Y() * aVector.Z() - Z() * aVector.Y(), Z() * aVector.X() - X() * aVector.Z(), X() * aVector.Y() - Y() * aVector.X() };
		}

		static Vector3<float> Reflect(const Vector3<float>& aDirection, const Vector3<float>& aNormal)
		{
			return aNormal * (-2.f * aNormal.Dot(aDirection)) + aDirection;
		}

	private:
		T& x;
		T& y;
		T& z;
	};

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;
}