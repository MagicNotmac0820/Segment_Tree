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
        std::pair<int,int> interval ;
        T value ;
        Node<T> *left , *right ;
    public :
        Node( const std::pair<int,int> &interval , const T value , 
                Node<T> *left = nullptr , Node<T> *right = nullptr ) :
                interval(interval) , value(value) , left(left) , right(right){}
        Node( const Node<T> &other_node ) : 
                interval(other_node.interval) , value(other_node.value) , 
                left(other_node.left) , right(other_node.right){}
        Node( Node<T> &&other_node ) : 
                interval(std::move(other_node.interval)) , value(std::move(other_node.value)) ,
                left(std::move(other_node.left)) , right(std::move(other_node.right)){}

    template<typename U,typename Algo>
    friend class SegmentTree ;
} ;

template<typename T,typename Algo>
class SegmentTree{
    private :
        Node<T> *root ;
        Algo _prefixAlgo ;

        void generateTree( Node<T> *& , size_t , size_t ) ;
        void deleteTree( Node<T> *& ) ;
    public :
        SegmentTree(void) : root(nullptr) , _prefixAlgo(){}
        SegmentTree( const std::vector<T> &nums ) ;
        SegmentTree( const SegmentTree<T,Algo> &other_tree ) : 
                     root(other_tree.root) , _prefixAlgo(other_tree._prefixAlgo){}
        SegmentTree( SegmentTree<T,Algo> &&other_tree ) : 
                     root(std::move(other_tree.root)) , _prefixAlgo(std::move(other_tree._prefixAlgo)){}
        ~SegmentTree(void) ;

        void update( size_t index , T data ) ;
        T query( size_t begin , size_t end ) ;
        T query( const std::pair<size_t,size_t> queryInterval ) ;

        // TODO: Range update
        // void updateRange( size_t begin , size_t end ) ;
        // void updateRange( const std::pair<size_t,size_t> updateInterval ) ;
} ;

template<typename T,typename Algo>
void SegmentTree<T,Algo>::generateTree( Node <T> *&root , size_t left , size_t right ){
    
}

template<typename T,typename Algo>
SegmentTree<T,Algo>::SegmentTree( const std::vector<T> &nums ){
    generateTree( root , 0 , nums.size() ) ;
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
SegmentTree<T,Algo>::~SegmentTree(void){
    deleteTree(root) ;
}

#endif	//__SEGMENTTREE_H__