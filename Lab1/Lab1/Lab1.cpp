// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "time.h"

struct Args
{
	int size, row, col;
};

std::vector<std::vector<int>> resultMatrix, matrix;


void printMatrix(std::vector<std::vector<int>> const & matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void readMatrix(std::vector<std::vector<int>> & matrix, int n)
{
	std::ifstream in("input.txt");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in >> matrix[i][j];
		}
	}
}

std::vector<std::vector<int>> getMinorMatrix(std::vector<std::vector<int>> & matrix, int n, int col, int row)
{
	std::vector<std::vector<int>> result;
	result.assign(n - 1, std::vector<int>(n - 1));
	int ni = 0, nj = 0;
	for (int i = 0; i < n; i++)
	{
		if (i != row)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != col)
				{
					result[ni][nj] = matrix[i][j];
					nj++;
				}
			}
			nj = 0;
			ni++;
		}

	}
	return result;
}

std::vector<std::vector<int>> getTransponMatrix(std::vector<std::vector<int>> & matrix, int n)
{
	std::vector<std::vector<int>> result;
	result.assign(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i][j] = matrix[j][i];
		}

	}
	return result;
}

int calcDet(std::vector<std::vector<int>> & matrix, int n)
{
	int res = 0;
	int mult = 1;
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		res = matrix[0][0];
	}
	else if (n == 2) {
		res = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	}
	else
	{
		for (int i = 0; i < n; i++) {
			std::vector<std::vector<int>> tempMatr;
			tempMatr.assign(n - 1, std::vector<int>(n - 1));
			tempMatr = getMinorMatrix(matrix, n, i, 0);
			res = res + mult * matrix[0][i] * calcDet(tempMatr, n - 1);
			mult = -mult;
		}
	}
	return res;
}

DWORD WINAPI ThreadFunc(PVOID pvParam)
{
	Args *args = (Args *)pvParam;
	int minorSize = args->size - 1;
	int det = calcDet(matrix, args->size);
	for (int col = 0; col < args->size; col++) {
		std::vector<std::vector<int>> minor = getMinorMatrix(matrix, args->size, args->row, col);
		resultMatrix[args->row][col] = pow(-1.0, args->row + col + 2) * calcDet(minor, minorSize) / det;
	}
	return 0;
}

void getInverseMatrix(std::vector<std::vector<int>> & matrix, int n, int threads) {
	HANDLE *handles = new HANDLE[threads];
	int indexThread = 0;
	for (int row = 0; row < n; row++)
	{
		if (indexThread == threads) {
			WaitForMultipleObjects(threads, handles, TRUE, INFINITE);
			indexThread = 0;
		}
		Args *args = new Args;
		args->size = n;
		args->row = row;
		handles[indexThread] = CreateThread(NULL, 0, ThreadFunc, (PVOID)args, 0, NULL);
		indexThread++;
	}
	WaitForMultipleObjects(indexThread, handles, TRUE, INFINITE);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cout << "invalid arguments\n";
	}
	int n = atoi(argv[1]);
	resultMatrix.assign(n, std::vector<int>(n));
	matrix.assign(n, std::vector<int>(n));
	readMatrix(matrix, n);
	HANDLE process = GetCurrentProcess();
	std::cout << calcDet(matrix, n) << "\n";
	SetProcessAffinityMask(process, 0b1111);
	int start = clock();
	getInverseMatrix(matrix, n, 1);
	std::cout << clock() - start << "ms\n";
	return 0;
}



