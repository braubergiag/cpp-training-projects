#include <iostream>



template <typename T>
struct Matrix {
public:

    Matrix(int rows, int cols) : mat_(allocate(rows,cols)), rows_(rows), cols_(cols) {};
    Matrix(std::initializer_list<T> args) {

    }
    virtual ~Matrix();

   
    void print();
    void fill_zeros();
    void fill_eye(int dim);
    static Matrix * eye(int dim);

    private:
            T ** mat_;
            int rows_;
            int cols_;


    private:
        T ** allocate(int rows, int cols);


};


template <typename T> Matrix<T> *  Matrix<T>::eye(int dim){



}

template <typename T> void Matrix<T>::fill_eye(int dim){

    for (size_t row_idx = 0; row_idx < rows_; row_idx++)
    {
        for (size_t cols_idx = 0; cols_idx < cols_; cols_idx++)
        {
            if (row_idx == cols_idx) {
                mat_[row_idx][cols_idx] = 1;

            }
        }

    }
}

template <typename T> T ** Matrix<T>::allocate(int rows, int cols) {
            T ** m = new T * [rows];
            for (auto row_idx{0}; row_idx < rows; ++row_idx)
            {
                m[row_idx] = new T[cols];
            }

            return m;
        }




template <typename T>  void Matrix<T>::print(){

    for (size_t row_idx = 0; row_idx < rows_; row_idx++)
    {
        for (size_t cols_idx = 0; cols_idx < cols_; cols_idx++)
        {
            std::cout << mat_[row_idx][cols_idx] << " ";
        }

        
        std::cout << "\n";
    }
}


template <typename T>  void Matrix<T>::fill_zeros(){
    for (size_t row_idx = 0; row_idx < rows_; row_idx++)
    {
        for (size_t cols_idx = 0; cols_idx < cols_; cols_idx++)
        {
            mat_[row_idx][cols_idx] = 0;
        }

    }
}




template <typename T> Matrix<T>::~Matrix(){

    for (auto row_idx{0}; row_idx < rows_; ++row_idx){
        
            delete[] mat_[row_idx];

        
    }
    delete[] mat_;
}

