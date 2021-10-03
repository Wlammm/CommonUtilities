#ifndef CU_VECTOR2_H
#define CU_VECTOR2_H

#include "Vector.h"

namespace cu
{
	template<typename T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2() :
			Vector<T, 2>{}
		{}

		Vector2(const Vector2& vector) :
			Vector<T, 2>{ vector }
		{}

		Vector2(const T& x, const T& y) :
			Vector<T, 2>{ x, y }
		{}

		~Vector2() = default;

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
		#pragma endregion
	};

	#pragma region Type aliases
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;
	using Vector2s = Vector2<short>;
	#pragma endregion
}

#endif