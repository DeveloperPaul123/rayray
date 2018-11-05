#pragma once

#include "raytracer/core/nd_base.h"
#include "point.h"

#include <cmath>

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
		vector(std::initializer_list<T> elements);
		explicit vector(std::array<T, N> data);
		~vector() = default;

		operator point<T, N>();
		self_type operator-();
		self_type operator*(const T& value);
		self_type operator*=(const T& value);
		self_type operator/(const T& value);
		self_type operator/=(const T& value);
		T length() const;
		T length_squared() const;
		vector to_unit_vector();

		typename nd_base<T, N>::value_type x() const;
		template<class S = typename nd_base<T, N>::value_type>
		typename std::enable_if<N >= 2, S>::type y() const;
		template<class S = typename nd_base<T, N>::value_type>
		typename std::enable_if<N >= 3, S>::type z() const;
	};

#pragma region Implementation
	template <typename T, std::size_t N>
	vector<T, N>::vector()
		: nd_base<T,N>()
	{

	}

	template <typename T, std::size_t N>
	vector<T, N>::vector(std::initializer_list<T> elements)
		:nd_base<T, N>(elements)
	{
	}

	template <typename T, std::size_t N>
	vector<T, N>::vector(std::array<T, N> data)
		:nd_base<T, N>(data)
	{
	}

	template <typename T, std::size_t N>
	vector<T, N>::operator point<T, N>()
	{
		point<T, N> result;
		for (auto i = 0; i < N; i++)
		{
			result[i] = nd_base<T, N>::data_[i];
		}
		return result;
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
		T square_sum{};

		for(auto i = 0; i < N; i++)
		{
			square_sum += std::pow(parent_type::data_[i], 2.0);
		}

		return square_sum;
	}

	template <typename T, std::size_t N>
	vector<T, N> vector<T, N>::to_unit_vector()
	{
		T k = 1.0 / length();
		return { parent_type::data_[0] * k, parent_type::data_[1] * k, parent_type::data_[2] * k };
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::value_type vector<T, N>::x() const
	{
		return nd_base<T, N>::data_[0];
	}

	template <typename T, std::size_t N>
	template <class S>
	typename std::enable_if<N >= 2, S>::type vector<T, N>::y() const
	{
		return nd_base<T, N>::data_[1];
	}

	template <typename T, std::size_t N>
	template <class S>
	typename std::enable_if<N >= 3, S>::type vector<T, N>::z() const
	{
		return nd_base<T, N>::data_[2];
	}
#pragma endregion
#pragma region Helper functions
	template<typename T>
	T dot(const vector<T, 3> &v1, const vector<T, 3> &v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	template<typename T>
	vector<T, 3> cross(const vector<T, 3> &v1, const vector<T, 3> &v2)
	{
		return
		{
			v1[1] * v2[2] - v1[2] * v2[1],
			-(v1[0] * v2[2] - v1[2] * v2[0]),
			v1[0] * v2[1] - v1[1] * v2[0]
		};
	}

	template<typename T, std::size_t N>
	vector<T, N> operator+(const vector<T, N>& first, const vector<T, N>& second)
	{
		std::array<T, N> data;
		for(auto i = 0; i < N; i++)
		{
			data[i] = first[i] + second[i];
		}

		return vector<T, N>(data);
	}

	template<typename T, std::size_t N>
	vector<T, N> operator*(const T& value, const vector<T, N>& vec)
	{
		vector<T, N> return_data;

		for(auto i = 0; i < N; i++)
		{
			return_data[i] = vec[i] * value;
		}

		return return_data;
	}

	template<typename T, std::size_t N>
	vector<T, N> operator-(const point<T, N> &first, const vector<T, N> &second)
	{
		vector<T, N> result;
		for(auto i = 0; i < N; i++)
		{
			result[i] = first[i] - second[i];
		}
		return result;
	}

	template<typename T, std::size_t N>
	vector<T, N> operator-(const vector<T, N> &first, const point<T, N> &second)
	{
		vector<T, N> result;
		for(auto i = 0; i < N; i++)
		{
			result[i] = first[i] - second[i];
		}
		return result;
	}

	template<typename T, std::size_t N>
	vector<T, N> operator/(const vector<T, N> &input, const T& value)
	{
		vector<T, N> result = input;
		for(auto i = 0; i < N; i++)
		{
			result[i] /= value;
		}

		return result;
	}
#pragma endregion
}
