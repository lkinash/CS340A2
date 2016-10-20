//
//  main.cpp
//  CS340_A2
//
//  Created by Lindsey Kinash on 2016-10-11.
//  Copyright © 2016 Lindsey. All rights reserved.
//

#include <iostream>
#include "Min-Max_Heap.h"

using namespace std;

int main() {

    Heap heap = *new Heap();

    heap.buildHeap();
    heap.printHeap();
    //heap.printEachLevel();
    
    cout << "Max: " << heap.findMax() << endl;
    cout << "Min: " << heap.findMin() << endl;
    
    heap.insertHeap(1);
    heap.printHeap();
    
    cout << "Min: " << heap.findMin() << endl;
    
    heap.insertHeap(90);
    heap.printHeap();
    
    cout << "Max: " << heap.findMax() << endl;
    
    return 0;
}
