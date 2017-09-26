#pragma once
#ifndef __GENEARTOR_H__
#define __GENERATOR_H__

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#define first_size 40320
using namespace std;

int Sudoku[9][9] = {
	{ 6, 2, 3, 4, 5, 1, 7, 8, 9 },
	{ 4, 5, 1, 7, 8, 9, 6, 2, 3 },
	{ 7, 8, 9, 6, 2, 3, 4, 5, 1 },
	{ 2, 6, 4, 3, 1, 5, 8, 9, 7 },
	{ 3, 1, 5, 8, 9, 7, 2, 6, 4 },
	{ 8, 9, 7, 2, 6, 4, 3, 1, 5 },
	{ 5, 3, 6, 1, 4, 2, 9, 7, 8 },
	{ 1, 4, 2, 9, 7, 8, 5, 3, 6 },
	{ 9, 7, 8, 5, 3, 6, 1, 4, 2 } };

int Sudoku_backup[9][9] = {
	{ 6, 2, 3, 4, 5, 1, 7, 8, 9 },
	{ 4, 5, 1, 7, 8, 9, 6, 2, 3 },
	{ 7, 8, 9, 6, 2, 3, 4, 5, 1 },
	{ 2, 6, 4, 3, 1, 5, 8, 9, 7 },
	{ 3, 1, 5, 8, 9, 7, 2, 6, 4 },
	{ 8, 9, 7, 2, 6, 4, 3, 1, 5 },
	{ 5, 3, 6, 1, 4, 2, 9, 7, 8 },
	{ 1, 4, 2, 9, 7, 8, 5, 3, 6 },
	{ 9, 7, 8, 5, 3, 6, 1, 4, 2 } };

class Generator{
public:
	double totTime;
	int count;
	struct node{
		int num;
		bool dir;
	};

	struct node location[9];
	FILE* file_write;

	Generator(int number,FILE* file){

		this->count = number;
		file_write = file;
		totTime = 0;
		for (int i = 0; i < 9; i++){
			if (i >= 6){
				location[i].num = i + 1;
			}
			else{
				location[i].num = i;
			}
			location[i].dir = true;
		}
	}

	void generate()
	{
		int number = 0;
		while (number < count){
			Out();
			number++;

			Line_exchange_floor(&number);
			Line_exchange_middle(&number);
			Line_exchange_ground(&number);
			if (number < count){
				TransForm();
				Change();
			}
		}
	}


private:
	void Out()
	{
		int pointer = 0;
		char temp[165];
		memset(temp,0,sizeof(temp));
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				temp[pointer] = Sudoku[i][j] + '0';
				pointer++;
				if (j != 8) {
					temp[pointer] = ' ';
					pointer++;
				}
			}
			temp[pointer] = '\n';
			pointer++;
		}
		
		temp[pointer] = '\n';
		fputs(temp,file_write);
	}

	void TransForm(){
		int move = 0;
		int move_num = 0;
		for (int i = 1; i <= 8; i++){
			if (location[i].dir && (i-1>0)){
				bool moveable;
				moveable = location[i].num > location[i - 1].num;
				if (moveable){
					move = move_num > location[i].num ? move : i;
					move_num = move_num > location[i].num ? move_num : location[i].num;
				}
			}
			else if(!location[i].dir && (i+1<9)){
				bool moveable;
				moveable = location[i].num > location[i + 1].num;
				if (moveable){
					move = move_num > location[i].num ? move : i;
					move_num = move_num > location[i].num ? move_num : location[i].num;
				}
			}
		}

		int temp = move_num;
		bool temp_dir = location[move].dir;
		if (temp_dir){  //change with left
			location[move].num = location[move - 1].num;
			location[move].dir = location[move - 1].dir;
			location[move - 1].num = temp;
			location[move - 1].dir = temp_dir;
		}
		else{          //change with right
			location[move].num = location[move + 1].num;
			location[move].dir = location[move + 1].dir;
			location[move + 1].num = temp;
			location[move + 1].dir = temp_dir;
		}
		

		for (int i = 1; i <= 8; i++){
			if (location[i].num > move_num){
				location[i].dir = !location[i].dir;
			}
		}
	}

	void Change(){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (Sudoku_backup[i][j] < 6){
					Sudoku[i][j] = location[Sudoku_backup[i][j]].num;
				}
				else if (Sudoku_backup[i][j] > 6){
					Sudoku[i][j] = location[Sudoku_backup[i][j] - 1].num;
				}
			}
		}
	}
	
	void Line_exchange_floor(int* number){
		if (*number < count){
			swap_line(2, 1);
			*number = (*number) + 1;
			Out();
			Line_exchange_middle(number);
		}
		if(*number < count)
		{
			swap_line(2, 1);
		}
	}

	void Line_exchange_middle(int* number){
		if (*number < count){
			swap_line(3, 4);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count){
			swap_line(4,5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count){
			swap_line(3, 5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}

		if (*number < count){
			swap_line(3,4);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}

		if (*number < count){
			swap_line(4,5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count)
		{
			swap_line(3, 5);
		}
	}

	void Line_exchange_ground(int* number){
		if (*number < count){
			swap_line(6, 7);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count){
			swap_line(7, 8);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count){
			swap_line(6,8);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count){
			swap_line(6,7);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count){
			swap_line(7,8);
			Out();
			*number = (*number) + 1;
		}
		if(*number < count)
		{
			swap_line(6, 8);
		}
	}

	void swap_line(int a, int b){
		int temp;
		for (int i = 0; i < 9; i++){
			temp = Sudoku[a][i];
			Sudoku[a][i] = Sudoku[b][i];
			Sudoku[b][i] = temp;
		}
	}
};

#endif