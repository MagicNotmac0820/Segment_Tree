#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include "SegmentTree.h"
using std::cin ;
using std::cout ;
using std::endl ;
using std::vector ;

struct Algo{
    public :
        int operator()( const int &num1 , const int &num2 )const {
            return std::min( num1 , num2 ) ;
        }
} ;

int64_t lucky_num( const vector<int> &nums , int left , int right , 
                   const vector<int64_t> &prefixSum , const SegmentTree<int,Algo> &minQuery )
{
    if( left > right )
        return 0 ;
    if( left == right )
        return nums[left] ;

    size_t min_element = std::find( nums.begin()+left , nums.begin()+right , 
                                    minQuery.query(static_cast<size_t>(left),static_cast<size_t>(right)) ) -
                         nums.begin() ;
    int64_t lSum = ( min_element <= static_cast<size_t>(left) ) ? 0 : prefixSum[min_element] - prefixSum[left] ;
    int64_t rSum = ( min_element >= static_cast<size_t>(right) ) ? 0 : prefixSum[right+1] - prefixSum[min_element+1] ;
    if( lSum > rSum )
        return lucky_num( nums , left , min_element-1 , prefixSum , minQuery ) ;
    return lucky_num( nums , min_element+1 , right , prefixSum , minQuery ) ;
}

int main(void){
    int numsSize ;
    cin >> numsSize ;

    vector<int> nums(numsSize) ;
    std::unordered_map<int,size_t> indexes ;
    size_t index = 0 ;
    vector<int64_t> prefixSum(numsSize+1) ;
    for( int &element : nums ){
        cin >> element ;
        indexes.insert({element,index++}) ;
    }
    
    SegmentTree<int,Algo> tree( nums.begin() , nums.end() ) ;
    prefixSum[0] = 0 ;
    std::partial_sum( nums.begin() , nums.end() , prefixSum.begin()+1 ) ;

    cout << lucky_num( nums , 0 , nums.size()-1 , prefixSum , tree ) << endl ;

    return EXIT_SUCCESS ;
}