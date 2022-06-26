
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include "containers/vector/vector.hpp"
#include "containers/vector/random_access_iterator.hpp"
#include "containers/stack/stack.hpp"
#include "containers/is_integral.hpp"
#include "containers/map/AVL_Tree.hpp"

int main()
{
    try 
    {
        ft::AvlTree<int> avl(1337);
        avl.contains(1337);
        avl.insert(42);
        avl.insert(420);
        avl.insert(100);
        avl.insert(101);
        avl.insert(102);
        avl.print();

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