#pragma once

#include <array>
#include "Vector.hpp"

class Matrix4 {

    public:
        Matrix4();
        Matrix4(std::array<std::array<float, 4>, 4> matrix);
        ~Matrix4();

        float get(int row, int col);

        Matrix4 operator+(const Matrix4& other);
        Matrix4 operator-(const Matrix4& other);
        Matrix4 operator*(const Matrix4& other);
        Vector4f operator*(const Vector4f& other);
        Matrix4 operator*(float value);

        Matrix4 inverse();
        Matrix4 gaussJordanInverse();
        Matrix4 gluInverse();
        Matrix4 ludInverse();
        Matrix4 transpose();

        // util
        void print();

    private:

        std::array<std::array<float, 4>, 4> matrix;
};

class Solver {
    
    public:

        static Matrix4 solve(Matrix4& inputMatrix);
        static std::array<std::array<float, 8>, 4> buildAugmentedMatrix(Matrix4& inputMatrix);
        static void swap(int first, 
                         int second, 
                         std::array<std::array<float, 8>, 4>& augmentedMatrix);
        static void scale(int row, 
                          float value, 
                          std::array<std::array<float, 8>, 4>& augmentedMatrix);
        static void add(int first, 
                        int second, 
                        float firstScale, 
                        float secondScale, 
                        std::array<std::array<float, 8>, 4>& augmentedMatrix);

};