#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "DFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

DFS::DFS(Network * g) : Framework(g)
{
}

DFS::~DFS()
{
}

#define MAX 100
int dMin = 1e8;                   // đường đi ngắn nhất DFS
vector<bool> visited(MAX, false); // các đỉnh đã ghé thăm DFS
vector<int> mark, res;            // Lưu vết đường đi

void DFS::InitDFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    fstream fin;
    fin.open(filein, ios::in);
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = 0;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

int DFS::sumOfMark(vector<vector<int>> Matrix)
{
    int res = 0;
    for (int i = 0; i < mark.size() - 1; i++)
    {
        res += Matrix[mark[i]][mark[i + 1]];
    }
    return res;
}

void DFS::alg_DFS(int n, int u, int t, vector<vector<int>> Matrix)
{
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && Matrix[u][i])
        {
            mark.push_back(i);
            visited[i] = true;
            if (i == t)
            {
                if (sumOfMark(Matrix) < dMin)
                {
                    dMin = sumOfMark(Matrix);
                    res = mark;
                }
                mark.pop_back();
                visited[i] = false;
            }
            else
            {
                alg_DFS(n, i, t, Matrix);
                mark.pop_back();
                visited[i] = false;
            }
        }
    }
}

void DFS::ResultDFS(int s, int t){
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "DFS\n";
    fout << "Duong di ngan nhat tu " << s << " den " << t << " la:" << endl;
    for (int i = 0; i < res.size() - 1; i++)
    {
        fout << res[i] << "=>";
    }
    fout << res[res.size() - 1];
    fout << endl;
    fout << "Do dai duong di la : ";
    fout << dMin;
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void DFS::runDFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix) {
    clock_t start = clock();
    InitDFS(filein, n, s, t, Matrix);
    mark.push_back(s);
    visited[s] = true;
    alg_DFS(n, s, t, Matrix);
    ResultDFS(s, t);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time DFS: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double DFS::get_solution(bool is_ds)
{
	vector<vector<int>> Matrix;
    runDFS(Constants::FILEIN, Constants::n_nodes, Constants::start, Constants::end, Matrix);
	return 0.0;
}
