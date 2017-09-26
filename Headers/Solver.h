#pragma once
#ifndef __SOLVER_H__
#define __SOLVER_H__

#pragma warning(disable : 4996)

#include <map>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

class Solver{
public:
	int incom_sudoku[9][9];
	FILE* file;
	FILE* file_write;
	
	Solver(FILE* path,FILE* ans_path)
	{
		file = path;
		file_write = ans_path;
		memset(incom_sudoku,0,sizeof(incom_sudoku));
	}

	void incom()
	{
		while (true){
			if (fscanf_s(file, "%d", &incom_sudoku[0][0]) == EOF)
			{
				break;
			}

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++){
					if (i == 0 && j == 0) continue;
					fscanf_s(file,"%d",&incom_sudoku[i][j]);
				}
			}
			
			if (dfs(0))
			{
				Out();
			}
		}
	}

private:
	void Out()
	{
		int pointer = 0;
		char temp[165];
		memset(temp, 0, sizeof(temp));

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				temp[pointer] = incom_sudoku[i][j] + '0';
				pointer++;
				if (j != 8) 
				{
					temp[pointer] = ' ';
					pointer++;
				}
			}
			temp[pointer] = '\n';
			pointer++;
		}
		temp[pointer] = '\n';
		fputs(temp, file_write);
	}

	bool dfs(int tot){             
		if (tot > 80)
		{
			return true;
		}
		
		int line = tot / 9;
		int col = tot % 9;

		if (incom_sudoku[line][col] > 0)
		{
		    return dfs(tot + 1);
		}

		//queue<int> writeable = possible_result[tot];
		//while(writeable.size() > 0)
		for(int i = 1;i <= 9;i++)
		{
			//incom_sudoku[line][col] = writeable.front();
			incom_sudoku[line][col] = i;
			if (check(line, col, i))
			{
				if (dfs(tot + 1)) 
				{
					return true;
				}
			}

			incom_sudoku[line][col] = 0;
		}
		
		return false;
	}

	bool check(int line, int col,int num){
		for (int i = 0; i < 9; i++){
			if ((col != i) && incom_sudoku[line][i] == num) {
				return false;
			}
		}

		for (int i = 0; i < 9; i++){
			if ((i != line) && incom_sudoku[i][col] == num){
				return false;
			}
		}

		int base_line = line / 3 * 3;
		int base_col = col / 3 * 3;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if ((line != base_line + i) && (col != base_col + j) &&
					incom_sudoku[base_line + i][base_col + j] == num){
					return false;
				}
			}
		}
		return true;
	}

};

#endif