#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
    public:
        Vector (int capacity = 10);
        ~Vector();
        // OBJECT MANAGEMENT
        void push_back(const T& val);
        T pop_back();
        T at(int i) const;
        int index(const T& val) const;
        void set(int i, const T& val);
        void clear();
        // VECTOR INFO
        bool full() const;
        bool empty() const;
        int length() const; // Returns size (aka amt of elements actually in vector)

    private:
        T* data;
        int size;
        int capacity;
        void allocateMemory(int new_capacity);
};

#include "Vector.tpp"

#endif
