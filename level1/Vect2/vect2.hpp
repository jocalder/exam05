#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <string>

class vect2
{
	private:
		int		x;
		int		y;
	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		vect2&	operator=(const vect2& other);
		~vect2();

		int		&operator[](int index);
		int		operator[](int index) const;

		vect2&	operator++();
		vect2	operator++(int);
		vect2&	operator--();
		vect2	operator--(int);

		vect2&	operator+=(const vect2& other);
		vect2&	operator-=(const vect2& other);
		vect2&	operator*=(int number);

		vect2	operator+(const vect2& other) const;
		vect2	operator-(const vect2& other) const;
		vect2	operator*(int number) const;
		vect2	operator-() const;

		bool	operator!=(const vect2& other) const;
		bool	operator==(const vect2& other) const;
};
vect2	operator*(int number, const vect2& other);
std::ostream&	operator<<(std::ostream& out, const vect2& other);

#endif