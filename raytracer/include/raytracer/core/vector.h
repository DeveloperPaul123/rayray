#pragma once

#include "raytracer/core/nd_base.h"

namespace rayray
{
	template<typename T, std::size_t N>
	class vector : public nd_base<T, N>
	{
	public:
		using self_type = vector;
		using reference = vector & ;
		using parent_type = nd_base<T, N>;
		vector();
		~vector() = default;

		self_type operator-();
		self_type operator*(const T& value);
		self_type operator*=(const T& value);
		self_type operator/(const T& value);
		self_type operator/=(const T& value);
		T length() const;
		T length_squared() const;
		vector to_unit_vector();
	};

	template<typename T>
	inline T dot(const vector<T, 3> &v1, const vector<T, 3> &v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	template<typename T>
	inline vector<T, 3> cross(const vector<T, 3> &v1, const vector<T, 3> &v2)
	{
		return
		{
			v1[1] * v2[2] - v1[2] * v2[1],
			-(v1[0] * v2[2] - v1[2] * v2[0]),
			v1[0] * v2[1] - v1[1] * v2[0]
		};
	}

	template <typename T, std::size_t N>
	vector<T, N>::vector()
		: nd_base<T,N>()
	{

	}

	template <typename T, std::size_t N>
	typename vector<T, N>::self_type vector<T, N>::operator-()
	{
		self_type return_vec(*this);

		return return_vec *= -1.0;
	}

	template <typename T, std::size_t N>
	typename vector<T, N>::self_type vector<T, N>::operator*(const T& value)
	{
		return *this *= value;
	}

	template <typename T, std::size_t N>
	typename vector<T, N>::self_type vector<T, N>::operator*=(const T& value)
	{
		for(auto i = 0; i < N; i++)
		{
			parent_type::data_[i] *= value;
		}

		return *this;
	}

	template <typename T, std::size_t N>
	typename vector<T, N>::self_type vector<T, N>::operator/(const T& value)
	{
		return *this /= value;
	}

	template <typename T, std::size_t N>
	typename vector<T, N>::self_type vector<T, N>::operator/=(const T& value)
	{
		for(auto i = 0; i < N; i++)
		{
			parent_type::data_[i] /= value;
		}
		return *this;
	}

	template <typename T, std::size_t N>
	T vector<T, N>::length() const
	{
		T square_sum = length_squared();

		return std::sqrt(square_sum);
	}

	template <typename T, std::size_t N>
	T vector<T, N>::length_squared() const
	{
		T square_sum;

		for(auto i = 0; i < N; i++)
		{
			square_sum += std::pow(parent_type::data_, 2.0);
		}

		return square_sum;
	}

	template <typename T, std::size_t N>
	vector<T, N> vector<T, N>::to_unit_vector()
	{
		T k = 1.0 / length();
		return { parent_type::data_[0] * k, parent_type::data_[1] * k, parent_type::data_[2] * k };
	}
}
