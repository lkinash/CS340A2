//
//  Min-Max_Heap.h
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//

#ifndef Min_Max_Heap_h
#define Min_Max_Heap_h

using namespace std;

const int HEAP_SIZE = 1000;

class Overflow
{};

class Heap{
    
public:
    Heap();
    
    void buildTestHeap();        //Builds a min-max heap from a list of naturals read from standard input.
    void buildUserHeap();
    void takeInput();
    void runTests();
    
    int findMin();
    int findMax();          //Returns the minimum (resp the maximum) element.
    
    void insertHeap(int newElement);         //Inserts a new element into the min-max heap.
    
    void deleteMin();
    void deleteMax();            //Deletes the minimum (resp the maximum) element.
    
    int getLeftChildIndex(int i);
    int getRightChildIndex(int i);
    int getParentIndex(int i);
    int getGrandparentIndex(int i);

    int getSmallestChildIndex(int i);
    
    bool hasLeftChild(int i);
    bool hasRightChild(int i);
    bool hasParent(int i);
    bool hasGrandparent(int i);
    
    void bubbleUp(int i);
    void bubbleUpMin(int i);
    void bubbleUpMax(int i);
    
    void trickleDown(int i);
    void trickleDownMin(int i);
    void trickleDownMax(int i);
    
    void swap(int index1, int index2);
    void printHeap();
    void printEachLevel();
    
    bool isOnMinLevel(int i);
    int grandparentLoop(int i);
        
private:
    int heap[HEAP_SIZE];
    int end;
    
};


#endif /* Min_Max_Heap_h */
