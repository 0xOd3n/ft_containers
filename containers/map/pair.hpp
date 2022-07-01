/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:04:44 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/01 22:29:23 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
		// Member Types :

		typedef T1      first_type;
		typedef T2      second_type;
        
        first_type      first;
        second_type     second;

        // Memeber functions :

        pair() : first(), second() { }
        pair(const first_type& a, const second_type& b) : first(a), second(b) { }
        template <class U1, class U2>
        pair(const pair<U1, U2>& copy) : first(copy.first), second(copy.second) {}

        pair&   operator=(const pair& rhs)
        {
            if (this != &rhs)
            {
                this->first = rhs.first;
                this->second = rhs.second;
            }
            return (*this);
        }
    };
	
		// Non member functions :

    template <class T1, class T2>
    bool    operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool    operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool    operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < lhs.second));
    }

      template <class T1, class T2>
    bool    operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T1, class T2>
    bool    operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool    operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(lhs < rhs));
    }

		// Make pair :

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }

};

#endif