#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <mutex>
#include <vector>
#include <chrono>
#include <fstream>


#define INF 99999
#define MAX 10


void display(int arr[][MAX], int size);
void floyds(int D[][MAX], int S[][MAX], int size);


void floyds(int D[][MAX], int S[][MAX], int size) {
	int i, j, k, l;
	
	int Dk[MAX][MAX], Sk[MAX][MAX];
	
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			if(i == j) {
				Dk[i][j] = INF;
				Sk[i][j] = INF;
			} else {
				Dk[i][j] = 0;
				Sk[i][j] = 0;
			}
		}
	}
    //
	for(k = 0; k < size; k++) {
		for(l = 0; l < size; l++) {
			Dk[k][l] = D[k][l];
			Sk[k][l] = S[k][l];
			
			Dk[l][k] = D[l][k];
			Sk[l][k] = S[l][k];
		}
		for(i = 0; i < size; i++) {
			if(i == k) {
				continue;
			}
				
			for(j = 0; j < size; j++) {
				if(j == k) {
					continue;
				}
				if(i == j) {
					continue;
				}
				if(D[i][j] > D[i][k] + D[k][j]) {
					Dk[i][j] = D[i][k] + D[k][j];
					Sk[i][j] = (k+1);	//kth iteration, as indexing starts from 0 so, we add 1
				} else {
					Dk[i][j] = D[i][j];
					Sk[i][j] = S[i][j];
				}
			}
		}
		for(i = 0; i < size; i++) {
			for(j = 0; j < size; j++) {
				D[i][j] = Dk[i][j];
				S[i][j] = Sk[i][j];
			}
		}
	}	
    //
	printf("Distance array: \n");
	display(D, size);
	printf("Sequence array: \n");
	display(S, size);
}
void display(int arr[][MAX], int size) {
	int i, j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			if(arr[i][j] == INF) {
				printf("%10s ", "INF");
			} else {
				printf("%10d ", arr[i][j]);
			}
		}
		printf("\n");
	}
}
int main(void) {
    const auto MAX_T = std::thread::hardware_concurrency();
	int D[MAX][MAX] = {
		{INF, 4, 5, 2},
		{3, INF, 7, 3},
		{2, 2, INF, 5},
		{5, 9, 8, INF}
	};
	

    std::cout<<"max_thr: "<<MAX_T <<"\n";
	int S[MAX][MAX] = {
		{INF, 3, 1, 4},
		{1, INF, 3, 4},
		{1, 2, INF, 4},
		{1, 2, 3, INF}
	};
	
	int size = 4;		//total number of vertices in the graph
	
	floyds(D, S, size);
	
	return 0;
}
