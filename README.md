# Segment_Tree

## Quick reference
- [Constructor]()
- [Range Query]()
- [Single-Point Update]()
- [Range Update]()

## Introduction
A Segment Tree is an advanced data structure that efficiently supports range queries and updates, as well as single-point modifications. By leveraging a divide-and-conquer approach, it ensures both query and update operations run in $O(\log n)$ time, where $n$ is the number of elements. Segment Trees are widely used in scenarios such as interval sum, minimum/maximum queries, and range modifications.

### Constructor
- **SegmentTree()**:  
    Default constructor
- **SegmentTree( const SegmentTree<T,Algo> & )**:  
    Copy constructor
- **SegmentTree( SegmentTree<T,Algo> && )**:  
    Move constructor
- **SegmentTree( InputIt __first , InputIt __last , const Algo &prefixAlgo = Algo() )**:  
    Construct Segment Tree by passing iterator range [__first,__last) and custom algorithm to implement prefix operations  
    **Notice!!!, the InputIterator requires a random-access iterator and the __first iterator should not be greater then the __last iterator.**

### Single-Point Update
- **SegmentTree::update( size_t index , T data )**:  
    Update the element in the index-th to data

### Range Query
- **SegmentTree::query( size_t begin , size_t end )**:  
    Find the value of range \[begin,end\]
- **SegmentTree::query( const std::pair<size_t,size_t> &queryInterval )**:  
    Similarily with last function but it requires passing a std::pair<size_t,size_t>, where the query range is \[queryInterval.first,queryInterval.second\]

### Range Update
Not yet implemented, please stay tuned

## Install
The source code requires a compiler with c++17 support. Please ensure you have GCC 7.1 or newer installed before building
```
$ git clone https://github.com/MagicNotmac0820/Segment_Tree.git
```

## Usage
To use this Segment Tree, you just need to include \<SegmentTree.h\>