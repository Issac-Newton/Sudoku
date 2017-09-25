
#include "stdafx.h"

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "generator.h" 
#include "Solver.h"
#define MAX_number 1000000
using namespace std;

bool compare(char* a, char* b);
int main(int argc, char** argv)
{
	int number_sudoku = 0;
	FILE* solve_path;
	
	if (argc != 3) {
		cout << "Illegal paramater number\n";
		cout << "Usage: sudoku.exe -c n -->generate n sudoku finals. \n sudoku.exe -s path -->";
		cout << "Read sudoku from file in the given path,and solve them.\n";
		cout << "The charactre should be itself:such as C is not equal to c.\n";
		return 1;
	}

	if (!(compare(argv[1], "-c") || compare(argv[1], "-s"))) {
		cout << "The first parameter should be -c or -s\n";
		cout << "-c means to generate the sudoku to file.\n";
		cout << "-s means to solve the sudoku from the file.\n";
		return 1;
	}
	
	if (compare(argv[1], "-c")) {
		size_t len = strlen(argv[2]);
		for (int i = 0; i < len; i++) {
			if (!(argv[2][i] >= '0' && argv[2][i] <= '9')) {
				cout << "The third paramater after -c should be number that indicate the sudoku you want.\n";
				if (argv[2][i] == '+' || argv[2][i] == '-' || argv[2][i] == '/' || argv[2][i] == '*') {
					cout << "I am not recommand you input a expression to represent the number.\n";
					cout << "Just input the number is good!\n";
				}
				return 1;
			}
			number_sudoku = 10 * number_sudoku + argv[2][i] - '0';
			if (number_sudoku > MAX_number) 
			{
				cout << "The number is too large\n";
				return 1;
			}
		}
		

		if (number_sudoku > 1000000 || number_sudoku < 1) {
			cout << "The number is too large,the number should be 1-1000000" << endl;
			return 1;
		}
		
		FILE* file;
		file = freopen("sudoku.txt", "w", stdout);
		if (!file) {
			cout << "No files exist,create sudoku.txt first!\n";
			return 1;
		}
		
		Generator generator(number_sudoku, file);
		generator.generate();
	}

	if (compare(argv[1], "-s")) {
		solve_path = freopen(argv[2], "r",stdin);
		//solve_path = freopen("solve.txt", "r", stdin);
		if (!solve_path) {
			cout << "The file path is not right,please check.";
			return 1;
		}
		Solver solver(solve_path);
		solver.incom();
	}

	return 0;
}

bool compare(char* a, char* b) {
	if (strlen(a) != strlen(b))
		return false;
	for (int i = 0; i < (int)strlen(a); i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}