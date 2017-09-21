//这个是主函数的文件
#include <iostream>
#include "Generator.h"
using namespace std;

int main()
{
	FILE* file;
	fopen_s(&file,"sudoku.txt", "w");
	if (!file){
		cout << "No files exist,create sudoku.txt first!\n";
		return 1;
	}
	Generator test(71,file);
	test.generate();
	return 0;
}