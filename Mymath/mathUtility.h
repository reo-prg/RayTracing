#pragma once

namespace math_util
{
	/// <summary>
	/// ZpŒ^‚Ì’l‚ğ2æ‚·‚é
	/// </summary>
	/// <param name="val">2æ‚·‚é’l</param>
	template<typename T>
	T Double(const T& val)
	{
		static_assert(std::is_arithmetic<T>::value);

		return val * val;
	}
}
