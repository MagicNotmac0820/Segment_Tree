#ifndef __SEGMENTTREE_H__
#define __SEGMENTTREE_H__

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Node ;

template<typename T,typename Algo>
class SegmentTree ;

template<typename T>
class Node{
    private :
        std::pair<int,int> _interval ;
        T value ;
        Node<T> *left , *right ;
    public :
        Node( const std::pair<int,int> &interval , const T value , 
                Node<T> *left = nullptr , Node<T> *right = nullptr ) :
                _interval(interval) , value(value) , left(left) , right(right){}
        Node( const Node<T> &other_node ) : 
                _interval(other_node._interval) , value(other_node.value) , 
                left(other_node.left) , right(other_node.right){}
        Node( Node<T> &&other_node ) : 
                _interval(std::move(other_node._interval)) , value(std::move(other_node.value)) ,
                left(std::move(other_node.left)) , right(std::move(other_node.right)){}

        size_t getLowerBound(void)const {
            return _interval.first ;
        }

        size_t getUpperBound(void)const {
            return _interval.second ;
        }
    template<typename U,typename Algo>
    friend class SegmentTree ;
} ;

template<typename T,typename Algo>
class SegmentTree{
    private :
        Node<T> *root ;
        // using custom algorithm for prefix operations
        Algo _prefixAlgo ;

        // generate tree recursively
        void generateTree( const std::vector<T> &nums , size_t left , size_t right , Node<T> *&root ) ;
        template<typename InputIterator>
        void generateTree( const InputIterator &__first ,
                           const std::pair<InputIterator,InputIterator> &interval , 
                           Node<T> *&root ) ;
        // update tree recursively
        void updateRecursive( Node<T> *&root , size_t index , T data ) ;
        // delete tree recursively
        void deleteTree( Node<T> *& ) ;
        // query recursively
        T getValue( const Node<T> *&root , size_t begin , size_t end )const ;
    public :
        // default constructor
        SegmentTree(void) : root(nullptr) , _prefixAlgo(){}
        // copy constructor
        SegmentTree( const SegmentTree<T,Algo> &other_tree ) : 
                     root(other_tree.root) , _prefixAlgo(other_tree._prefixAlgo){}
        // move constructor
        SegmentTree( SegmentTree<T,Algo> &&other_tree ) : 
                     root(std::move(other_tree.root)) , _prefixAlgo(std::move(other_tree._prefixAlgo)){}
                     
        template<typename InputIterator>
        SegmentTree( InputIterator __first , InputIterator __last , 
                     const Algo &prefixAlgo = Algo() ) ;

        // destructor
        ~SegmentTree(void) ;

        // single-point update
        void update( size_t index , T data ) ;
        // interval query
        T query( size_t begin , size_t end )const ;
        T query( const std::pair<size_t,size_t> &queryInterval )const ;

        // TODO: Range update
        // void updateRange( size_t begin , size_t end ) ;
        // void updateRange( const std::pair<size_t,size_t> updateInterval ) ;
} ;

template<typename T,typename Algo>
void SegmentTree<T,Algo>::generateTree( const std::vector<T> &nums , size_t left , size_t right , Node<T> *&root ){
    if( left == right ){
        root = new Node<T>( {left,right} , nums[left] ) ;
        return ;
    }

    root = new Node<T>( {left,right} , 0 ) ;
    size_t mid = (left+right) / 2 ;
    generateTree( nums , left , mid , root->left ) ;
    generateTree( nums , mid+1 , right , root->right ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
template<typename InputIterator>
void SegmentTree<T,Algo>::generateTree( const InputIterator &__first , 
                                        const std::pair<InputIterator,InputIterator> &interval ,
                                        Node<T> *&root )
{
    InputIterator left = interval.first , right = interval.second ;
    if( left == right ){
        root = new Node<T>( {left-__first,right-__first} , *left ) ;
        return ;
    }

    root = new Node<T>( {left-__first,right-__first} , 0 ) ;
    InputIterator mid = left + (right-left) / 2 ;
    generateTree( __first , {left,mid} , root->left ) ;
    generateTree( __first , {mid+1,right} , root->right ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::deleteTree( Node<T> *&root ){
    if(!root)   return ;

    deleteTree(root->left) ;
    deleteTree(root->right) ;
    delete root ;
    root = nullptr ;
}

template<typename T,typename Algo>
template<typename InputIterator>
SegmentTree<T,Algo>::SegmentTree( InputIterator __first , InputIterator __last ,
                                  const Algo &prefixAlgo ) : root(nullptr) , _prefixAlgo(prefixAlgo) 
{
    if( __first == __last )
        return ;
    generateTree( __first , {__first,__last-1} , root ) ;
}
                                         

template<typename T,typename Algo>
SegmentTree<T,Algo>::~SegmentTree(void){
    deleteTree(root) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::updateRecursive( Node<T> *&root , size_t index , T data ){
    if( root->getLowerBound() == root->getUpperBound() ){
        root->value = data ;
        return ;
    }

    size_t mid = ( root->getLowerBound() + root->getUpperBound() ) / 2 ;
    if( index > mid )
        updateRecursive( root->right , index , data ) ;
    else
        updateRecursive( root->left , index , data ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::update( size_t index , T data ){
    updateRecursive( root , index , data ) ;
    return ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::getValue( const Node<T> *&root , size_t begin , size_t end )const {
    if( begin == root->getLowerBound() && end == root->getUpperBound() )
        return root->value ;
    
    size_t mid = ( root->getLowerBound() + root->getUpperBound() ) / 2 ;
    if( begin > mid )
        return getValue( const_cast<const Node<T> *&>(root->right) , begin , end ) ;
    if( end <= mid )
        return getValue( const_cast<const Node<T> *&>(root->left) , begin , end ) ;

    return _prefixAlgo( getValue( const_cast<const Node<T> *&>(root->left) , begin , mid ) ,
                        getValue( const_cast<const Node<T> *&>(root->right) , mid+1 , end ) ) ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::query( size_t begin , size_t end )const {
    return getValue( const_cast<const Node<T> *&>(root) , begin , end ) ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::query( const std::pair<size_t,size_t> &queryInterval )const {
    return getValue( root , queryInterval.first , queryInterval.second ) ;
}

#endif	//__SEGMENTTREE_H__