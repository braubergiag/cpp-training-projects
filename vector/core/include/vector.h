
#pragma once
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iostream>
template <typename T>
struct Vector {
    

    typedef T* iterator ;
    typedef const T* const_iterator ;

    typedef T value_type;
    typedef size_t size_type;

    typedef T& reference ;
    typedef const T& const_reference ;




    explicit Vector(size_t n = 0);
    Vector(size_t n,const T & default_val);
    Vector(std::initializer_list<T> values);
    Vector(const Vector<T> &);
    Vector<T>& operator=(const Vector<T>&);
    ~Vector();

    size_t size() const {return size_;};


    T & operator[](int i) {return vec_[i];};
    const T& operator[](int i) const {return vec_[i];};
    const T & at(int i);

    
    void swap(Vector<T> &) noexcept;

    void resize(size_t n);


    T& front() {return vec_[0];};
    const T& front() const {return vec_[0];};

    T& back() {return vec_[size_- 1];};
    const T& back() const {return vec_[size_ -1];};


    const_iterator begin() const { return data_;};
    iterator begin() { return data_;};

    const_iterator end() const { return limit_;};
    iterator end() {return limit_;};

    private:
        size_t size_;
        T * vec_;
        iterator data_;
        iterator limit_;
};


template<typename T>
Vector<T>::Vector(size_t n) : size_(n), vec_(new T[n]){
    std::cout << "ctr 1\n";
};
template<typename T>
Vector<T>::Vector(std::initializer_list<T> values) : Vector(values.size())
{
    std::cout << "ctr 2\n";
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
};

//Copy ctr
template<typename T>
Vector<T>::Vector(const Vector & v) : Vector(v.size())
{
    std::cout << "copy ctr\n";
    for (auto i{0}; i < v.size(); ++i)
    {
        vec_[i] = v[i];
    }
}

// Copy assignment
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    std::cout << "copy assign\n";
    // Check for (this != &rhs ) not required. If we will make a = a, then we just create another copy
    Vector temp(rhs);
    swap(temp);
    return *this;
};

template<typename T>
void Vector<T>::swap(Vector & other) noexcept {

    std::swap(size_, other.size_);
    std::swap(vec_,other.vec_);
}

template<typename T>
void swap(Vector<T> & first,Vector<T> & second) noexcept {
    first.swap(second);
}


template<typename T>
void Vector<T>::resize(size_t n){

    T * data = new T[n];
    for (auto i{0}; i < std::min(size_,n); ++i)
    {
        data[i] = vec_[i];
    }
    if (n > size_)
    {
        for (auto i{size_}; i < n; ++i)
        {
            data[i] = T();
        }   
    }
    delete[] vec_;
    vec_ = data;
    size_ = n;
}




template<typename T>
Vector<T>::~Vector()
{
    delete[] vec_;
};





template<typename T>
const T& Vector<T>::at(int i){
    if (i > 0 && i < size_) {
        return vec_[i];
    }

    throw std::domain_error("Out of range");
}