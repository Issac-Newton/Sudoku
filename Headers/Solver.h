#pragma once
#ifndef __SOLVER_H__
#define __SOLVER_H__

#pragma warning(disable : 4996)
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

class Solver{
public:
	typedef queue<int> qi;
	typedef map<int,qi> mqi;
	mqi possible_result;
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

			int filled;
			bool first = true;
			filled = first_check(first);
			while (filled > 8)
			{
				if (first)
				{
					first = false;
				}
				filled = first_check(first);
			}
			if (dfs(0))
			{
				Out();
			}
			possible_result.clear();
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
				temp[pointer] = Sudoku[i][j] + '0';
				pointer++;
				if (j != 8) 
				{
					temp[pointer] = ' ';
					pointer++;
				}
				//fprintf(file_write,"%d ",incom_sudoku[i][j]);
			}
			//fprintf(file_write,"\n");
			temp[pointer] = '\n';
			pointer++;
		}
		//fprintf(file_write,"\n");
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

		queue<int> writeable = possible_result[tot];
		while(writeable.size() > 0)
		{
			incom_sudoku[line][col] = writeable.front();
			if (check(line, col, writeable.front()))
			{
				if (dfs(tot + 1)) 
				{
					return true;
				}
			}

			incom_sudoku[line][col] = 0;
			writeable.pop();
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

	int first_check(bool first)
	{
		int fill_count = 0;
		for (int i = 0; i < 9; i++) 
		{
			for (int j = 0; j < 9; j++)
			{
				if (incom_sudoku[i][j] == 0)
				{
					int fill_in;
					fill_in = count_ok(i, j,first);
					if (fill_in > 0)
					{
						incom_sudoku[i][j] = fill_in;
						fill_count++;
					}
				}
			}
		}
		return fill_count;
	}

	int count_ok(int line, int col,bool first)
	{
		int ans = 0;
		bool exist[10];
		memset(exist,0,sizeof(exist));
		//line analyse
		for (int i = 0; i < 9; i++)
		{
			if (incom_sudoku[line][i] > 0)
			{
				exist[incom_sudoku[line][i]] = true;
			}
		}

		//col analyse
		for (int i = 0; i < 9; i++)
		{
			if (incom_sudoku[i][col] > 0)
			{
				exist[incom_sudoku[i][col]] = true;
			}
		}

		//nine call check
		int base_line = line / 3 * 3, base_col = col / 3 * 3;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (incom_sudoku[base_line + i][base_col + j] > 0)
				{
					exist[incom_sudoku[base_line + i][base_col + j]] = true;
				}
			}
		}

		int ans_count = 0;
		for (int i = 1; i < 10; i++)
		{
			//if (ans != 0 && !exist[i])
			//{
			//	return 0;
			//}
			if (!exist[i])
			{
				if (first)
				{
					possible_result[line * 9 + col].push(i);
				}
				if (ans == 0)
				{
					ans = i;
				}
				ans_count++;
			}

		}
		if (ans_count > 1)
		{
			return 0;
		}
		return ans;
	}

};

#endif