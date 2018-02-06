#pragma once

#include <memory>

namespace phantom::core
{
	template <typename T>
	struct Vector2
	{
	public:
		Vector2() = default;
		explicit Vector2(const T value) : x(value), y(value) {}
		Vector2(const T m_x, const T m_y) : x(std::move(m_x)), y(std::move(m_y)) {}

		Vector2(const Vector2& rhs) noexcept = default;
		Vector2(Vector2&& rhs) noexcept = default;

		Vector2& operator=(const Vector2& rhs) noexcept = default;
		Vector2& operator=(Vector2&& rhs) noexcept = default;

		Vector2 operator+() const noexcept;
		Vector2 operator-() const noexcept;
		Vector2 operator+(const Vector2& rhs) const noexcept;
		Vector2 operator-(const Vector2& rhs) const noexcept;
		Vector2 operator*(const Vector2& rhs) const noexcept;
		Vector2& operator+=(const Vector2& rhs) noexcept;
		Vector2& operator-=(const Vector2& rhs) noexcept;
		Vector2& operator*=(const Vector2& rhs) noexcept;
		bool operator==(const Vector2& rhs) const noexcept;
		bool operator!=(const Vector2& rhs) const noexcept;

		T x {};
		T y {};
	};

	template <typename T>
	Vector2<T> Vector2<T>::operator+() const noexcept
	{
		return { x, y };
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator-() const noexcept
	{
		return { -x, -y };
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const noexcept
	{
		return { x + rhs.x, y + rhs.y };
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const noexcept
	{
		return { x - rhs.x, y - rhs.y };
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator*(const Vector2<T>& rhs) const noexcept
	{
		return { x * rhs.x, y * rhs.y };
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& rhs) noexcept
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs) noexcept
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& rhs) noexcept
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	template <typename T>
	bool Vector2<T>::operator==(const Vector2<T>& rhs) const noexcept
	{
		return !(*this != rhs);
	}

	template <typename T>
	bool Vector2<T>::operator!=(const Vector2<T>& rhs) const noexcept
	{
		return (x != rhs.x || y != rhs.y);
	}
}