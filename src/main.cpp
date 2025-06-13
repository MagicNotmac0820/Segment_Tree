#include "SegmentTree.h"

struct Algo{
    int operator()( const int &num1 , const int &num2 ){
        return num1 + num2 ;
    }
} ;

int main(void){
    SegmentTree<int,Algo> tree ;

    return EXIT_SUCCESS ;
}