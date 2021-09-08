#pragma once

#include "Vector.h"

namespace CommonUtilities{
template<typename T>
	class Vector4 : public Vector<T, 4>
	{
	public:
		Vector4() :
			Vector<T, 4>{}, x{ Element(0) }, y{ Element(1) }, z{ Element(2) }, w{ Element(3) }
		{}

		Vector4(const Vector4& aVector) :
			Vector<T, 4>{ aVector }, x{ Element(0) }, y{ Element(1) }, z{ Element(2) }, w{ Element(3) }
		{}

		Vector4(const Vector<T, 4>& aVector) :
			Vector<T, 4>{ aVector }, x{ Element(0) }, y{ Element(1) }, z{ Element(2) }, w{ Element(3) }
		{}

		Vector4(const T& x, const T& y, const T& z, const T& w) :
			Vector<T, 4>{ x, y, z }, x{ Element(0) }, y{ Element(1) }, z{ Element(2) }, w{ Element(3) }
		{}

		inline T& X()
		{
			return Element(0);
		}

		inline T& X() const
		{
			return Element(0);
		}

		inline T& Y()
		{
			return Element(1);
		}
		
		inline T& Y() const
		{
			return Element(1);
		}

		inline T& Z()
		{
			return Element(2);
		}

		inline T& Z() const
		{
			return Element(2);
		}
		
		inline T& W()
		{
			return Element(3);
		}

		inline T& W() const
		{
			return Element(3);
		}

	private:
		T& x;
		T& y;
		T& z;
		T& w;
	};

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int>;
	using Vector4ui = Vector4<unsigned int>;
}