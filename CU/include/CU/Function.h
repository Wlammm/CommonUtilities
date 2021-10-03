#ifndef CU_FUNCTION_H
#define CU_FUNCTION_H

namespace cu
{
	template<typename ReturnT, typename... ArgumentT>
	class Function
	{
	private:
		using FunctionPointer = ReturnT(*)(ArgumentT...);

		FunctionPointer function;

	public:
		Function() :
			function{}
		{}

		Function(const FunctionPointer& function) :
			function{ function }
		{}

		~Function() = default;

		// Gets the target function.
		FunctionPointer& Target()
		{
			return function;
		}

		// Sets the target function.
		void SetFunction(const FunctionPointer& function)
		{
			this->function = function;
		}

		#pragma region Operators
		inline ReturnT operator()(ArgumentT&... argument)
		{
			return function(argument...);
		}

		inline Function& operator=(const Function& function)
		{
			this->function = function.function;
			return *this;
		}

		inline Function& operator=(const FunctionPointer& function)
		{
			this->function = function;
			return *this;
		}

		inline bool operator==(const Function& function) const
		{
			return this->function == function.function;
		}

		inline bool operator==(const FunctionPointer& function) const
		{
			return this->function == function;
		}
		#pragma endregion
	};
}

#endif