//
//  Min-Max_Heap.cpp
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//


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

void Heap::deleteAllMinTest(){                              //test the delete min function by deleting min over and over until the heap is empty
    
    for(int i = end; i > 0; i--){
        cout << "Min to Delete: " << findMin() << endl;           //this is done by running a for loop the number of times that there are nodes in the heap
        deleteMin();                                              //and calling the delete function for each time
    }
    return;
}

void Heap::deleteAllMaxTest(){                              //test the delete max function by deleting max over and over until the heap is empty
    
    for(int i = end; i > 0; i--){
        cout << "Max to Delete: " << findMax() << endl;             //this is done by running a for loop the number of times that there are nodes in the heap
        deleteMax();                                                //and calling the delete function for each time
    }
    return;
}

void Heap::buildUserHeap(){
    
    int value, index = 1;
    string input;
    
    getline(cin, input);
    
    cout << "Please enter the string of numbers to be placed in the heap" << endl;
    cout << "Ensure this string is just integer values with spaces in between" << endl;
    cout << "Only postive numbers are accedpted, anything else will throw an error" << endl;
    cout << "Enter the numbers to be added to the heap hear: " << endl;
    
    getline(cin, input);
    
    istringstream iss(input);                 //a stream of the string is created

    while (iss) {
        string word;                        //while there are words left in the string each word is put in the variable word one at a time
        iss >> word;
    
        value = toInt(word);
        
        if(value > 0 ){
            
           heap[index] = value;
           index++;
           end ++;
        }
    }

    for (int i = (end / 2); i > 0; i--)
        trickleDown(i);
    
    
}

void Heap::promptCommands(){
    
    string input;
    int num;
    
    while(1){
        
        cout << "Enter a number to manipulate your heap: " << endl;
        cout << "Enter 1 for findMin, enter 2 for findMax, enter 3 for insert, enter 4 for deleteMin, enter 5 for deleteMax, enter 6 to print the heap" << endl;
        cout << "Enter 0 to exit these options" << endl;
        cout << "Enter the number here: " ;
        
        
        cin >> num;
        getline(cin, input);
        
        if(num == 0)
            break;
        
        callPromptedFunction(num);

    }
}

void Heap::callPromptedFunction(int i){
    
    int num;
    string input;
    
    switch (i) {
        case 1:
            cout << "Min: " << findMin() << endl;
            break;
        case 2:
            cout << "Max: " << findMax() << endl;
            break;
        case 3:
           
            cout << "Enter the number to be inserted into your heap: ";
            
            cin >> num;
            getline(cin, input);
            
            insertHeap(num);
            
            cout << num << " has been added to the heap" << endl;
            
            break;
        case 4:
            cout << "The min to be deleted: " << findMin()  << endl;
            deleteMin();
            break;
        case 5:
            cout << "The max to be deleted: " << findMax() << endl;
            deleteMax();
            break;
        case 6:
            cout << "The following is you heap: " << endl;
            printHeap();
            break;
        default:
            cout << "Not a valid command number, please try again" << endl;
            return ;
    };
    
    return;
    
}

void Heap::takeInput(){
 
    int input;
    
    cout << "For a user entered heap of numbers enter 1, to run default system tests enter any other number: ";
    cin >> input;
    
    
    if(input == 1){
        buildUserHeap();
        cout << "The following is the heap that was built for you: " << endl;
        printHeap();
        promptCommands();
    }
    else{
        cout << "Running Tests" << endl;
        runTests();
    }
    

}

int Heap::findMin(){                //the min is always at the top of the heap

    return heap[1];                 //this returns the min value
}

int Heap::findMax(){          //Returns the maximum element.

    if(end < 2)
        return heap[1];                             //since max can be one of the children of the root
    else if((end > 2) && (heap[2] < heap[3]))       //the two children are compared and the greater one is returned
        return heap[3];
    else                                            //the root is returned if it is the only node
        return heap[2];
}

void Heap::insertHeap(int newElement){         //Inserts a new element into the min-max heap.

    if(!(end < HEAP_SIZE))                      //checks that this will not cause overflow to occur by ading a node
        throw Overflow();
    
    end++;                                  //increments the end counter
    heap[end] = newElement;                 //adds the new element to the end of the heap
    bubbleUp(end);                          //calls bubble up to put the new element in the right place in the heap
    return;
}

void Heap::deleteMin(){                     //deleted the min node in the heap

    if (end == 0)
        throw Empty();                          //checks that the heap isnt empty and throws an empty error if it is
    else {
        heap[1] = heap[end];                    //puts the end node in the heap in the location of the min
        end--;                              //decrement count of nodes in heap
        if(end > 0)
            trickleDown(1);                 //if there are still other nodes in the heap, call the trickle down to make sure it is in the right place
    }
    return;
}

void Heap::deleteMax(){            //Deletes the maximum) element in the heap.

    if (end == 0)
        throw Empty();              //checks that the heap isnt already empty, throws an empty error if it is
    
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


void Heap::bubbleUp(int i){                     //bubble ensures that when a node is added the nodes remain in the right order

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

void Heap::bubbleUpMin(int i){                      //the bubble up function specific to min nodes
    
    if(hasGrandparent(i)){
        if((heap[i]) < (heap[(getGrandparentIndex(i))])){
            swap(i, (getGrandparentIndex(i)));
            bubbleUpMin((getGrandparentIndex(i)));
        }
    }
    return;
     
}

void Heap::bubbleUpMax(int i){                  //the bubble up function specific to max nodes
    
    if(hasGrandparent(i)){
        if((heap[i]) > (heap[(getGrandparentIndex(i))])){
            swap(i, (getGrandparentIndex(i)));
            bubbleUpMax((getGrandparentIndex(i)));
        }
    }
    return;
    
}

void Heap::trickleDown(int i){                  //trickle down ensures that when a node is removed the nodes are back in order again
    
    if(isOnMinLevel(i)){
        trickleDownMin(i);
    }
    else{
        trickleDownMax(i);
    }

    return;
}

void Heap::trickleDownMin(int i){                       //the trickle down function specifically for a min node

    if ((hasLeftChild(i)) || (hasRightChild(i))){           //if the node has any childern
        int m = getSmallestGrandChildIndex(i);               //index of smallest of the children and grandchildren (if any) of A[i]
        if ((getGrandparentIndex(m)) == i){                     //if m is a grandchild of i
            if(heap[m] < heap[i]){                  //if the value at index m is less than at i
                swap(i, m);                                     //swap the two values for each other
                if (heap[m] > heap[(getParentIndex(m))]){           //if the value at m is less that the value of m's parent
                    swap(m, (getParentIndex(m)));               //swap the two values for each other
                }
                trickleDownMin(m);                   //then trickle down min calls itself again
            }
        }
        else{                               //otherwise if the value at index m is greater than the value at index i
            if (heap[m] < heap[i]){
                swap(i, m);                 //swap the two values for each other
            }
        }
    }
    return;
}

void Heap::trickleDownMax(int i){                               //the trickle down function specifically for a max node
   
    if ((hasLeftChild(i)) || (hasRightChild(i))){           //if the node has any childern
        int m = getLargestGrandChildIndex(i);               //index of smallest of the children and grandchildren (if any) of A[i]
        if ((getGrandparentIndex(m)) == i){                 //if m is a grandchild of i
            if(heap[m] > heap[i]){                          //if the value at index m is greater than at i
                swap(i, m);                                     //swap the two values
                if (heap[m] < heap[(getParentIndex(m))]){           //if the value at m is less that the value of m's parent
                    swap(m, (getParentIndex(m)));               //swap them around
                }
                trickleDownMax(m);                          //then trickle down max calls itself again
            }
        }
        else{                               //otherwise if the value at index m is greater than the value at index i
            if (heap[m] > heap[i]){
                swap(i, m);                 //swap the two values for each other
            }
        }
    }
    return;
}

int Heap::getLeftChildIndex(int i){         //gets the index location of the left child
 
    return (2*i);                         //returns the index calculated based on the index passed in
}

int Heap::getRightChildIndex(int i){             //gets the index location of the right child
    
    return (2*i + 1);                         //returns the index calculated based on the index passed in
}

int Heap::getParentIndex(int i){            //gets the index location of the parent

    return (i/2);                           //returns the index calculated based on the index passed in
}

int Heap::getGrandparentIndex(int i){                //gets the index location of the grandparent
    
    return (getParentIndex(getParentIndex(i)));         //does this by getting the parent index of the parent
}

int Heap::getSmallestChildIndex(int i){                 //gets the index of the child with the smallest value of the two

    if(hasLeftChild(i)){                        //tests that the node has a child
        if((((heap[(getLeftChildIndex(i))] > heap[(getRightChildIndex(i))])) && (hasRightChild(i))))            //tests if the right child exists and is smaller
            return (getRightChildIndex(i));                 //if it is then the right child index is returned
        else
            return (getLeftChildIndex(i));              //if the left child is smaller or is the only one then it is returned
    }
    else
        return i;           //if there are no children then the value i is returned
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

int Heap::getLargestChildIndex(int i){              //gets the index of the child with the largest value of the two
    
    if(hasLeftChild(i)){                    //tests that the node has a child
       if((((heap[(getLeftChildIndex(i))] < heap[(getRightChildIndex(i))])) && (hasRightChild(i))))          //tests if the right child exists and is larger
            return (getRightChildIndex(i));              //if it is then the right child index is returned
       else
            return (getLeftChildIndex(i));                 //if the left child is larger or is the only one then it is returned
    }
    else
        return i;           //if there are no children then the value i is returned
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

bool Heap::hasLeftChild(int i){         //tests if the current node has a left child
    
    return ((2*i) <= end);              //this is done by testing if the childs index is in bounds
}

bool Heap::hasRightChild(int i){             //tests if the current node has a right child
    
    return ((2*i + 1)  <= end);             //this is done by testing if the childs index is in bounds
}

bool Heap::hasParent(int i){                    //tests if the node has a parent node
    
    return ((i/2)  <= end && ((i/2) > 0));          //this is done by testing if the parent node is within the bounderies
}

bool Heap::hasGrandparent(int i){                             //tests if the node has a grand parent node
    
    return ((getParentIndex(getParentIndex(i))) <= end && ((getParentIndex(getParentIndex(i))) > 0));            //this is done by testing if the grandparent node is within the bounderies
}

void Heap::swap(int index1, int index2){

    if(index1 > end || index2 > end)            
        throw OutOfBounds();
    
    int temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
    
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
void Heap::printHeap(){                     //cycles through the heap in order and prinds the value of each of the nodes
    
    for(int i = 1; i < end  ; i++)
        cout << heap[i] << ", ";                //this is done using a for loop of the heap array and printing out each value

    cout <<  heap[end] << endl;
    return;
}

void Heap::printEachLevel(){            //tests if the current level is a max or min and prints that result
 
    for(int i = 1; i <= end  ; i++)
        cout << heap[i] << " ->  " << (isOnMinLevel(i)) << endl;      //this is done by cycling through all of the nodes and calling the is on min level function
    
    return;
}


int Heap::toInt(string str){              //to int takes a string of a number and converts it into an integer
    
    int number = 0;
    bool negative = false;          //there is a variable for if it is a negative number or not
    int i = 0;
    if(str[0] == '-' ){
        negative = true;            //tests if the number is negative and sets the boolean if it is
        i = 1;
    }
    
    for(int j = i; j < str.length();  j++)
        number = (number * 10) + (getDigit((str[j])));  //takes each number in the string and adds it to the integer to get the total number
    
    if(negative)
        number = ( (-1) * number);          //if the negative boolean is set then the number is converted into an integer
    
    return number;                      //then that value is returned
}

int Heap::getDigit(char c){               //a get digit function that returns the value of a digit using a switch statement to convert from char to int
    
    switch (c) {
        case '1': return 1;
            break;
        case '2': return 2;
            break;
        case '3': return 3;
            break;
        case '4': return 4;
            break;
        case '5': return 5;
            break;
        case '6': return 6;
            break;
        case '7': return 7;
            break;
        case '8': return 8;
            break;
        case '9': return 9;
            break;
        default:
            return 0;
    };
}




