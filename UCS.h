#pragma once
#include "Framework.h"

class UCS: public Framework
{
public:
	UCS(Network * g);
	~UCS();
	double get_solution(bool is_ds = true);
    void InitUCS(string filein);
    vector<int> uniform_cost_search(vector<int> goal, int start);
};

