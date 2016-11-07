//
//  Min-Max_Heap.h
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//

#ifndef Min_Max_Heap_h
#define Min_Max_Heap_h

#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

const int HEAP_SIZE = 1000;         //sets the max heap size, in this case 1000 nodes, can be set to more

const int INT_min = -2147483648;
const int INT_max = 2147483647;

class Overflow              //an overflow class for when the heap overflows, an overflow error is thrown
{};

class Empty             //an empty error will be thrown if the remove from the heap is tried when it is empty
{};

class OutOfBounds           //an out of bounds error is thrown if a node that is past the end is tried
{};

class Heap{             //a heap class is created
    
public:
    Heap();             //heap constructor
    
    void buildTestHeap();       //Builds a min-max heap from a list of naturals preset as the test heap for the program
    void buildUserHeap();       //Builds a min-max heap from a list of naturals read from standard input.

    void takeInput();                    //the initial take input from the user determines if the system will take the user input or build a test heap
    void runTests();                    //the run tests function runs a number of test functions on the test heap that is creaeted
    void promptCommands();              //the prompt user commands function asks the user what they would like to do with their heap after they create it
    void callPromptedFunction(int i);  //this function is passed the user input for a function they would like to be executed on the heap and calls the function
    
    void deleteAllMinTest();                //test the delete min function by deleting min over and over until the heap is empty
    void deleteAllMaxTest();                   //test the delete max function by deleting min over and over until the heap is empty
    
    int findMin();              //Returns the minimum element
    int findMax();          //Returns the  maximum element.
    
    int getDigit(char c);               //gets the integer value of a char
    int toInt(string str);                  //converts a string digit to an integer
    
    void insertHeap(int newElement);         //Inserts a new element into the min-max heap.
    
    void deleteMin();               //deletes the minimum element in the heap
    void deleteMax();            //Deletes the maximum element in the heap
    
    int getLeftChildIndex(int i);           //returns the index of the left child
    int getRightChildIndex(int i);              //returns the index of the right child
    int getParentIndex(int i);                  //returns the index of the parent node
    int getGrandparentIndex(int i);             //returns the index of the grandparent node

    int getSmallestChildIndex(int i);               //gets the index of the child with the smallest value of the two
    int getSmallestGrandChildIndex(int i);          //gets the grandchild index of the smallest of the grandchild nodes
    
    int getLargestChildIndex(int i);                //gets the index of the child with the largest value of the two
    int getLargestGrandChildIndex(int i);            //gets the grandchild index of the largest of the grandchild nodes

    bool hasLeftChild(int i);               //tests if the current node has a left child
    bool hasRightChild(int i);              //tests if the current node has a right child
    bool hasParent(int i);                  //tests if the current node has a parent node
    bool hasGrandparent(int i);              //tests if the current node has a greandparent node
    
    void bubbleUp(int i);                 //bubble ensures that when a node is added the nodes remain in the right order
    void bubbleUpMin(int i);                //the bubble up function specific to min nodes
    void bubbleUpMax(int i);                //the bubble up function specific to max nodes
    
    void trickleDown(int i);                 //trickle down ensures that when a node is removed the nodes are back in order again
    void trickleDownMin(int i);                //the trickle down function specifically for a min node
    void trickleDownMax(int i);                 //the trickle down function specifically for a max node
    
    void swap(int index1, int index2);          //the swap function takes the index of two nodes in the heap and swaps them
    void printHeap();                           //prints the entire heap in order, top down
    void printEachLevel();                          //tests if the current level is a max or min and prints that result
    
    bool isOnMinLevel(int i);                   //tests if the index passed in is on a max or min level
    int grandparentLoop(int i);                 //the loop for testing for grandparents
        
private:
    int heap[HEAP_SIZE];                    //the heap array where the information is stored
    int end;                            //the current end of the heap, the last node tracker
    
};


#endif /* Min_Max_Heap_h */
