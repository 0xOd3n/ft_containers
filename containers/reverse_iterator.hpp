#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "random_access_iterator.hpp"

namespace ft
{
	template <class Iterator>
		class reverse_iterator
		{
			public:
				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::value_type			value_type;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

				reverse_iterator() : _ptr(Iterator()) {};
				explicit reverse_iterator(iterator_type it) : _ptr(it) {};
				reverse_iterator(const reverse_iterator<Iterator>& rev_it) : _ptr(rev_it._ptr) {};
				~reverse_iterator() {};

				reverse_iterator	&operator=(const reverse_iterator &src)
				{
					_ptr = src._ptr;
					return (*this);
				}

				iterator_type	base() const
				{return (_ptr);}

			private:
				Iterator	_ptr;

			public:

				// increment/decrement
				reverse_iterator	&operator++()
				{
					--(*this);
					return (*this);
				}
				reverse_iterator	operator++(int)
				{
					reverse_iterator	tmp = *this;
					--(*this);
					return (tmp);
				}
				reverse_iterator	&operator--()
				{
					++(*this);
					return (*this);
				}
				reverse_iterator	operator--(int)
				{
					reverse_iterator	tmp = *this;
					++(*this);
					return (tmp);
				}

				// assignement
				reverse_iterator	&operator+=(difference_type n)
				{
					*(this) -= n;
					return (*this);
				}
				reverse_iterator	&operator-=(difference_type n)
				{
					*(this) += n;
					return (*this);
				}

				// arithmetic
				reverse_iterator	operator+(difference_type n) const
				{
					reverse_iterator	tmp = *this;
					tmp += n;
					return (tmp);
				}
				reverse_iterator	operator-(difference_type n) const
				{
					reverse_iterator	tmp = *this;
					tmp -= n;
					return (tmp);
				}

				// access
				reference operator[](difference_type n) const
				{
					return (*(_ptr - n - 1));
				}
				reference operator*() const
				{
					Iterator	tmp = _ptr;

					return (*(_ptr - 1));
				}
				pointer operator->() const
				{
					return &(operator*());
				}
		};

	// relatioanal operator

	template <class Iterator>
		bool	operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator>
		bool	operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator>
		bool	operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator>
		bool	operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator>
		bool	operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator>
		bool	operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}
// arithmetic template
	template <class Iterator>
		reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it + n);}

	template <class Iterator>
		reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it - n);}
}

#endif