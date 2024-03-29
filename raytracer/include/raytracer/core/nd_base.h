#pragma once
#include <ostream>
#include <array>
#include <iomanip>
#include <type_traits>

namespace rayray
{
    template<typename T, std::size_t N>
	class nd_base
    {
		static_assert(std::is_arithmetic<T>::value, "T must be a numeric type.");
		static_assert(N > 0, "Size must be positive and greater than 0.");

    public:
		using value_type = T;
		using value_type_reference = T & ;
		using size_type = std::size_t;
		using iterator = typename std::array<T, N>::iterator;
		using const_iterator = typename std::array<T, N>::const_iterator;

		nd_base();
		~nd_base() = default;
		explicit nd_base(const T&& default_value);
		explicit nd_base(std::array<T, N> data);
		nd_base(std::initializer_list<T> data);
	
		static std::size_t dimension();

		value_type_reference operator[](const std::size_t& index);
		value_type operator[](const std::size_t& index) const;

		nd_base operator+(const T& value);
		nd_base& operator+=(const T& value);
		nd_base operator-(const T& value);
		nd_base& operator-=(const T& value);
		nd_base operator+(const nd_base<T, N>& other);
		nd_base& operator+=(const nd_base<T, N>& other);
		nd_base operator-(const nd_base<T, N>& other);
		nd_base& operator-=(const nd_base<T, N>& other);
        nd_base operator/(const T& value);
        nd_base& operator/=(const T& value);
        nd_base operator*(const T& value);
        nd_base& operator*=(const T& value);

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
    protected:
		std::array<T, N> data_;
	};

	template <typename T, std::size_t N>
	nd_base<T, N>::nd_base()
	{
		std::fill(begin(), end(), T());
	}

	template <typename T, std::size_t N>
	nd_base<T, N>::nd_base(const T&& default_value)
	{
		std::fill(begin(), end(), default_value);
	}

	template <typename T, std::size_t N>
	nd_base<T, N>::nd_base(std::array<T, N> data)
		: data_(std::move(data))
	{
	}

	template <typename T, std::size_t N>
	nd_base<T, N>::nd_base(std::initializer_list<T> data)
	{
		if (data.size() != N)
		{
			throw std::runtime_error("Initializer list size must match size of nd_base.");
		}
		std::copy(data.begin(), data.end(), data_.begin());
	}

	template <typename T, std::size_t N>
	std::size_t nd_base<T, N>::dimension()
	{
		return N;
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::value_type_reference nd_base<T, N>::operator[](const std::size_t& index)
	{
		if (index >= N)
		{
			throw std::runtime_error("Index out of bounds.");
		}
		return data_[index];
	}

	template <typename T, std::size_t N>
	T nd_base<T, N>::operator[](const std::size_t& index) const
	{
		if (index >= N)
		{
			throw std::runtime_error("Index out of bounds.");
		}
		return data_[index];
	}

	template <typename T, std::size_t N>
	nd_base<T, N> nd_base<T, N>::operator+(const T& value)
	{
		return *this += value;
	}

	template <typename T, std::size_t N>
	nd_base<T, N>& nd_base<T, N>::operator+=(const T& value)
	{
		for(auto i = 0; i < N; i++)
		{
			data_[i] += value;
		}
		return *this;
	}

	template <typename T, std::size_t N>
	nd_base<T, N> nd_base<T, N>::operator-(const T& value)
	{
		return *this -= value;
	}

	template <typename T, std::size_t N>
	nd_base<T, N>& nd_base<T, N>::operator-=(const T& value)
	{
		for (auto i = 0; i < N; i++)
		{
			data_[i] -= value;
		}
		return *this;
	}

	template <typename T, std::size_t N>
	nd_base<T, N> nd_base<T, N>::operator+(const nd_base<T, N>& other)
	{
		return *this += other;
	}

	template <typename T, std::size_t N>
	nd_base<T, N>& nd_base<T, N>::operator+=(const nd_base<T, N>& other)
	{
		for(auto i = 0; i < N; i++)
		{
			data_[i] += other[i];
		}
		return *this;
	}

	template <typename T, std::size_t N>
	nd_base<T, N> nd_base<T, N>::operator-(const nd_base<T, N>& other)
	{
		return *this -= other;
	}

	template <typename T, std::size_t N>
	nd_base<T, N>& nd_base<T, N>::operator-=(const nd_base<T, N>& other)
	{
		for(auto i = 0; i < N; i++)
		{
			data_[i] -= other[i];
		}
		return *this;
	}

    template <typename T, std::size_t N>
    nd_base<T, N> nd_base<T, N>::operator/(const T& value)
    {
        return *this /= value;
    }

    template <typename T, std::size_t N>
    nd_base<T, N>& nd_base<T, N>::operator/=(const T& value)
    {
        for(auto i = 0; i < N; i++)
        {
            data_[i] /= value;
        }

        return *this;
    }

    template <typename T, std::size_t N>
    nd_base<T, N> nd_base<T, N>::operator*(const T& value)
    {
        return *this *= value;
    }

    template <typename T, std::size_t N>
    nd_base<T, N>& nd_base<T, N>::operator*=(const T& value)
    {
        for(auto i = 0; i < N; i++)
        {
            data_[i] *= value;
        }
        return *this;
    }

    template <typename T, std::size_t N>
	typename nd_base<T, N>::iterator nd_base<T, N>::begin()
	{
		return data_.begin();
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::iterator nd_base<T, N>::end()
	{
		return data_.end();
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::const_iterator nd_base<T, N>::begin() const
	{
		return data_.begin();
	}

	template <typename T, std::size_t N>
	typename nd_base<T, N>::const_iterator nd_base<T, N>::end() const
	{
		return data_.end();
	}

#pragma region Comparison overloads

	template <typename T, std::size_t N>
	inline nd_base<T, N> operator/(const nd_base<T, N> &input, const T& value)
	{
		auto result = input;
		for(auto i = 0; i < N; i++)
		{
			result[i] /= value;
		}
		return result;
	}

	template<typename T, std::size_t N>
	inline nd_base<T, N> operator-(const nd_base<T, N> &first, const nd_base<T, N> &second)
	{
		nd_base<T, N> result;
		for(auto i = 0; i < N; i++)
		{
			result[i] = first[i] - second[i];
		}

		return result;
	}

	template<typename T, std::size_t N>
	inline bool operator>=(const nd_base<T, N>& lhs, const nd_base<T, N>& rhs)
	{
		std::size_t depth = 0;
		while (true)
		{
			if (lhs[depth] == rhs[depth] && depth < N)
			{
				depth++;
			}
			else if (depth == N)
			{
				// points equal.
				return true;
			}
			return lhs[depth] >= rhs[depth];
		}
	}

	template<typename T, std::size_t N>
	inline bool operator>(const nd_base<T, N>& lhs, const nd_base<T, N> &rhs)
	{
		std::size_t depth = 0;
		while (true)
		{
			if (lhs[depth] == rhs[depth] && depth < N)
			{
				depth++;
			}
			else if (depth == N)
			{
				// points are equal so comparison is false.
				return false;
			}
			return lhs[depth] > rhs[depth];
		}
	}

	template<typename T, std::size_t N>
	inline bool operator<=(const nd_base<T, N>& lhs, const nd_base<T, N> &rhs)
	{
		std::size_t depth = 0;
		while (true)
		{
			if (lhs[depth] == rhs[depth] && depth < N)
			{
				depth++;
			}
			else if (depth == N)
			{
				// points are equal.
				return true;
			}
			return lhs[depth] <= rhs[depth];
		}
	}

	template<typename T, std::size_t N>
	inline bool operator<(const nd_base<T, N>& lhs, const nd_base<T, N> &rhs)
	{
		std::size_t depth = 0;
		while (true)
		{
			if (lhs[depth] == rhs[depth] && depth < N)
			{
				depth++;
			}
			else if (depth == N)
			{
				// points are equal so 
				return false;
			}
			return lhs[depth] < rhs[depth];
		}
	}

	template<typename T, std::size_t N>
	inline bool operator==(const nd_base<T, N> &lhs, const nd_base<T, N> &rhs)
	{
		auto result = true;
		for (auto i = 0; i < N; i++)
		{
			if (lhs[i] != rhs[i])
			{
				result = false;
				break;
			}
		}

		return result;
	}
#pragma endregion 

#pragma region Utility functions
	template<std::size_t N, typename T>
	std::ostream& operator<<(std::ostream& stream, const nd_base<T, N> &point)
	{
		stream << std::setprecision(3) << "(";
		for (auto i = 0; i < N; i++)
		{
			if (i < N - 1) stream << point[i] << ", ";
			else stream << point[i];
		}
		stream << ")";
		return stream;
	}
#pragma endregion 
}
