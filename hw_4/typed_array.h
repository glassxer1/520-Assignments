#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);
    
    // Operator
    void push(ElementType value);
    ElementType pop();
    void push_front(ElementType value);
    ElementType pop_front();

    TypedArray concat(const TypedArray& other);
    TypedArray reverse();

    TypedArray operator+(const TypedArray& other);
private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}
// operator
template <typename ElementType>
void TypedArray<ElementType>::push(ElementType value) {
    this->set(this->size(), value);
}

template <typename ElementType>
void TypedArray<ElementType>::push_front(ElementType value) {
    while ( this->origin == 0 ) {
        extend_buffer();
    }
    this->origin--;
    this->set(0, value);
}

template <typename ElementType>
ElementType TypedArray<ElementType>::pop() {
    if(this->size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType value = this->get(this->size() - 1);
    this->end--;
    // this->set(this->end, )
    return value;
}

template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front() {
    if(this->size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType value = this->get(0);
    this->origin++;
    return value;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray& other) {
    TypedArray<ElementType> newArray = TypedArray();
    for (int i=0; i<this->size(); i++ ) {
        newArray.set(i, this->get(i));
    }
    int base = newArray.size();
    for (int i=0; i<other.size(); i++ ) {
        ElementType value = other.safe_get(i);
        newArray.set(base + i, value);
    }
    return newArray;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& other) {
    TypedArray<ElementType> newArray = TypedArray();
    for (int i=0; i<this->size(); i++ ) {
        newArray.set(i, this->get(i));
    }
    int base = newArray.size();
    for (int i=0; i<other.size(); i++ ) {
        ElementType value = other.safe_get(i);
        newArray.set(base + i, value);
    }
    return newArray;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::reverse() {
    int l = 0;
    int r = this->size() - 1;
    while (l < r) {
        ElementType val = this->safe_get(r);
        this->set(r, this->safe_get(l));
        this->set(l, val);
        l++;
        r--;
    }
    return *this;
}
// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}

#endif