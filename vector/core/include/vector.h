
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
    


    explicit Vector(size_t n = 0);
    Vector(size_t n,const T & default_val);
    Vector(std::initializer_list<T> values);
    Vector(const Vector &);
    Vector& operator=(const Vector&);
    ~Vector();

    size_t size() const;


    T & operator[](int i);
    const T& operator[](int i) const;
    const T & at(int i);

    
    void swap(Vector<T> &) noexcept;


    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    private:
        size_t size_;
        T * vec_;
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
Vector<T>::Vector(const Vector<T> & v) : Vector(v.size())
{
    std::cout << "copy ctr\n";
    for (auto i{0}; i < v.size(); ++i)
    {
        vec_[i] = v[i];
    }
}

// Copy assignment
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    std::cout << "copy assign\n";
    // Check for (this != &rhs ) not required. If we will make a = a, then we just create another copy
    Vector<T> temp(rhs);
    swap(temp);
    return *this;
};

template<typename T>
void Vector<T>::swap(Vector<T> & other) noexcept {

    std::swap(size_, other.size_);
    std::swap(vec_,other.vec_);
}

template<typename T>
void swap(Vector<T> & first,Vector<T> & second) noexcept {
    first.swap(second);
}


// https://en.cppreference.com/w/cpp/container/vector/front
// https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func
// Marc Gregoire p.310
template<typename T>
T& Vector<T>::front(){
    return const_cast<T&>(std::as_const(*this).front());
}


template<typename T>
const T& Vector<T>::front() const{
    return vec_[0];
}


// https://en.cppreference.com/w/cpp/container/vector/back
template<typename T>
T& Vector<T>::back(){
    return const_cast<T&>(std::as_const(*this).back());
}

template<typename T>
const T& Vector<T>::back() const {
    return vec_[size_ - 1];
}


template<typename T>
size_t Vector<T>::size() const
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
const T& Vector<T>::operator[](int i) const {
    return vec_[i];
};




template<typename T>
const T& Vector<T>::at(int i){
    if (i > 0 && i < size_) {
        return vec_[i];
    }

    throw std::domain_error("Out of range");
}