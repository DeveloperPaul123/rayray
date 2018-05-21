#pragma once
#include <ostream>
#include <array>

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

		nd_base();
		~nd_base() = default;
		explicit nd_base(std::array<T, N> data);
		nd_base(std::initializer_list<T> data);
	
		static std::size_t dimension();

		value_type_reference operator[](const std::size_t& index);
		value_type operator[](const std::size_t& index) const;

    protected:
		std::array<T, N> data_;
    };

	template <typename T, std::size_t N>
	nd_base<T, N>::nd_base()
	{
		std::fill(data_.begin(), data_.end(), T());
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
}