#pragma once
#include <ostream>

#include "raytracer/core/nd_base.h"

namespace rayray
{
#pragma region Point class declaration
	template<typename T, std::size_t N = 2>
	class point : public nd_base<T, N>
	{
	public:
		using point_type = point<T, N>;
		using reference = point<T, N>&;
		using pointer = point<T, N>*;

		point();
		explicit point(const T& x);
		point(const T& x, const T& y);
		point(const T& x, const T& y, const T& z);

		typename nd_base<T, N>::value_type x() const;

		template<class S = typename nd_base<T, N>::value_type>
		typename std::enable_if<N >= 2, S>::type y() const;

		template<class S = typename nd_base<T, N>::value_type>
		typename std::enable_if<N >= 3, S>::type z() const;
	};
#pragma endregion 

#pragma region Implementation
	template <typename T, std::size_t N>
	point<T, N>::point()
		: nd_base<T, N>()
	{
	}

	template <typename T, std::size_t N>
	point<T, N>::point(const T& x)
	{
		nd_base<T, N>::data_[0] = x;
	}

	template <typename T, std::size_t N>
	point<T, N>::point(const T& x, const T& y)
	{
		static_assert(N >= 2, "X,Y constructor only available in 2D+");
		nd_base<T, N>::data_[0] = x;
		nd_base<T, N>::data_[1] = y;
	}

	template <typename T, std::size_t N>
	point<T, N>::point(const T& x, const T& y, const T& z)
	{
		static_assert(N >= 3, "X,Y,Z constructor only available in 3D+");
		nd_base<T, N>::data_[0] = x;
		nd_base<T, N>::data_[1] = y;
		nd_base<T, N>::data_[2] = z;
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::value_type point<T, N>::x() const
	{
		return nd_base<T, N>::data_[0];
	}

	template <typename T, std::size_t N>
	template <class S>
	typename std::enable_if<N >= 2, S>::type point<T, N>::y() const
	{
		return nd_base<T, N>::data_[1];
	}

	template <typename T, std::size_t N>
	template <class S>
	typename std::enable_if<N >= 3, S>::type point<T, N>::z() const
	{
		return nd_base<T, N>::data_[2];
	}
#pragma endregion 

#pragma region Utility functions

	template<typename PointType, typename T = typename PointType::value_type,
		typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
		inline T distance(const PointType &first, const PointType &second)
	{
		// holder for the sum of squares.
		T square_sum = T();
		auto dimension = first.dimension();
		for (std::size_t i = 0; i < dimension; i++)
		{
			// add the sum square.
			square_sum += std::pow(second[i] - first[i], 2);
		}

		// return the square root of the sum of squares.
		return std::sqrt(square_sum);
	}

	template<std::size_t N, typename Iterator, class PointType = typename std::iterator_traits<Iterator>::value_type,
		typename DataType = typename PointType::value_type>
		inline point<double, N> centroid(Iterator begin, Iterator end)
	{
		auto length = std::distance(begin, end);
		// holder for the sum in each dimension from 0 to N. 
		std::array<double, N> dimensions{};
		for (auto itr = begin; itr != end; ++itr)
		{
			// get the point.
			auto point = *itr;
			for (auto i = 0; i < N; i++)
			{
				// add the dimension value to the holder array.
				dimensions[i] += static_cast<double>(point[i]);
			}
		}

		// calculate the centroid by dividing by the number of points. 
		for (auto i = 0; i < N; i++)
		{
			dimensions[i] = dimensions[i] / static_cast<double>(length);
		}

		// return the centroid point.
		return point<double, N>(dimensions);
	}

	template<std::size_t N, typename InputType, typename OutputType>
	inline point<OutputType, N> convertPoint(const point<InputType, N> &input)
	{
		std::array<OutputType, N> data;
		for (auto i = 0; i < N; i++)
		{
			data[i] = static_cast<OutputType>(input[i]);
		}

		return point<OutputType, N>(data);
	}

	template<std::size_t N,
		typename OutputType,
		typename InputPointType,
		typename InputType = typename InputPointType::value_type,
		typename = typename std::enable_if<std::is_floating_point<InputType>::value>::type,
		typename = typename std::enable_if<std::is_integral<OutputType>::value>::type>
		inline point<OutputType, N> convertPointWithRounding(const InputPointType &input)
	{
		std::array<OutputType, N> data{};
		for (auto i = 0; i < N; i++)
		{
			data[i] = static_cast<OutputType>(std::round(input[i]));
		}

		return point<OutputType, N>(data);
	}
#pragma endregion
}
