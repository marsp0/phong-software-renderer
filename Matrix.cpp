#include "Matrix.hpp"
#include <iostream>
#include <math.h>

Matrix4::Matrix4(): matrix() 
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			this->matrix[i][j] = 0.f;
		}
	}
	this->matrix[0][0] = 1.f;
	this->matrix[1][1] = 1.f;
	this->matrix[2][2] = 1.f;
	this->matrix[3][3] = 1.f;
}

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> matrix): matrix(matrix) 
{

}

Matrix4::~Matrix4() 
{

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
	return Solver::solve(*this);
}

Matrix4 Matrix4::gaussJordanInverse() 
{
	return Matrix4();
}

Matrix4 Matrix4::gluInverse() 
{
	return Matrix4();
}

Matrix4 Matrix4::ludInverse() 
{
	return Matrix4();
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