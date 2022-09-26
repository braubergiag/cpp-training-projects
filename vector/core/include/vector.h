
#pragma once
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <tuple>



template <typename T>
struct Vector {
    


    Vector(size_t n = 0);
    Vector(size_t n,const T & default_val);
    Vector(std::initializer_list<T> values);

    size_t size();

    T & operator[](int i);
    const T & at(int i);



    ~Vector();


    private:
        size_t size_;
        T * vec_;
};


template<typename T>
Vector<T>::Vector(size_t n) : size_(n), vec_(new T[n]){};

template<typename T>
Vector<T>::Vector(std::initializer_list<T> values) : Vector(values.size())
{
    for (auto [it, i] = std::tuple(values.begin(), 0); it != values.end() && i < size_; ++it,++i)
    {
        vec_[i] = *it;
    }
}

template<typename T>
Vector<T>::Vector(size_t n,const T & default_val) : Vector(n)
{
    for (auto i{0}; i < size_; ++i)
    {
        vec_[i] = default_val;
    }
}

template<typename T>
size_t Vector<T>::size()
{
    return size_;
};


template<typename T>
Vector<T>::~Vector()
{
    delete[] vec_;
};


template<typename T>
T& Vector<T>::operator[](int i){
    return vec_[i];
};

template<typename T>
const T& Vector<T>::at(int i){
    if (i > 0 && i < size_) {
        return vec_[i];
    }

    throw std::domain_error("Out of range");
}