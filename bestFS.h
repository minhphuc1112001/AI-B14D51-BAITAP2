#pragma once
#include "Framework.h"

class bestFS: public Framework
{
public:
	bestFS(Network * g);
	~bestFS();
	double get_solution(bool is_ds = true);
    void InitBestFS(string filein);
    void addedge(int x, int y, int cost);
    void best_first_search(int actual_Src, int target, int n);
};