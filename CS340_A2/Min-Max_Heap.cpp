//
//  Min-Max_Heap.cpp
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//


#include "Min-Max_Heap.h"

Heap::Heap(){           //the heap constructor
    
    end = 0;            //sets the end value to start at zero since the heap is empty
}

void Heap::buildTestHeap(){        //Builds a min-max heap from a list of naturals read from standard input.

    int temp[] = {0, 6, 81, 87, 14, 17, 12, 28, 71, 25, 80, 20, 52, 78, 31, 42, 31, 59, 16, 24, 79, 63, 18, 19, 32, 13, 15, 48};
                                //creates an array of numbers in min max heap order to be placed into the heap

    end = 27;                   //sets the end value based on the length of the array
    
    for(int i = 1; i <= end; i++)         //each of the values in the array is then added into the heap, this assumes this array is already in min max heap order
        heap[i] = temp[i];              //itterates through adding all the values
    
}

void Heap::runTests(){          //the run tests function runs a number of test functions on the test heap that is creaeted
 
    buildTestHeap();                //first a test heap is created
    printHeap();                        //then that heap is printed out to the user
    
    cout << "Max: " << findMax() << endl;           //the max in the heap is tested out
    cout << "Min: " << findMin() << endl;           //then the min value is printed out
   
    insertHeap(1);                              //a new value is inserted into the heap
    printHeap();                                //then the heap is printed out again
    
    cout << "Min: " << findMin() << endl;       //then the min value is printed out again, this should be the value that was added
    
    insertHeap(90);                              //a new value is inserted into the heap
    printHeap();                                //then the heap is printed out again
    
    cout << "Max: " << findMax() << endl;             //then the max value is printed out again, this should be the value that was added
    
    insertHeap(90);                              //a new value is inserted into the heap
    printHeap();                                //then the heap is printed out again
    
    deleteMax();                        //the max value in the heap is deleted and the heap is printed out
    printHeap();
    
    deleteMin();
    printHeap();                    //the min value in the heap is deleted and the heap is printed out
   
    deleteAllMinTest();             //the delete all min test is called to delete all the nodes one at a time from min to max until they are all gone
    
    buildTestHeap();                //the test heap has been emptied so it is built agian
    printHeap();                //it is printed out to the user then
    deleteAllMaxTest();      //the delete all max test is called to delete all the nodes one at a time from max to min until they are all gone
    
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

void Heap::buildUserHeap(){                 //the build user heap function builds the heap based on the user input of a list of non zero numbers
    
    int value, index = 1;                   //temporary values for creating the heap are declared
    string input;
    
    getline(cin, input);                    //the getline function is called into a variable that will be thrown away to make sure nothing else was on the command line
    
    cout << "Please enter the string of numbers to be placed in the heap. ";
    cout << "Ensure this string is just integer values with spaces in between. ";           //a set of instructions is printed out to the user
    cout << "Only postive numbers are accedpted, anything else will throw an error. ";      //it tells them how to enter the numbers to be put in the heap
    cout << "Enter the numbers to be added to the heap hear: " << endl;                 //the format should look as follows "2 4 6 77 23 45 12 11 2 3 12 44 22"
                                                                                //nothing but numbers and spaces in the string
    
    getline(cin, input);                        //the get line function is used to take in the string of numbers to be put into the heap
    
    istringstream iss(input);                 //a stream of the string is created

    while (iss) {
        string word;                        //while there are words left in the string each word is put in the variable word one at a time
        iss >> word;
    
        value = toInt(word);                //the value is then changed into its integer value
        
        if(value != 0 ){                     //the heap cannot have a zero value in it, thus if the value passed in is 0 it will not be put in the heap
            
           heap[index] = value;                 //this value that is now an integer is placed in the heap
           index++;                             //the index of values being added is increased
           end ++;                              //the end of the heap value is increaesed
        }
    }

    for (int i = (end / 2); i > 0; i--)             //then the array is taken and each of the nodes from the halfway point all the way back are run through the
        trickleDown(i);                             //trickle down function to ensure they are in the right place in the heap
    
    
}

void Heap::promptCommands(){            //the prompt user commands function asks the user what they would like to do with their heap after they create it
    
    string input;               //some variables used to take in the value from the user are created
    int num;
    
    while(1){                   //a loop is created so that the user can do more than one thing to the heap
        cout << "Enter a number to manipulate your heap: " << endl;         //prompts to tell the user which number entered calls which function are printed
        cout << "Enter 1 for findMin, enter 2 for findMax, enter 3 for insert, enter 4 for deleteMin, enter 5 for deleteMax, enter 6 to print the heap" << endl;
        cout << "Enter 0 to exit these options" << endl;
        cout << "Enter the number here: " ;                 //the user is prompted to enter a number and a list of options is printed out with numbers for each
        
        cin >> num;                                     //the users desired action is taken is as a number
        getline(cin, input);                    //a getline is done so there are no errors later if the user entered anythign extra
        
        if(num == 0)                            //if the number is 0 then then the user wants to exit the program so this breaks out of the loop
            break;
        
        callPromptedFunction(num);              //otherwise the value entered is passed to a function that will call the appropriate function baaed on the input
    }
    return;
}

void Heap::callPromptedFunction(int i){             //this function is passed the user input for a function they would like to be executed on the
                                                    //heap and calls the function using a switch statement
    switch (i) {
        case 1:{
            cout << "Min: " << findMin() << endl;           //if 1 was entered the find min function is called and the value is printed out
            break;
        }
        case 2:{
            cout << "Max: " << findMax() << endl;           //if 2 was entered the find max function is called and the value is printed out
            break;
        }
        case 3:{                                //if three was entered the user is prompted to enter the value to be inserted into the heap
            int num;
            string input;                                       // variables that are temporary for taking user input of a value to add are declared
            
            cout << "Enter the number to be inserted into your heap: ";     //prompt user to enter value to be added to the heap
            
            cin >> num;
            getline(cin, input);                                    //take in the value and anything else that may have been entered
            
            insertHeap(num);                                        //then that value is inserted into the heap
            cout << num << " has been added to the heap" << endl;           //then a message telling the user their value was added to the heap is printed
            
            break;
        }
        case 4:{
            cout << "The min to be deleted: " << findMin()  << endl;     //if 4 was entered the delete min function is called and the value to be deleted printed
            deleteMin();
            break;
        }
        case 5:{
            cout << "The max to be deleted: " << findMax() << endl;    //if 5 was entered the delete max function is called and the value to be deleted printed
            deleteMax();
            break;
        }
        case 6:{
            cout << "The following is you heap: " << endl;          //if 6 was entered then the user wanted the heap to be printed out
            printHeap();                                        //the heap is then printed out in order
            break;
        }
        default:{
            cout << "Not a valid command number, please try again" << endl;     //if a different number was entered then it will tell the user that that was not
            return;                            //a valid option and then the user will be asked to enter their choice again
        }
    };
    return;
}

void Heap::takeInput(){             //the initial take input from the user determines if the system will take the user input or build a test heap
 
    int input;                  //an input variable is declared
    
    cout << "For a user entered heap of numbers enter 1, to run default system tests enter any other number: ";
    cin >> input;                   //the user is prompted to tell if they want to enter values or run the tests and then takes the users input
    
    if(input == 1){                     //if the user entered 1
        buildUserHeap();                //it calls the function to take the user input to build the heap for them
        cout << "The following is the heap that was built for you: " << endl;           //tells them this is their heap and prints out the users heap
        printHeap();
        promptCommands();                           //then calls the function that prompts the user to enter commands for what to do with the heap
    }
    else{                                   //if the values entered was not a 1
        cout << "Running Tests" << endl;            //it tells the user that it will run the tests
        runTests();                                 //then calls teh run tests function
    }
    return;
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
        heap[1] = heap[end];        //if the heap only has the root then the last node is put in the root spot
        end--;                          //the end value is decremented
        if(end > 0)                     //and if there is still anything left
            trickleDown(1);                 //trickle down is called on it to make sure it is in the right place
    }
    else if((end > 2) && (heap[2] < heap[3])){      //if there is more than one node in the tree and the node at 3 is the largest
        heap[3] = heap[end];                //the value at the max is then replaced by the end node
        end--;                    //then the end is decremented
        if(end > 2)   //if there are still nodes left in the tree
            trickleDown(3);               //trickle down is called on it to make sure it is in the right place
    }
    else{                           //otherwise the one at 2 must be max
        heap[2] = heap[end];            //it is replaced by the end
        end--;                          //then the end is decremented
        if(end > 1)                     //if there are still nodes left in the tree
            trickleDown(2);               //trickle down is called on it to make sure it is in the right place
    }
    return;
}


void Heap::bubbleUp(int i){                     //bubble ensures that when a node is added the nodes remain in the right order

    if(isOnMinLevel(i)){                    //if the node passed in is on a min level
        if((hasParent(i)) && ((heap[i]) > (heap[(getParentIndex(i))]))){   //if it has a parent and is larger than the parent value
            swap(i, (getParentIndex(i)));                       //then swap the two nodes values
            bubbleUpMax((getParentIndex(i)));                   //and call the bubble up max function for the parent node
        }
        else{
            bubbleUpMin(i);                                 //otherwise bubble up min is called for the index
        }
    }
    else{                                             //otherwise if the node passed in is not on a min level
        if((hasParent(i)) && ((heap[i]) < (heap[(getParentIndex(i))]))){         //if it has a parent and is smaller than the parent value
            swap(i, (getParentIndex(i)));                                //then swap the two nodes values
            bubbleUpMin((getParentIndex((i))));                       //and call the bubble up min function for the parent node
        }
        else{
            bubbleUpMax(i);                               //otherwise bubble up max is called for the index
        }
    }
    return;
}

void Heap::bubbleUpMin(int i){                      //the bubble up function specific to min nodes
    
    if(hasGrandparent(i)){                                     //if the node passed in has a grandparent
        if((heap[i]) < (heap[(getGrandparentIndex(i))])){       //and the heap value at that node is less than the grandparent node
            swap(i, (getGrandparentIndex(i)));                               //then swap the two nodes values
            bubbleUpMin((getGrandparentIndex(i)));              //and then call the bubble up min function again for the grandparent node
        }
    }
    return;
}

void Heap::bubbleUpMax(int i){                  //the bubble up function specific to max nodes
    
    if(hasGrandparent(i)){                                      //if the node passed in has a grandparent
        if((heap[i]) > (heap[(getGrandparentIndex(i))])){     //and the heap value at that node is greater than the grandparent node
            swap(i, (getGrandparentIndex(i)));                  //then swap the two nodes values
            bubbleUpMax((getGrandparentIndex(i)));                      //and then call the bubble up max function again for the grandparent node
        }
    }
    return;
}

void Heap::trickleDown(int i){                  //trickle down ensures that when a node is removed the nodes are back in order again
    
    if(isOnMinLevel(i)){            //tests if the value is on a min or max level of the heap
        trickleDownMin(i);              //trickle down min is called if it is on a min level
    }
    else{
        trickleDownMax(i);              //trickle down max is called if it is on a max level
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

int Heap::getSmallestGrandChildIndex(int i){               //this function determines which of the children and grandchildren of a node is the smallest
    
    int i1 = getSmallestChildIndex((getLeftChildIndex(i)));    //first the get smallest child of the left child function is called, and the index variable is set
    int i2 = getSmallestChildIndex((getRightChildIndex(i)));  //then the get smallest child of the right child function is called, and the index variable is set
    int i3 = getSmallestChildIndex(i);                      //finally the get smallest of just the nodes children's index variable is set
    
    int a1  = INT_MAX, a2  = INT_MAX, a3 = INT_MAX;              //the value variables are set to int max
    
    if(i1 <= end)                         //if the index of the left childs smallest child is in bounds, a variable is set for the heap value at that index
        a1 = heap[(getSmallestChildIndex((getLeftChildIndex(i))))];
    
    if(i2 <= end)                  //if the index of the right childs smallest child is in bounds, a variable is set for the heap value at that index
        a2 = heap[(getSmallestChildIndex((getRightChildIndex(i))))];
    
    if(i3 <= end)                              //if the index of the smallest child is in bounds, a variable is set for the heap value at that index
        a3 = heap[(getSmallestChildIndex(i))];
    
    if( a1 == (min(a1, (min(a2, a3)))))         //if the value at the first index is the smallest then that index is returned
        return i1;
    if( a2 == (min(a1, (min(a2, a3)))))             //if the value at the second index is the smallest then that index is returned
        return i2;
    if( a3 == (min(a1, (min(a2, a3)))))    //if the value at the third index is the smallest then that index is returned
        return i3;
    else
        return i;               //otherwise the value passed in is just returned back

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

int Heap::getLargestGrandChildIndex(int i){                   //this function determines which of the children and grandchildren of a node is the largest
    
    int i1 = getLargestChildIndex((getLeftChildIndex(i)));    //first the get largest child of the left child function is called, and the index variable is set
    int i2 = getLargestChildIndex((getRightChildIndex(i)));  //then the get largest child of the right child function is called, and the index variable is set
    int i3 = getLargestChildIndex(i);                      //finally the get largest of just the nodes children's index variable is set
    
    int a1 = INT_MIN, a2 = INT_MIN, a3 = INT_MIN;           //the value variables are set to int min
    
    if(i1 <= end)                              //if the index of the left childs largest child is in bounds, a variable is set for the heap value at that index
        a1 = heap[(getLargestChildIndex((getLeftChildIndex(i))))];
    
    if(i2 <= end)                          //if the index of the right childs largest child is in bounds, a variable is set for the heap value at that index
        a2 = heap[(getLargestChildIndex((getRightChildIndex(i))))];
    
    if(i3 <= end)                          //if the index of the largest child is in bounds, a variable is set for the heap value at that index
        a3 = heap[(getLargestChildIndex(i))];
    
    if( a1 == (max(a1, (max(a2, a3)))))     //if the value at the first index is the largest then that index is returned
        return i1;
    if( a2 == (max(a1, (max(a2, a3)))))    //if the value at the second index is the largest then that index is returned
        return i2;
    if( a3 == (max(a1, (max(a2, a3)))))    //if the value at the third index is the largest then that index is returned
        return i3;
    else
        return i;                   //otherwise the value passed in is just returned back
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

void Heap::swap(int index1, int index2){        //the swap function takes the index of two nodes in the heap and then switches the two values

    if(index1 > end || index2 > end)               //first it checks that the two values to be swapped are in bounds
        throw OutOfBounds();                    //throws and out of bounds error if they are not
    
    int temp = heap[index1];                //it creates a temp to hold the first value
    heap[index1] = heap[index2];            //puts the second value in the first value
    heap[index2] = temp;                    //then puts the first value in the second effictively swapping them
    
    return;
}

int Heap::grandparentLoop(int i){           //the grandparent loop determines if the root is a grandparent of the node passed in
    
    if(i == 1)
        return 1;                       //if the value passed in is the root it returns 1 for true
    else if(hasGrandparent(i)){             //ensures it has a grandparent
        i = getGrandparentIndex(i);             //otherwise it gets the grandparent's index and calls the function recursively
        return grandparentLoop(i);
    }
    else                            //if it does not have a grandparent and is not the root then it is not a min level and returns false
        return 0;
}

bool Heap::isOnMinLevel(int i){         //the on min level function tests if the index passed in is on a max or min level and returns true for min level
    
    if(i == 1)                          //if it is the root it is a min level and returns true
        return true;
    else if((grandparentLoop(i)) == 1)      //otherwise it calls the grandparent loop to find out if it is a grandchild of the root
         return true;                       //if it is then it is a min level and it returns true
    else
        return false;                       //if it is not then it returns false since it is a max level

}
void Heap::printHeap(){                     //cycles through the heap in order and prinds the value of each of the nodes
    
    for(int i = 1; i < end  ; i++)
        cout << heap[i] << ", ";                //this is done using a for loop of the heap array and printing out each value

    cout <<  heap[end] << endl;             //the last node is printed without a comma after it
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




