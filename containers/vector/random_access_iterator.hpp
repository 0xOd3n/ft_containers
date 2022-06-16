
#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include "../iterator_traits.hpp"

// https://en.cppreference.com/w/cpp/iterator/random_access_iterator

namespace ft
{
	template <class T>
		class random_access_iterator
		{
			public:
				typedef typename iterator_traits<T>::value_type						value_type;
				typedef typename iterator_traits<T>::reference						reference;
				typedef typename iterator_traits<T>::pointer						pointer;
				typedef typename iterator_traits<T>::difference_type				difference_type;
				typedef typename iterator_traits<T>::iterator_category				iterator_category;

			private:
				pointer	_ptr;

			public :
				random_access_iterator() : _ptr(NULL) {};
				random_access_iterator(pointer ptr) : _ptr(ptr) {};
				random_access_iterator(const random_access_iterator &src)
					: _ptr(src._ptr) {};

				random_access_iterator	&operator=(const random_access_iterator &src)
				{
					_ptr = src._ptr;
					return (*this);
				}

				pointer base() const
				{
					return (_ptr);
				}

				// increment/decrement
				random_access_iterator	&operator++()
				{
					++_ptr;
					return (*this);
				}
				random_access_iterator	operator++(int)
				{
					random_access_iterator	tmp(*this);
					++_ptr;
					return (tmp);
				}
				random_access_iterator	&operator--()
				{
					--_ptr;
					return (*this);
				}
				random_access_iterator	operator--(int)
				{
					random_access_iterator	tmp(*this);
					--_ptr;
					return (tmp);
				}

				// assignment
				random_access_iterator	&operator+=(difference_type n)
				{
					_ptr += n;
					return (*this);
				}
				random_access_iterator	&operator-=(difference_type n)
				{
					_ptr -= n;
					return (*this);
				}

				// arithmetic
				random_access_iterator	operator+(difference_type val) const
				{return (random_access_iterator<T>(_ptr + val));}
				random_access_iterator	operator-(difference_type val) const
				{return (random_access_iterator<T>(_ptr - val));}

				// access
				reference	operator*() const
				{return (*_ptr);}
				pointer		operator->() const
				{return (_ptr);}
				reference	operator[](difference_type n) const
				{return (_ptr[n]);}

		};

			template <class T>
		bool	operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class T>
		bool	operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class T>
		bool	operator< (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class T>
		bool	operator> (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class T>
		bool	operator<= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class T>
		bool	operator>= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class T>
  typename random_access_iterator<T>::difference_type operator- (const random_access_iterator<T>& lhs,
    const random_access_iterator<T>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class T>
  typename random_access_iterator<T>::difference_type operator+ (const random_access_iterator<T>& lhs,
    const random_access_iterator<T>& rhs)
	{
		return (lhs.base() + rhs.base());
	}
	// template <class T>
	// 	random_access_iterator<T> operator+ (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& iter)
	// 	{return (iter + n);}

	// template <class T>
	// 	random_access_iterator<T> operator- (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& iter)
	// 	{return (iter - n);}
}

#endif