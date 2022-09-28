
#pragma once
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iostream>
#include <memory>
template <typename T>
struct Vector {
    

    typedef T* iterator ;
    typedef const T* const_iterator ;

    typedef T value_type;
    typedef size_t size_type;

    typedef T& reference ;
    typedef const T& const_reference ;




    Vector() {create();};
    explicit Vector(size_t n,const T & default_val = T()) {create(n,default_val);};
    Vector(const std::initializer_list<T> &  values) {
      create(values.begin(),values.end());
    }
    Vector(const Vector<T> & v) {create(v.begin(),v.end());};
    Vector<T>& operator=(const Vector<T>& rhs){
        if (this != &rhs)
        {
            uncreate();
            create(rhs.begin(),rhs.end());
        }
        return *this;
    };
    ~Vector() { uncreate();};

    [[nodiscard]] size_type size() const {return avail_ - data_;};
    [[nodiscard]] size_type capacity() const {return limit_ - data_;}

    T & operator[](int i) {return data_[i];};
    const T& operator[](int i) const {return data_[i];};
    const T & at(int i);


    T& front() {return data_[0];};
    const T& front() const {return data_[0];};

    T& back() {return data_[size() - 1];};
    const T& back() const {return data_[size() - 1];};

    void push_back(const T& val);
    void clear();

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    const_iterator begin() const { return data_;};
    iterator begin() { return data_;};


    const_iterator end() const { return limit_;};
    iterator end() {return limit_;};
private:
    void create();

    void create(size_type, const T&);
    void create(const_iterator,const_iterator);
    void uncreate();

    void grow();

    void unchecked_append(const T&);
private:

    iterator data_;
    iterator avail_;
    iterator limit_;
    std::allocator<T> alloc_;
};



template<typename T>
const T& Vector<T>::at(int i){
    if (i > 0 && i < size()) {
        return data_[i];
    }

    throw std::domain_error("Out of range");
}

template<typename T>
void Vector<T>::push_back(const T &val) {
    if (avail_ == limit_)
    {
        grow();
    }
    unchecked_append(val);

}

template<typename T>
void Vector<T>::create() {
    data_ = avail_ = limit_ = 0;
}

template<typename T>
void Vector<T>::create(Vector::size_type n, const T & val) {
    data_ = alloc_.allocate(n);
    limit_ = avail_ = data_ + n;
    std::uninitialized_fill(data_,limit_,val);
}

template<typename T>
void Vector<T>::create(Vector::const_iterator i, Vector::const_iterator j) {
    data_ = alloc_.allocate(j - i);
    limit_ = avail_ = std::uninitialized_copy(i,j,data_);
}

template<typename T>
void Vector<T>::uncreate() {
    if (data_)
    {
        iterator it = avail_;
        while (it != data_)
        {
            alloc_.destroy(--it);
        }
        alloc_.deallocate(data_,limit_ - data_);
    }
    data_ = avail_ = limit_;
}

template<typename T>
void Vector<T>::grow() {
    size_type new_size = std::max(2 * (limit_ - data_), std::ptrdiff_t(1));

    iterator new_data = alloc_.allocate(new_size);
    iterator  new_avail = std::uninitialized_copy(data_,avail_,new_data);

    uncreate();
    data_ = new_data;
    avail_ = new_avail;
    limit_ = data_ + new_size;
}

template<typename T>
void Vector<T>::unchecked_append(const T & val) {
    alloc_.construct(avail_++,val);
}

template<typename T>
void Vector<T>::clear() {
    if (data_)
    {
        iterator it = avail_;
        while (it != data_)
        {
            alloc_.destroy(--it);
        }
    }
    avail_ = data_;
}

template<typename T>
T * Vector<T>::erase(Vector::const_iterator pos) {
    return nullptr;
}

template<typename T>
T* Vector<T>::erase(Vector::const_iterator first, Vector::const_iterator last) {
    return nullptr;
}
