#ifndef CU_PAIR_H
#define CU_PAIR_H

namespace cu
{
	template<typename FirstT, typename SecondT>
	class Pair
	{
	private:
		FirstT first;
		SecondT second;

	public:
		Pair()
		{}

		Pair(const FirstT& first, const SecondT& second) :
			first{ first },
			second{ second }
		{}

		Pair(const Pair& pair) :
			Pair{ pair.first, pair.second }
		{}

		bool operator==(const Pair& pair)
		{
			return first == pair.first && second == pair.second;
		}

		#pragma region Elements
		FirstT& First()
		{
			return first;
		}

		const FirstT& First() const
		{
			return first;
		}

		SecondT& Second()
		{
			return second;
		}

		const SecondT& Second() const
		{
			return second;
		}
		#pragma endregion
	};
}

#endif