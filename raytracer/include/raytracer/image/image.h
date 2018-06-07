#pragma once
#include <memory>

namespace rayray
{
	enum channel
	{
		red = 0,
		green = 1,
		blue = 2
	};

	template<typename T>
	class image
	{
	public:
		using value_type = T;
		using self_type = image;
		using iterator = T * ;
		
		image(const int& width, const int& height);
		image(const image& other);
		image(image&& other) noexcept;

		T at(const int &row, const int &column, const int &channel);
		T at(const int &row, const int &column, const int &channel) const;

		void set(const int &row, const int &column, const int &channel, const T& value);

		int width() const;
		int height() const;
		int size() const;

		void operator=(const image& other);
		void operator=(image &&other) noexcept;
		T& operator[](const int& index);
		T operator[](const int& index) const;

		iterator begin();
		iterator end();

		iterator begin() const;
		iterator end() const;

	private:
		std::unique_ptr<T[]> data_;
		int width_;
		int height_;
	};

	template <typename T>
	image<T>::image(const int& width, const int& height)
		:width_(width), height_(height)
	{
		data_ = std::make_unique<T[]>(width_*height_ * 3);
	}

	template <typename T>
	image<T>::image(const image& other)
	{
		width_ = other.width();
		height_ = other.height();

		data_ = std::make_unique<T[]>(other.size());
		std::copy(other.begin(), other.end(), begin());
	}

	template <typename T>
	image<T>::image(image&& other) noexcept
	{
		width_ = other.width_;
		height_ = other.height_;
		other.height_ = 0;
		other.width_ = 0;
		data_ = std::move(other.data_);
		other.data_.reset(nullptr);
	}


	template <typename T>
	T image<T>::at(const int& row, const int& column, const int& channel)
	{
		return data_[channel + column * 3 + row * width_ * 3];
	}

	template <typename T>
	T image<T>::at(const int& row, const int& column, const int& channel) const
	{
		return data_[channel + column * 3 + row * width_ * 3];
	}

	template <typename T>
	void image<T>::set(const int& row, const int& column, const int& channel, const T& value)
	{
		data_[channel + column * 3 + row * width_ * 3] = value;
	}

	template <typename T>
	int image<T>::width() const
	{
		return width_;
	}

	template <typename T>
	int image<T>::height() const
	{
		return height_;
	}

	template <typename T>
	int image<T>::size() const
	{
		return width_ * height_ * 3;
	}

	template <typename T>
	void image<T>::operator=(const image& other)
	{
		width_ = other.width_;
		height = other.height_;
		data_ = std::make_unique<T[]>(other.size());
		std::copy(other.begin(), other.end(), begin());
	}

	template <typename T>
	void image<T>::operator=(image&& other) noexcept
	{
		width_ = other.width_;
		height_ = other.height_;
		other.height_ = 0;
		other.width_ = 0;

		data_ = std::move(other.data_);
		other.data_.reset(nullptr);
	}

	template <typename T>
	T& image<T>::operator[](const int& index)
	{
		return data_[index];
	}

	template <typename T>
	T image<T>::operator[](const int& index) const
	{
		return data_[index];
	}

	template <typename T>
	typename image<T>::iterator image<T>::begin()
	{
		return data_.get();
	}

	template <typename T>
	typename image<T>::iterator image<T>::begin() const
	{
		return data_.get();
	}

	template <typename T>
	typename image<T>::iterator image<T>::end()
	{
		return data_.get() + width_ * height_ * 3;
	}

	template <typename T>
	typename image<T>::iterator image<T>::end() const
	{
		return data_.get() + width_ * height_ * 3;
	}



}
