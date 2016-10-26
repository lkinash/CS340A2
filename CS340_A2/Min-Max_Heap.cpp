//
//  Min-Max_Heap.cpp
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Min-Max_Heap.h"

Heap::Heap(){
    
    end = 0;
}

void Heap::buildTestHeap(){        //Builds a min-max heap from a list of naturals read from standard input.

    int temp[] = {0, 6, 81, 87, 14, 17, 12, 28, 71, 25, 80, 20, 52, 78, 31, 42, 31, 59, 16, 24, 79, 63, 18, 19, 32, 13, 15, 48};

    //int temp[] = {0, 6, 81, 87, 14, 17, 12, 28, 71, 25, 80, 20, 52, 78};
    
    end = 27;
    //end = 13;
    
    for(int i = 1; i <= end; i++)
        heap[i] = temp[i];
    
}

void Heap::runTests(){
 
    buildTestHeap();
    printHeap();
    
    cout << "Max: " << findMax() << endl;
    cout << "Min: " << findMin() << endl;
   /*
    insertHeap(1);
    printHeap();
    
    cout << "Min: " << findMin() << endl;
    
    insertHeap(90);
    printHeap();
    
    cout << "Max: " << findMax() << endl;
    
    deleteMax();
    printHeap();
    
    deleteMin();
    printHeap();
   */
    deleteAllMinTest();
    
    buildTestHeap();
    printHeap();
    deleteAllMaxTest();
    
    
    return;
    
}

void Heap::deleteAllMinTest(){
    
    for(int i = end; i > 0; i--){
        cout << "Min to Delete: " << findMin() << endl;
        deleteMin();
        //printHeap();
    }
    return;
}

void Heap::deleteAllMaxTest(){
    
    for(int i = end; i > 0; i--){
        cout << "Max to Delete: " << findMax() << endl;
        deleteMax();
        //printHeap();
    }
    return;
}

void Heap::buildUserHeap(){
    
    int value, index = 1;

    while(1){
        
        cin >> value;
        heap[index] = value;
    }
        
    
}

void Heap::takeInput(){
 
    int input = 2;
    
    //cout << "For a user entered heap of numbers enter 1, to run default system tests enter any other number: ";
    //cin >> input;
    
    
    if(input == 1){
        buildUserHeap();
    }
    else{
        cout << "Running Tests" << endl;
        runTests();
    }
}

int Heap::findMin(){

    return heap[1];
}

int Heap::findMax(){          //Returns the minimum (resp the maximum) element.

    if(end < 2)
        return heap[1];
    else if((end > 2) && (heap[2] < heap[3]))
        return heap[3];
    else
        return heap[2];
}

void Heap::insertHeap(int newElement){         //Inserts a new element into the min-max heap.

    if(!(end < HEAP_SIZE))
        throw Overflow();
    
    end++;
    heap[end] = newElement;
    bubbleUp(end);
    
    return;
    
}

void Heap::deleteMin(){

    if (end == 0)
        throw Empty();
    else {
        heap[1] = heap[end];
        end--;
        if(end > 0)
            trickleDown(1);
    }

    return;
}

void Heap::deleteMax(){            //Deletes the minimum (resp the maximum) element.

    if (end == 0)
        throw Empty();
    
    if(end < 2){
        heap[1] = heap[end];
        end--;
        if(end > 0)
            trickleDown(1);
    }
    else if((end > 2) && (heap[2] < heap[3])){
        heap[3] = heap[end];
        end--;
        if(end > 2)
            trickleDown(3);
    }
    else{
        heap[2] = heap[end];
        end--;
        if(end > 1)
            trickleDown(2);
    }
    return;
}


void Heap::bubbleUp(int i){

    if(isOnMinLevel(i)){
        if((hasParent(i)) && ((heap[i]) > (heap[(getParentIndex(i))]))){
            swap(i, (getParentIndex(i)));
            bubbleUpMax((getParentIndex(i)));
        }
        else{
            bubbleUpMin(i);
        }
    }
    else{
        if((hasParent(i)) && ((heap[i]) < (heap[(getParentIndex(i))]))){
            swap(i, (getParentIndex(i)));
            bubbleUpMin((getParentIndex((i))));
        }
        else{
            bubbleUpMax(i);
        }
    }
    return;
}

void Heap::bubbleUpMin(int i){
    
    if(hasGrandparent(i)){
        if((heap[i]) < (heap[(getGrandparentIndex(i))])){
            swap(i, (getGrandparentIndex(i)));
            bubbleUpMin((getGrandparentIndex(i)));
        }
    }
    return;
     
}

void Heap::bubbleUpMax(int i){
    
    if(hasGrandparent(i)){
        if((heap[i]) > (heap[(getGrandparentIndex(i))])){
            swap(i, (getGrandparentIndex(i)));
            bubbleUpMin((getGrandparentIndex(i)));
        }
    }
    return;
    
}

void Heap::trickleDown(int i){
    
    if(isOnMinLevel(i)){
        trickleDownMin(i);
    }
    else{
        trickleDownMax(i);
    }

    return;
}

void Heap::trickleDownMin(int i){

    if ((hasLeftChild(i)) || (hasRightChild(i))){
        int m = getSmallestGrandChildIndex(i);               //index of smallest of the children and grandchildren (if any) of A[i]
        if ((getGrandparentIndex(m)) == i){
            if(heap[m] < heap[i]){
                swap(i, m);
                if (heap[m] > heap[(getParentIndex(m))]){
                    swap(m, (getParentIndex(m)));
                }
                trickleDownMin(m);
            }
        }
        else{
            if (heap[m] < heap[i]){
                swap(i, m);
            }
        }
    }
    return;
}

void Heap::trickleDownMax(int i){
   
    if ((hasLeftChild(i)) || (hasRightChild(i))){
        int m = getLargestGrandChildIndex(i);               //index of smallest of the children and grandchildren (if any) of A[i]
        if ((getGrandparentIndex(m)) == i){
            if(heap[m] > heap[i]){
                swap(i, m);
                if (heap[m] < heap[(getParentIndex(m))]){
                    swap(m, (getParentIndex(m)));
                }
                trickleDownMax(m);
            }
        }
        else{
            if (heap[m] > heap[i]){
                swap(i, m);
            }
        }
    }
    return;
}

int Heap::getLeftChildIndex(int i){
 
    return (2*i);
}

int Heap::getRightChildIndex(int i){
    
    return (2*i + 1);
}

int Heap::getParentIndex(int i){

    return (i/2);
}

int Heap::getGrandparentIndex(int i){
    
    return (getParentIndex(getParentIndex(i)));
}

int Heap::getSmallestChildIndex(int i){

    if(hasLeftChild(i)){
        if((((heap[(getLeftChildIndex(i))] > heap[(getRightChildIndex(i))])) && (hasRightChild(i))))
            return (getRightChildIndex(i));
        else
            return (getLeftChildIndex(i));
    }
    
    else
        return i;
    
}

int Heap::getSmallestGrandChildIndex(int i){
    
    int i1 = getSmallestChildIndex((getLeftChildIndex(i)));
    int i2 = getSmallestChildIndex((getRightChildIndex(i)));
    int i3 = getSmallestChildIndex(i);
    
    int a1  = INT_MAX, a2  = INT_MAX, a3 = INT_MAX;
    
    if(i1 <= end)
        a1 = heap[(getSmallestChildIndex((getLeftChildIndex(i))))];
    if(i2 <= end)
        a2 = heap[(getSmallestChildIndex((getRightChildIndex(i))))];
    if(i3 <= end)
        a3 = heap[(getSmallestChildIndex(i))];
    
    if( a1 == (min(a1, (min(a2, a3)))))
        return i1;
    if( a2 == (min(a1, (min(a2, a3)))))
        return i2;
    if( a3 == (min(a1, (min(a2, a3)))))
        return i3;
    else
        return i;

}

int Heap::getLargestChildIndex(int i){
    
    if(hasLeftChild(i)){
       if((((heap[(getLeftChildIndex(i))] < heap[(getRightChildIndex(i))])) && (hasRightChild(i))))
            return (getRightChildIndex(i));
       else
            return (getLeftChildIndex(i));
    }
    
    else
        return i;
    
}

int Heap::getLargestGrandChildIndex(int i){
    
    int i1 = getLargestChildIndex((getLeftChildIndex(i)));
    int i2 = getLargestChildIndex((getRightChildIndex(i)));
    int i3 = getLargestChildIndex(i);
    
    int a1 = INT_MIN, a2 = INT_MIN, a3 = INT_MIN;
    
    if(i1 <= end)
        a1 = heap[(getLargestChildIndex((getLeftChildIndex(i))))];
    if(i2 <= end)
        a2 = heap[(getLargestChildIndex((getRightChildIndex(i))))];
    if(i3 <= end)
        a3 = heap[(getLargestChildIndex(i))];
    
    if( a1 == (max(a1, (max(a2, a3)))))
        return i1;
    if( a2 == (max(a1, (max(a2, a3)))))
        return i2;
    if( a3 == (max(a1, (max(a2, a3)))))
        return i3;
    else
        return i;
}

bool Heap::hasLeftChild(int i){
    
    return ((2*i) <= end);
}

bool Heap::hasRightChild(int i){
    
    return ((2*i + 1)  <= end);
}

bool Heap::hasParent(int i){
    
    return ((i/2)  <= end && ((i/2) > 0));
}

bool Heap::hasGrandparent(int i){
    
    return ((getParentIndex(getParentIndex(i))) <= end && ((getParentIndex(getParentIndex(i))) > 0));
}

void Heap::swap(int index1, int index2){

    if(index1 > end || index2 > end)
        throw OutOfBounds();
    
    int temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
    
    //cout << "Swap: " << heap[index1] << ", " << heap[index2] << endl;
    //cout << "Swap Index: " << index1 << ", " << index2 << endl;
    
    return;
    
}

int Heap::grandparentLoop(int i){
    
    if(i == 1)
        return 1;
    else if(hasGrandparent(i)){
        i = getGrandparentIndex(i);
        return grandparentLoop(i);
    }
    else
        return 0;
}

bool Heap::isOnMinLevel(int i){
    
    if(i == 1)
        return true;
    else if((grandparentLoop(i)) == 1)
         return true;
    else
        return false;

}
void Heap::printHeap(){
    
    for(int i = 1; i < end  ; i++)
        cout << heap[i] << ", ";
 
    cout <<  heap[end] << endl;
    
}

void Heap::printEachLevel(){
 
    for(int i = 1; i <= end  ; i++)
        cout << heap[i] << " ->  " << (isOnMinLevel(i)) << endl;
    

}





