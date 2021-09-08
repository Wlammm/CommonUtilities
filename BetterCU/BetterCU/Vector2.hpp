#pragma once

#include "Vector.h"

namespace CommonUtilities
{
	template<typename T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2()
			: Vector<T, 2>{}, x{ this->Element(0) }, y{ this->Element(1) }
		{}

		Vector2(const Vector2& vector) :
			Vector<T, 2>{ vector }, x{ this->Element(0) }, y{ this->Element(1) }
		{}

		Vector2(const T& x, const T& y) :
			Vector<T, 2>{ x, y }, x{ this->Element(0) }, y{ this->Element(1) }
		{}

		~Vector2() = default;

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

		const std::string ToString()
		{
			return "NEJ TACK";
		}

	private:
		T& x;
		T& y;
	};

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;
	using Vector2ui = Vector2<unsigned int>;
}