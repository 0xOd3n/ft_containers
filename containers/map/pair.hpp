/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 23:04:44 by abbelhac          #+#    #+#             */
/*   Updated: 2022/06/30 22:57:06 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1      first_type;
        typedef T2      second_type;
        
        first_type      first;
        second_type     second;
        
        pair() : first(), second() { }
        pair(const first_type& a, const second_type& b) : first(a), second(b) { }
        template <class U1, class U2>
        pair(const pair<U1, U2>& copy) : first(copy.first), second(copy.second) {}
    }
}

#endif