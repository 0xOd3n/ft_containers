
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include "containers/vector/vector.hpp"
#include "containers/vector/random_access_iterator.hpp"
#include "containers/stack/stack.hpp"
#include "containers/is_integral.hpp"

int main()
{

    // vector.push_back("hahah");
    // ft::stack<int> st;
    // std::cout << st.size() << std::endl;
    // st.push(10);
    // st.push(10);
    // st.push(10);
    // st.push(11);
    // st.push(12);
    // st.push(13);
    // st.push(14);

    // std::cout << st.size() << std::endl;
    // ft::stack<int> st2 = st;
    // std::cout << "relational : "<< (st2 == st) << std::endl;

    // while(!st2.empty())
    // {
    //     std::cout << st2.top() << std::endl;
    //     st2.pop();
    // }

    // std::cout << is_integral<int>::value << std::endl;
    // std::cout << is_integral<ft::vector<int>>::value;
    // ft::vector<std::string> v2(vector.begin(), vector.end());
    try 
    {
        ft::vector<std::string> vector(10, "abdo");
        ft::vector<std::string> vector2(vector.begin(), vector. begin());
    // vector.resize(5);
        for (int i = 0; i < vector2.size(); i++)
            std::cout << vector2[i] << std::endl;
            vector.push_back("amine");

        // ft::  swap(vector2, vector);
        ft::vector<std::string>::iterator it  =  vector.erase(vector.end() - 1);
        std::cout << "after erase : " << *it << std::endl;
    // vector.assign()
    std::cout << "get alloc : " << vector.get_allocator().max_size() << std::endl << vector.max_size() << std::endl;
    std::cout << "after swap : " << vector[vector2.size() - 1] << std::endl;
    // ft::vector<int> vec(10, 1337);

    // std::cout << vector.max_size() << std::endl;
    // ft::vector<int>::reverse_iterator riter = vec.rend();
    // ft::vector<int>::iterator  ref = vec.begin();
    // std::cout << "riter : " << *riter << " ref : " << *ref << std::endl;
    // // ref = 10;
    // std::cout << "riter : " << *riter << " ref : " << *ref << std::endl;
    // vector.assign(vector.max_size() + 11, 455);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    // // std::cout << "iterator : " << iter[5] << std::endl;

    // std::cout << "iterator : " << *(--iter) << std::endl;

    // std::cout << vec.max_size();
    // exit (0);
    // std::allocator<int> my_allocator;

//    int *ptr =  my_allocator.allocate(5);
//    for (int i = 0; i < 5; i++)
//    {
//        ptr[i] = i + 10;
//    }
// my_allocator.construct(ptr, 100);

//    for (int i = 0; i < 5; i++)
//    {
//        std::cout << "ptr[" << i << "] : " << ptr[i] << std::endl; 
//    }
   
//    my_allocator.deallocate(ptr, 0);
// for(int i = 0; i < 10; i++)
// {
//     std::cout << "index " << i << " " <<  vec[i] << std::endl;
// }

// std::cout << vec.capacity() << vec.size();

// ft::vector<int> vec2(vec);



// for(int i = 0; i < 10; i++)
// {
//     std::cout << "index " << i << " " <<  vec2[i] << std::endl;
// }
//    return 0;
}