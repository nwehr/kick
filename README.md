# About

The kick library provides containers with better performance and a smaller footprint compared to much larger libraries (STL, C++ Standard Library, boost). Header-only files also make it easy to import kick into any existing project.

## Vector

A vector is a dynamic, sequence container. All memory management for vector is handled by an allocator. By default, the allocator keeps track of two internal sizes - allocated size, and utilized size.

Allocated size referes to the total number of items that have been allocated for the vector. Utilized size referes to the total number of items that have been added to the vector. Each time an item is added, the allocator will make sure that enough memory has already been allocated for the new item. If not, it will allocate four additional spaces, one for the new item, and three for future items.

### Features

* Sequential - Items are ordered in a linear sequence and accessed the same as regular arrays
* Dynamic - Items can be added/removed to and from anywhere in the vector
* Allocation - Any vector can use custom allocators based on performance needs

### Template Parameters

* T - The object type of individual items
* A - The allocator type for managing memory

### Example

    #include <iostream>
    #include <kick/vector.hpp>

    using namespace kick;
    
    int main( int argc, char* argv[] ){
        vector<int> myVector; 
        
        myVector.push_back(100); 
        myVector.push_back(200); 
        myVector.push_back(300); 
        
        // Access individual items, outputs 100
        std::cout << myVector[0] << std::endl; 
    
        // Iterate by incrementing an index
        for(int i = 0; i < myVector.size(); ++i) {
            std::cout << myVector[i] << std::endl; 
        }

        // Iterate with the vector iterator
        for(vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
            std::cout << *it << std::endl; 
        }
    }


## Map

A map is an associative container. Items are represented by key and value pairs. By default, map uses array_allocator<T> (same as vector) for memory management.

### Features

* Associative - Items are accessed by their unique keys
* Dynamic - Items can be added/removed dynamically
* Allocation - Any map can use custom allocators based on performance needs

### Template Parameters

* K - The object type for key
* V - The object type for value
* A - The allocator type for managing memory

### Example

    #include <iostream>

    #include <kick/string.hpp>
    #include <kick/map.hpp>

    using namespace kick;

    int main( int argc, const char* argv[] ){
        map<string, int> myMap; 

        // Adding items using insert
        myMap.insert(pair<string, int>("one", 100)); 
        myMap.insert(pair<string, int>("two", 200)); 

        // Adding items using the subscript operator
        myMap["three"] = 300; 
        myMap["four"]  = 400; 

        // Access individual items, outputs 100
        std::cout << myMap["one"] << std::endl; 

        // Iterate through all items in the map
        for(map<string, int>::iterator it = myMap.begin(); it != myMap.end() ++it) {
            std::cout << (*it).key() << " = " << (*it).val() << std::endl; 
        }
    }

## Deque

A deque (double-ended queue) is a dynamic, sequence container. Deque is similar to vector in many respects apart from one. Adding elements to a vector may require reallocation of large blocks of memory. This is because vector requires the items to be contiguous. Deque, on the other hand, can have its items scattered throughout memory without having to perform any reallocation. This may allow the deque to perform better under certain circumstances.

### Features

* Sequential - Items are ordered in a linear sequence
* Dynamic - Items can be added to either end of the deque

## Template Parameters

* T - The object type of individual items

## Example

    #include <iostream>
    #include <kick/deque.hpp>

    using namespace kick;

    int main( int argc, const char* argv[] ){
        deque<int> myDeque; 

        myDeque.push_back(100); 
        myDeque.push_back(200); 
        myDeque.push_back(300); 

        // Iterate through the deque
        for(deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); ++it) {
            std::cout << *it << std::end; 
        }
    }