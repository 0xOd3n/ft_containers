#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

        protected :

                container_type c;
        
        public :
                
                explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
                ~stack() {}

                stack  &operator=(const stack& copy)
                {
                    if (this != &copy)
                        this->c = copy.c;
                    return(*this);
                }

                bool empty() const
                {
                    return(c.empty());
                }

                size_type size() const
                {
                    return (c.size());
                }

                value_type& top()
                {
                    return(c.back());
                }

                const value_type& top() const
                {
                    return (c.back());
                }

                void push(const value_type& val)
                {
                    c.push_back(val);
                }

                void pop()
                {
                    c.pop_back();
                }
            
            template <class Type, class Cntr>      
        friend  bool operator== (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
            
            template <class Type, class Cntr>
        friend  bool operator!= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
            
            template <class Type, class Cntr>
        friend  bool operator<  (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
            
            template <class Type, class Cntr>
        friend  bool operator<= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
            
            template <class Type, class Cntr>
        friend  bool operator>  (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
           
            template <class Type, class Cntr>
        friend  bool operator>= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs);
    };

        template <class Type, class Cntr>
    bool operator== (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
        {
            return (lhs.c == rhs.c);
        };

        template <class Type, class Cntr>
    bool operator!= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
        {
            return (lhs.c != rhs.c);
        }

        template <class Type, class Cntr>
    bool operator<  (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
    {
        return (lhs.c < rhs.c);
    }

        template <class Type, class Cntr>
    bool operator<= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
    {
        return (lhs.c <= rhs.c);
    }

        template <class Type, class Cntr>
    bool operator>  (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
    {
        return (lhs.c > rhs.c);
    }

        template <class Type, class Cntr>
    bool operator>= (const stack<Type,Cntr>& lhs, const stack<Type,Cntr>& rhs)
    {
        return (lhs.c >= rhs.c);
    }
}

#endif