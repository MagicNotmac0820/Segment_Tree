// A solution of the problem on Zerojudge using my SegmentTree
// If you want to see the details of the problem, the problem id is g277
#include <iostream>
#include <vector>
#include <numeric>
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

int64_t lucky_num( const vector<int64_t> &nums , int left , int right , 
                   const vector<int64_t> &prefixSum , const SegmentTree<int64_t,Algo> &minQuery )
{
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

    vector<int64_t> nums(numsSize) ;
    vector<int64_t> prefixSum(numsSize+1) ;
    for( int64_t &element : nums ){
        cin >> element ;
    }
    
    SegmentTree<int64_t,Algo> tree( nums.begin() , nums.end() ) ;
    prefixSum[0] = 0 ;
    std::partial_sum( nums.begin() , nums.end() , prefixSum.begin()+1 ) ;

    cout << lucky_num( nums , 0 , nums.size()-1 , prefixSum , tree ) << endl ;

    return EXIT_SUCCESS ;
}