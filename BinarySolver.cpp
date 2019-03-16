#include <stdio.h>
#include <iostream>

using namespace std;

#define EMPTY 2
const int N = 14;

int puzzle06x06[6][6] = {
	{1, 2, 2, 1, 2, 2},
	{2, 2, 2, 1, 2, 0},
	{2, 2, 2, 2, 2, 2},
	{2, 0, 0, 2, 2, 0},
	{0, 2, 2, 2, 2, 2},
	{2, 2, 1, 2, 1, 2}
};

int puzzle14x14[14][14] = {
	{2, 2, 2, 2, 1, 1, 2, 2, 1, 2, 2, 0, 2, 2},
	{1, 2, 1, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2},
	{1, 2, 1, 2, 0, 2, 2, 2, 1, 2, 1, 2, 2, 1},
	{2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 0, 0, 2},
	{2, 0, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 0},
	{2, 0, 0, 2, 2, 0, 0, 2, 2, 1, 2, 2, 1, 2},
	{2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
	{2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1},
	{2, 2, 2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2},
	{2, 1, 2, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 0, 2, 2, 2, 2, 1, 2, 2, 0, 2},
	{1, 1, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2},
	{2, 1, 2, 2, 0, 2, 2, 1, 2, 1, 2, 2, 2, 1}	
};

void print(int puzzle[N][N]){
	for(int y = 0; y < N; y++){
		for(int x = 0; x < N; x++){
			if(puzzle[y][x] == EMPTY)
				cout << ".";
			else 
				cout << puzzle[y][x];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool compare(int a[N], int b[N]){
	for(int i = 0; i < N; i++){
		if(a[i] != b[i])
			return false;
	}
	return true;
}

void transpose(int puzzle[N][N]){
	for(int y = 0; y < N; y++){
		for(int x = y; x < N; x++){
			int temp = puzzle[y][x];
			puzzle[y][x] = puzzle[x][y];
			puzzle[x][y] = temp;
		}
	}
}

bool check_rows(int puzzle[N][N]){
	for(int y0 = 0; y0 < N; y0++)
		for(int y1 = y0+1; y1 < N; y1++)
			if(compare(puzzle[y0], puzzle[y1]))
				return false; 	

	for(int y = 0; y < N; y++){
		int n2=-1, n1=-1, n0=-1;
		int c0=0, c1=0;
		for(int x = 0; x < N; x++){
			n2 = n1;
			n1 = n0;
			n0 = puzzle[y][x];	
			if(n2 == n1 && n1 == n0)
				return false;

			if(puzzle[y][x] == 0)
				c0++;
			else if(puzzle[y][x] == 1)
				c1++;
			else 
				return false;
		}
		if(c0 != c1)
			return false;
	}

	return true;
}

bool isSolution(int puzzle[N][N]){
	if(check_rows(puzzle)){
		transpose(puzzle);
		if(check_rows(puzzle)){
			transpose(puzzle);
			return true;	
		}
		transpose(puzzle);
	}	
	return false;
}

bool isValid(int puzzle[N][N]){

	for(int y = 0; y < N; y++){
		int n2=-1, n1=-1, n0=-1;
		int c0 = 0, c1 = 0;
		for(int x = 0; x < N; x++){
			n2 = n1;
			n1 = n0;
			n0 = puzzle[y][x];	
			if(n0 != EMPTY && n2 == n1 && n1 == n0)
				return false;
			if(puzzle[y][x] == 0)
				c0++;
			if(puzzle[y][x] == 1)
				c1++;
		}
		if(c0 > N/2 || c1 > N/2)
			return false;
	}

	for(int x = 0; x < N; x++){
		int n2=-1, n1=-1, n0=-1;
		int c0 = 0, c1 = 0;
		for(int y = 0; y < N; y++){
			n2 = n1;
			n1 = n0;
			n0 = puzzle[y][x];	
			if(n0 != EMPTY && n2 == n1 && n1 == n0)
				return false;
			if(puzzle[y][x] == 0)
				c0++;
			if(puzzle[y][x] == 1)
				c1++;
		}
		if(c0 > N/2 || c1 > N/2)
			return false;
	}

	return true;
}

void update_xy(int &x, int &y){
	if(x == N-1){
		x = 0;
		y++;
	}else{
		x++;
	}
}

void solve(int puzzle[N][N], int x, int y){
	
	if(y == N){
		if(isSolution(puzzle))
			print(puzzle);
		return;
	}
	if(!isValid(puzzle))
		return;

	int x_old = x, y_old = y;
	if(puzzle[y][x] != EMPTY){
		update_xy(x, y);
		solve(puzzle, x, y);

		x = x_old;
		y = y_old;
	}else{
		int temp = puzzle[y][x];
		for(int i = 0; i < 2; i++){
			puzzle[y][x] = i;
			update_xy(x, y);
			solve(puzzle, x, y);

			x = x_old;
			y = y_old;
			puzzle[y][x] = temp;
		}
	}
}

int main(){
	print(puzzle14x14);
	solve(puzzle14x14, 0, 0);

	return 0;
}
