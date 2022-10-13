#pragma once
#include "Framework.h"

class BFS: public Framework
{
public:
	BFS(Network * g);
	~BFS();
	double get_solution(bool is_ds = true);
	void InitBFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
    void ResultBFS(int s, int t);
    void alg_BFS(int n, int s, int t, vector<vector<int>> Matrix);
    void runBFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix);
};

