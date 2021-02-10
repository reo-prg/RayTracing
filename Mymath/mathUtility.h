#pragma once

namespace math_util
{
	/// <summary>
	/// �Z�p�^�̒l��2�悷��
	/// </summary>
	/// <param name="val">2�悷��l</param>
	template<typename T>
	T Double(const T& val)
	{
		static_assert(std::is_arithmetic<T>::value);

		return val * val;
	}
}
