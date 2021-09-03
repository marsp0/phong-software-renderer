#pragma once

#include <array>
#include "Vector.hpp"

class Matrix4 
{

    public:
        Matrix4();
        Matrix4(std::array<std::array<float, 4>, 4> matrix);
        ~Matrix4();

        void set(int row, int col, float value);
        float get(int row, int col) const;

        Matrix4 operator+(const Matrix4& other) const;
        Matrix4 operator-(const Matrix4& other) const;
        Matrix4 operator*(const Matrix4& other) const;
        Vector4f operator*(const Vector4f& other) const;
        Matrix4 operator*(float value) const;
        bool operator==(const Matrix4& other) const;
        bool operator!=(const Matrix4& other) const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Matrix4& other);

        Matrix4 inverse();
        Matrix4 gaussJordanInverse();
        Matrix4 gluInverse();
        Matrix4 transpose();

        // util
        void print();

    private:

        std::array<std::array<float, 4>, 4> matrix;
};

std::ostream& operator<<(std::ostream& outputStream, const Matrix4& other);

class Solver 
{
    
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