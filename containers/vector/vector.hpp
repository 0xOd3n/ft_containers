
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <cmath>
#include "random_access_iterator.hpp"
#include "../reverse_iterator.hpp"
#include "../enable_if.hpp"
#include "../is_integral.hpp"

namespace ft
{
    template <typename T,class Alloc = std::allocator<T> >
    class vector
    {

        public :
                    typedef     T                                                           value_type;
                    typedef     Alloc                                                       allocator_type;
                    typedef     typename allocator_type::reference                          reference;
                    typedef     typename allocator_type::const_reference                    const_reference;
                    typedef     typename allocator_type::pointer                            pointer;
                    typedef     typename allocator_type::const_pointer                      const_pointer; 
                    typedef     ft::random_access_iterator<pointer>                         iterator;
                    typedef     ft::random_access_iterator<const_pointer>                   const_iterator;
                    typedef     ft::reverse_iterator<iterator>                              reverse_iterator;
                    typedef     ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
                    typedef     typename iterator_traits<iterator>::difference_type         difference_type;
                    typedef     typename allocator_type::size_type                          size_type;

        private :
                    pointer ptr;
                    size_type m_size;
                    size_type m_capacity;
                    allocator_type _alloc;

        public :
                    explicit vector(const allocator_type& alloc = allocator_type()) : ptr(0), m_size(0), m_capacity(0) {}

                    explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
                    :   ptr(0), m_size(0), m_capacity(0), _alloc(alloc)
                    {
                        ptr = _alloc.allocate(n);
                        m_capacity = n;
                        for (int i = 0; i < n; i++)
                        {
                            ptr[i] = val;
                        }
                        m_size = n;
                    }

                    template <class InputIterator>
                    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
                    : ptr(0), m_size(0), m_capacity(0), _alloc(alloc)
                    {
                        difference_type nt = last - first;
                        this->reserve(nt);
                        m_size = nt;
                        for (int i = 0; i < nt; i++)
                        {
                            ptr[i] = *(first + i);
                        }
                    }

                    vector(const vector& copy) : ptr(0)
                    {
                        *this = copy;
                    }
                    ~vector()
                    {
                        for (size_type i = 0; i < m_capacity; i++)
                            this->_alloc.destroy(&ptr[i]);
                        this->_alloc.deallocate(this->ptr, this->m_capacity);
                    }
                    vector& operator=(const vector& copy)
                    {
                        if (this != &copy)
                        {
                            if(this->ptr != 0)
                                this->_alloc.deallocate(this->ptr, this->m_capacity);
                            this->m_capacity = copy.m_capacity;
                            this->m_size = copy.m_size;
                            this->_alloc = copy._alloc;
                            this->ptr = this->_alloc.allocate(copy.m_capacity);
                            for (int i = 0; i < copy.m_size; i++)
                                _alloc.construct(&ptr[i], copy.ptr[i]);
                        }
                        return (*this);
                    }

                    // iterators

                    iterator begin()
                    {
                        return(iterator(ptr));
                    }
                    iterator    end()
                    {
                        return(iterator(ptr + m_size));
                    }
                    const_iterator begin() const
                    {
                        return(const_iterator(ptr));
                    }
                    const_iterator end() const
                    {
                        return(const_iterator(ptr + m_size));
                    }
                    reverse_iterator rbegin()
                    {
                        return (reverse_iterator(this->end()));
                    }
                    const_reverse_iterator rbegin() const
                    {
                        return (reverse_iterator(this->end()));
                    }
                    reverse_iterator rend()
                    {
                        return (reverse_iterator(this->begin()));
                    }
                    const_reverse_iterator rend() const
                    {
                        return (reverse_iterator(this->begin()));
                    }

                    // capacity

                    size_type   size() const
                    {
                        return (m_size);
                    }
                    
                    size_type   capacity() const
                    {
                        return (m_capacity);
                    }

                    size_type   max_size() const
                    {
                        return (_alloc.max_size());
                    }

                    bool    empty() const
                    {
                        return (m_size == 0);
                    }

                    void    resize(size_type n, value_type val = value_type())
                    {
                        if (n > this->max_size())
                            throw (std::length_error("vector::resize"));
                        if (n > m_capacity)
                            this->reserve(n);
                        if (n < m_size)
                        {
                            for (size_type i = n; i < m_size; i++)
                                _alloc.destroy(&ptr[i]);
                            m_size = n;
                        }
                        else if (n > m_size)
                        {
                            for (size_type i = m_size; i < n; i++)
                                _alloc.construct(&ptr[i], val);
                            m_size = n;
                        }
                    }

                    void    reserve(size_type n)
                    {
                        if (n > this->max_size())
                            throw (std::length_error("vector::reserve"));
                        if (n > m_capacity)
                        {
                            value_type *tmp = _alloc.allocate(n);

                            for (size_type i = 0; i < m_size; i++)
                            {
                                _alloc.construct(&tmp[i], ptr[i]);
                                _alloc.destroy(&ptr[i]);
                            }
                            if (ptr)
                                _alloc.deallocate(ptr, m_capacity);
                            ptr = tmp;
                            m_capacity = n;
                        }
                    }
                    // element access

                    reference& operator[](size_type idx) const
                    {
                        return (*(ptr + idx));
                    }

                    reference	at(size_type n)
                    {
                        if (n >= m_size)
                            throw std::out_of_range("out of range");
                        return (ptr[n]);
                    }

				    const_reference	at(size_type n) const
                    {
                        if (n >= m_size)
                            throw std::out_of_range("out of range");
                        return (ptr[n]);
                    }

                    reference	front()
                    {
                        return (ptr[0]);
                    }

                    const_reference	front() const
                    {
                        return (ptr[0]);
                    }

                    reference	back()
                    {
                        return (ptr[m_size - 1]);
                    }

                    const_reference	back() const
                    {
                        return (ptr[m_size - 1]);
                    }
                    
                    // modifiers

                    void    assign(size_type n, const value_type& val)
                    {
                        if (n > m_capacity)
                            reserve(n);
                        for (size_type i = 0; i < n; i++)
                            _alloc.construct(&ptr[i], val);
                        m_size = n;
                    }

                    void    push_back(const value_type& val)
                    {
                        if (m_size == m_capacity)
                        {
                            if (m_capacity == 0)
                                reserve(1);
                            else
                                reserve(m_capacity * 2);
                        }
                        _alloc.construct(&ptr[m_size], val);
                        m_size++;
                    }

                    void    pop_back()
                    {
                        _alloc.destroy(&ptr[m_size - 1]);
                        m_size--;
                    }


                    iterator	erase(iterator position)
                    {
                        difference_type i = position - begin();

                        _alloc.destroy(&ptr[i]);
                        _shift_left(i, 1);
                        m_size--;
                        return (iterator(&ptr[i]));			
                    }

                    iterator	erase(iterator first, iterator last)
                    {
                        size_type	x = &*first - &*begin();
                        size_type	y = &*last - &*begin();

                        for (size_type z = x; z < y; z++)
                            _alloc.destroy(&ptr[z]);
                        _shift_left(x, y - x);
                        m_size -= y - x;
                        return (iterator(&ptr[x]));
                    }

                    void	swap(vector &x)
                    {
                        vector<T> tmp = x; 
                        x = *this;
                        *this = tmp;
                    }


                    void    clear()
                    {
                        for (size_type i = 0; i < m_size; i++)
                            _alloc.destroy(&ptr[i]);
                        m_size = 0;
                    }

                    allocator_type get_allocator() const
                    {
                        return (_alloc);
                    }

                private:

				void	_shift_right(size_type position, size_type n)
				{
					if (empty())
						return;
					for (size_type i = m_size - 1; i >= position; i--)
					{
						_alloc.construct(&ptr[i + n], ptr[i]);
						_alloc.destroy(&ptr[i]);
					}
				}
                
				void	_shift_left(size_type position, size_type n)
				{
					if (empty())
						return;
					for (size_type i = position; i < m_size - n; i++)
					{
						_alloc.construct(&ptr[i], ptr[i + n]);
						_alloc.destroy(&ptr[i + n]);
					}
				}
	};

    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) 
                    return false;
                else if (*first1 < *first2)
                    return true;
                ++first1; ++first2;
            }
            return (first2 != last2);
        }

    template <class InputIt1, class InputIt2>
        bool equal(InputIt1 first1, InputIt1 last1, 
                InputIt2 first2)
        {
            for (; first1 != last1; ++first1, ++first2) {
                if (!(*first1 == *first2)) {
                    return false;
                }
            }
            return true;
        }

 template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (equal(lhs.begin(), lhs.end(), rhs.begin()) && rhs.size() == lhs.size());
  }

template <class T, class Alloc>
  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return(!(lhs == rhs));
  }

template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }


template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (!(rhs < lhs));
  }


template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (rhs < lhs);
  }

template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (!(lhs < rhs));
  }

template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
  {
      x.swap(y);
  };
};

#endif