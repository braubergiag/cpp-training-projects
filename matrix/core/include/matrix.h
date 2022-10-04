#include <iostream>



template <typename T>
struct Matrix {


public:

    Matrix(int rows, int cols) : mat_(allocate(rows,cols)), rows_(rows), cols_(cols) {};

    void print(){

        for (size_t row_idx = 0; row_idx < rows_; row_idx++)
        {
            for (size_t cols_idx = 0; cols_idx < cols_; cols_idx++)
            {
                std::cout << mat_[row_idx][cols_idx] << " ";
            }

            
            std::cout << "\n";
        }
    }

    void fill_zeros(){
        for (size_t row_idx = 0; row_idx < rows_; row_idx++)
        {
            for (size_t cols_idx = 0; cols_idx < cols_; cols_idx++)
            {
                mat_[row_idx][cols_idx] = 0;
            }

        }
    }



    ~Matrix(){

        for (auto row_idx{0}; row_idx < rows_; ++row_idx){
            
                delete[] mat_[row_idx];

            
        }
        delete[] mat_;
    }



    private:
            T ** mat_;
            int rows_;
            int cols_;


    private:
        T ** allocate(int rows, int cols) {
            T ** m = new T * [rows];
            for (auto row_idx{0}; row_idx < rows; ++row_idx)
            {
                m[row_idx] = new T[cols];
            }

            return m;
        }


};