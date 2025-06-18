#include <iostream>
#include <vector>
#include <algorithm>
#include "SegmentTree.h"

struct MyAlgo{
    int operator()( const int &num1 , const int &num2 )const {
        return std::max( num1 , num2 ) ;
    }
} ;

int main(void){
    std::vector<int> nums{3,20,11,19,6,2} ;
    SegmentTree<int,MyAlgo> tree( nums.begin() , nums.begin()+5 ) ;

    std::cout << tree.query({1,2}) << '\n' ;
    // Throws an exception on query if out of memory to prevent undefine behavior
    std::cout << tree.query({2,nums.size()}) << '\n' ;
    // Throws an exception on query if out of memory to prevent undefine behavior
    std::cout << tree.query({-1,2}) << '\n' ;
    // Interval queries do not support ranges where the start is greater than the end. Hence it throws an exception
    std::cout << tree.query({3,2}) << '\n' ;

    tree.update(1,6) ;
    // Throws an exception on update if out of memory to prevent undefined behavior
    tree.update(-1,2) ;
    // Throws an exception on update if out of memory to prevent undefined behavior
    tree.update(5,100) ;

    std::cout << tree.query({1,2}) << '\n' ;

    // Throws an exception because the iterator constructor does not support __first > __last
    SegmentTree<int,MyAlgo> tree2( nums.begin()+4 , nums.begin() ) ;

    return EXIT_SUCCESS ;
}