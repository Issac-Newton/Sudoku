//这个是主函数的文件
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "Generator.h"
#include "Solver.h"
using namespace std;

bool compare(char* a, char* b);
int main(int argc,char** argv)
{
	int number_sudoku = 0;
	FILE* solve_path;
	if (argc != 3){
		cout << "Illegal paramater number\n";
		cout << "Usage: sudoku.exe -c n -->generate n sudoku finals. \n sudoku.exe -s path -->";
		cout << "Read sudoku from file in the given path,and solve them.\n";
		cout << "The charactre should be itself:such as C is not equal to c.\n";
		return 1;
	}
	//if (argv[0] != "sudoku.exe"){
	//	cout << "The executable file is wrong,it should be sudoku.exe\n";
//		return 1;
	//}
	
	if (!(compare(argv[1],"-c") || compare(argv[1],"-s"))){
		cout << "The first parameter should be -c or -s\n";
		cout << "-c means to generate the sudoku to file.\n";
		cout << "-s means to solve the sudoku from the file.\n";
		return 1;
	}
	if (compare(argv[1],"-c")){		
		int len = strlen(argv[2]);
		for (int i = len - 1; i >= 0; i--){
			if (!(argv[2][i] >= '0' && argv[2][i] <= 9)){
				cout << "The third paramater after -c should be number that indicate the sudoku you want.\n";
				if (argv[2][i] == '+' || argv[2][i] == '-' || argv[2][i] == '/' || argv[2][i] == '*'){
					cout << "I am not recommand you input a expression to represent the number.\n";
					cout << "Just input the number is good!\n";
				}
				return 1;
			}
			number_sudoku = 10 * number_sudoku + argv[2][i] - '0';
		}
		FILE* file;
		fopen_s(&file,"sudoku.txt", "w");
		if (!file){
		cout << "No files exist,create sudoku.txt first!\n";
		return 1;
		}
		Generator generator(number_sudoku,file);
		generator.generate();
	}

	if (compare(argv[1],"-s")){
		fopen_s(&solve_path,argv[2],"r");
		if (!solve_path){
			cout << "The file path is not right,please check.";
			return 1;
		}
		Solver solver(argv[2]);
		solver.incom();
	}
	return 0;
}

bool compare(char* a, char* b){
	if (strlen(a) != strlen(b))
		return false;
	for (int i = 0; i < (int)strlen(a); i++){
		if (a[i] != b[i])
			return false;
	}
	return true;
}