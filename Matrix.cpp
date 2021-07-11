#include "Matrix.hpp"
#include <iostream>
#include <math.h>
#include <assert.h>

Matrix4::Matrix4(): matrix() 
{
    this->matrix[0][0] = 1.f;
    this->matrix[0][1] = 0.f;
    this->matrix[0][2] = 0.f;
    this->matrix[0][3] = 0.f;
    this->matrix[1][0] = 0.f;
    this->matrix[1][1] = 1.f;
    this->matrix[1][2] = 0.f;
    this->matrix[1][3] = 0.f;
    this->matrix[2][0] = 0.f;
    this->matrix[2][1] = 0.f;
    this->matrix[2][2] = 1.f;
    this->matrix[2][3] = 0.f;
    this->matrix[3][0] = 0.f;
    this->matrix[3][1] = 0.f;
    this->matrix[3][2] = 0.f;
    this->matrix[3][3] = 1.f;
}

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> matrix): matrix(matrix) 
{

}

Matrix4::~Matrix4() 
{

}

void Matrix4::set(int row, int col, float value)
{
    this->matrix[row][col] = value;
}

float Matrix4::get(int row, int col) 
{
    return this->matrix[row][col];
}

Matrix4 Matrix4::operator*(const Matrix4& other) 
{
    std::array<std::array<float, 4>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = 0.f;
            for (int x = 0; x < 4; x++) 
            {
                result[i][j] += this->matrix[i][x] * other.matrix[x][j];
            }
        }
    }
    return Matrix4(result);
}

Matrix4 Matrix4::operator*(float value) 
{
    std::array<std::array<float, 4>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = this->matrix[i][j] * value;
        }
    }
    return Matrix4(result);
}

Matrix4 Matrix4::operator+(const Matrix4& other) 
{
    std::array<std::array<float, 4>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return Matrix4(result);
}

Matrix4 Matrix4::operator-(const Matrix4& other) 
{
    std::array<std::array<float, 4>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return Matrix4(result);
}

Vector4f Matrix4::operator*(const Vector4f& other) 
{
    float x, y, z, w;
    x = this->matrix[0][0] * other.x + \
        this->matrix[0][1] * other.y + \
        this->matrix[0][2] * other.z + \
        this->matrix[0][3] * other.w;
    y = this->matrix[1][0] * other.x + \
        this->matrix[1][1] * other.y + \
        this->matrix[1][2] * other.z + \
        this->matrix[1][3] * other.w;
    z = this->matrix[2][0] * other.x + \
        this->matrix[2][1] * other.y + \
        this->matrix[2][2] * other.z + \
        this->matrix[2][3] * other.w;
    w = this->matrix[3][0] * other.x + \
        this->matrix[3][1] * other.y + \
        this->matrix[3][2] * other.z + \
        this->matrix[3][3] * other.w;
    return Vector4f(x, y, z, w);
}

Matrix4 Matrix4::inverse() 
{
    return this->gaussJordanInverse();
}

Matrix4 Matrix4::gaussJordanInverse() 
{
    return Solver::solve(*this);
}

Matrix4 Matrix4::gluInverse() 
{
    // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    float a2323 = this->matrix[2][2] * this->matrix[3][3] - this->matrix[2][3] * this->matrix[3][2];
    float a1323 = this->matrix[2][1] * this->matrix[3][3] - this->matrix[2][3] * this->matrix[3][1];
    float a1223 = this->matrix[2][1] * this->matrix[3][2] - this->matrix[2][2] * this->matrix[3][1];
    float a0323 = this->matrix[2][0] * this->matrix[3][3] - this->matrix[2][3] * this->matrix[3][0];
    float a0223 = this->matrix[2][0] * this->matrix[3][2] - this->matrix[2][2] * this->matrix[3][0];
    float a0123 = this->matrix[2][0] * this->matrix[3][1] - this->matrix[2][1] * this->matrix[3][0];
    float a2313 = this->matrix[1][2] * this->matrix[3][3] - this->matrix[1][3] * this->matrix[3][2];
    float a1313 = this->matrix[1][1] * this->matrix[3][3] - this->matrix[1][3] * this->matrix[3][1];
    float a1213 = this->matrix[1][1] * this->matrix[3][2] - this->matrix[1][2] * this->matrix[3][1];
    float a2312 = this->matrix[1][2] * this->matrix[2][3] - this->matrix[1][3] * this->matrix[2][2];
    float a1312 = this->matrix[1][1] * this->matrix[2][3] - this->matrix[1][3] * this->matrix[2][1];
    float a1212 = this->matrix[1][1] * this->matrix[2][2] - this->matrix[1][2] * this->matrix[2][1];
    float a0313 = this->matrix[1][0] * this->matrix[3][3] - this->matrix[1][3] * this->matrix[3][0];
    float a0213 = this->matrix[1][0] * this->matrix[3][2] - this->matrix[1][2] * this->matrix[3][0];
    float a0312 = this->matrix[1][0] * this->matrix[2][3] - this->matrix[1][3] * this->matrix[2][0];
    float a0212 = this->matrix[1][0] * this->matrix[2][2] - this->matrix[1][2] * this->matrix[2][0];
    float a0113 = this->matrix[1][0] * this->matrix[3][1] - this->matrix[1][1] * this->matrix[3][0];
    float a0112 = this->matrix[1][0] * this->matrix[2][1] - this->matrix[1][1] * this->matrix[2][0];

    float det = this->matrix[0][0] * ( this->matrix[1][1] * a2323 - this->matrix[1][2] * a1323 + this->matrix[1][3] * a1223 ) 
                - this->matrix[0][1] * ( this->matrix[1][0] * a2323 - this->matrix[1][2] * a0323 + this->matrix[1][3] * a0223 ) 
                + this->matrix[0][2] * ( this->matrix[1][0] * a1323 - this->matrix[1][1] * a0323 + this->matrix[1][3] * a0123 ) 
                - this->matrix[0][3] * ( this->matrix[1][0] * a1223 - this->matrix[1][1] * a0223 + this->matrix[1][2] * a0123 ) ;
    det = 1 / det;
    std::array<std::array<float, 4>, 4> result;
    result[0][0] = det *   ( this->matrix[1][1] * a2323 - this->matrix[1][2] * a1323 + this->matrix[1][3] * a1223 );
    result[0][1] = det * - ( this->matrix[0][1] * a2323 - this->matrix[0][2] * a1323 + this->matrix[0][3] * a1223 );
    result[0][2] = det *   ( this->matrix[0][1] * a2313 - this->matrix[0][2] * a1313 + this->matrix[0][3] * a1213 );
    result[0][3] = det * - ( this->matrix[0][1] * a2312 - this->matrix[0][2] * a1312 + this->matrix[0][3] * a1212 );
    result[1][0] = det * - ( this->matrix[1][0] * a2323 - this->matrix[1][2] * a0323 + this->matrix[1][3] * a0223 );
    result[1][1] = det *   ( this->matrix[0][0] * a2323 - this->matrix[0][2] * a0323 + this->matrix[0][3] * a0223 );
    result[1][2] = det * - ( this->matrix[0][0] * a2313 - this->matrix[0][2] * a0313 + this->matrix[0][3] * a0213 );
    result[1][3] = det *   ( this->matrix[0][0] * a2312 - this->matrix[0][2] * a0312 + this->matrix[0][3] * a0212 );
    result[2][0] = det *   ( this->matrix[1][0] * a1323 - this->matrix[1][1] * a0323 + this->matrix[1][3] * a0123 );
    result[2][1] = det * - ( this->matrix[0][0] * a1323 - this->matrix[0][1] * a0323 + this->matrix[0][3] * a0123 );
    result[2][2] = det *   ( this->matrix[0][0] * a1313 - this->matrix[0][1] * a0313 + this->matrix[0][3] * a0113 );
    result[2][3] = det * - ( this->matrix[0][0] * a1312 - this->matrix[0][1] * a0312 + this->matrix[0][3] * a0112 );
    result[3][0] = det * - ( this->matrix[1][0] * a1223 - this->matrix[1][1] * a0223 + this->matrix[1][2] * a0123 );
    result[3][1] = det *   ( this->matrix[0][0] * a1223 - this->matrix[0][1] * a0223 + this->matrix[0][2] * a0123 );
    result[3][2] = det * - ( this->matrix[0][0] * a1213 - this->matrix[0][1] * a0213 + this->matrix[0][2] * a0113 );
    result[3][3] = det *   ( this->matrix[0][0] * a1212 - this->matrix[0][1] * a0212 + this->matrix[0][2] * a0112 );
    return Matrix4(result);
}

Matrix4 Matrix4::transpose() 
{
    std::array<std::array<float, 4>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = this->matrix[j][i];
        }
    }
    return Matrix4(result);
}

void Matrix4::print() 
{
    std::cout << "-- Matrix --" << std::endl;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            std::cout << this->matrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

// Solver

Matrix4 Solver::solve(Matrix4& inputMatrix) 
{
    // assumption made here is that the matrix will always be invertible.
    // TODO: see if we ever need to handle non invertible matrices.
    std::array<std::array<float, 4>, 4> rawMatrix;
    std::array<std::array<float, 8>, 4> augmentedMatrix = Solver::buildAugmentedMatrix(inputMatrix);
    int col = 0;
    while (col < 4)
    {
        int maxRow = col;
        for (int i = col + 1; i < 4; i++)
        {
            if (fabs(augmentedMatrix[i][col]) > fabs(augmentedMatrix[col][col]))
            {
                maxRow = i;
            }
        }
        if (maxRow != col)
        {
            Solver::swap(col, maxRow, augmentedMatrix);
        }
        assert(augmentedMatrix[col][col] != 0.f);
        Solver::scale(col, 1.f/augmentedMatrix[col][col], augmentedMatrix);
        for (int i = 0; i < 4; i++)
        {
            if (i != col)
            {
                Solver::add(i, col, 1.f, -augmentedMatrix[i][col], augmentedMatrix);
            }
        }
        col++;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 4; j < 8; j++)
        {
            rawMatrix[i][j - 4] = augmentedMatrix[i][j];
        }
    }
    return Matrix4(rawMatrix);
}

std::array<std::array<float, 8>, 4> Solver::buildAugmentedMatrix(Matrix4& inputMatrix) 
{
    std::array<std::array<float, 8>, 4> result;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            result[i][j] = inputMatrix.get(i, j);
        }
    }

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 4; j < 8; j++) 
        {
            result[i][j] = 0.f;
        }
    }
    result[0][4] = 1.f;
    result[1][5] = 1.f;
    result[2][6] = 1.f;
    result[3][7] = 1.f;
    return result;
}

void Solver::swap(int first, int second, std::array<std::array<float, 8>, 4>& augmentedMatrix) 
{
    std::array<float, 8> tempRow;
    for (int i = 0; i < 8; i++) 
    {
        tempRow[i] = augmentedMatrix[first][i];
        augmentedMatrix[first][i] = augmentedMatrix[second][i];
        augmentedMatrix[second][i] = tempRow[i];
    }
}

void Solver::scale(int row, float value, std::array<std::array<float, 8>, 4>& augmentedMatrix)
{
    for (int i = 0; i < 8; i++) 
    {
        augmentedMatrix[row][i] *= value;
    }
}

void Solver::add(int first, 
                 int second, 
                 float firstScale, 
                 float secondScale, 
                 std::array<std::array<float, 8>, 4>& augmentedMatrix) 
{
    for (int i = 0; i < 8; i++) 
    {
        augmentedMatrix[first][i] = augmentedMatrix[first][i] * firstScale + augmentedMatrix[second][i] * secondScale;
    }
}