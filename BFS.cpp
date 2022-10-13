#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "BFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

BFS::BFS(Network * g) : Framework(g)
{
}

BFS::~BFS()
{
}

#define MAX 100
#define TRUE 1
#define FALSE 0
#define VOCUNG 10000000

vector<int> truoc(MAX, 0);   // mảng đánh dấu đường đi.
vector<int> d(MAX, 0);       // mảng đánh dấu khoảng cách.
vector<int> chuaxet(MAX, 0); // mảng đánh dấu đỉnh đã được gán nhãn.

void BFS::InitBFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    fstream fin;
    fin.open(filein, ios::in);
    Matrix = vector<vector<int>>(MAX, vector<int>(MAX, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = VOCUNG;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

void BFS::ResultBFS(int s, int t)
{
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "BFS\n";
    fout << "Duong di ngan nhat tu " << s << " den " << t << " la" << endl;
    fout << t << "<=";
    int i = truoc[t];
    while (i != s)
    {
        fout << i << "<=";
        i = truoc[i];
    }
    fout << s;
    fout << endl
         << "Do dai duong di la : " << d[t];
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
}

void BFS::alg_BFS(int n, int s, int t, vector<vector<int>> Matrix)
{
    int u, minp;
    // khởi tạo nhãn tạm thời cho các đỉnh.
    for (int v = 0; v < n; v++)
    {
        d[v] = Matrix[s][v];
        truoc[v] = s;
        chuaxet[v] = FALSE;
    }
    truoc[s] = 0;
    d[s] = 0;
    chuaxet[s] = TRUE;
    // bươc lặp
    while (!chuaxet[t])
    {
        minp = VOCUNG;
        // tìm đỉnh u sao cho d[u] là nhỏ nhất
        for (int v = 0; v < n; v++)
        {
            if ((!chuaxet[v]) && (minp > d[v]))
            {
                u = v;
                minp = d[v];
            }
        }
        chuaxet[u] = TRUE; // u la dinh co nhan tam thoi nho nhat
        if (!chuaxet[t])
        {
            // gán nhãn lại cho các đỉnh.
            for (int v = 0; v < n; v++)
            {
                if ((!chuaxet[v]) && (d[u] + Matrix[u][v] < d[v]))
                {
                    d[v] = d[u] + Matrix[u][v];
                    truoc[v] = u;
                }
            }
        }
    }
}

void BFS::runBFS(string filein, int n, int s, int t, vector<vector<int>> &Matrix)
{
    // BFS
    clock_t start = clock();
    InitBFS(filein, n, s, t, Matrix);
    alg_BFS(n, s, t, Matrix);
    ResultBFS(s, t);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duration time BFS: " << time_taken * 1000 << " miliseconds";
    fout.close();
}

double BFS::get_solution(bool is_ds){
    vector<vector<int>> Matrix;
    runBFS(Constants::FILEIN, Constants::n_nodes, Constants::start, Constants::end, Matrix);
    return 0.0;
}