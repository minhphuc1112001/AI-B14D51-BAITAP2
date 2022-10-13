#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>
#include "bestFS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

bestFS::bestFS(Network * g) : Framework(g)
{
}

bestFS::~bestFS()
{
}

typedef pair<int, int> pi; 
vector<vector<pi> > graphBestFS;


void bestFS::addedge(int x, int y, int cost)
{
    graphBestFS[x].push_back(make_pair(cost, y));
    graphBestFS[y].push_back(make_pair(cost, x));
}

 void bestFS::InitBestFS(string filein) {
    graphBestFS.resize(Constants::n_nodes);
    fstream fin;
    fin.open(filein, ios::in);
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        addedge(u, v, w);
    }
    fin.close();
}

// Function For Implementing Best First Search
// Gives output path having lowest cost
void bestFS::best_first_search(int actual_Src, int target, int n)
{
    fstream fout;
    fout.open("output.out", ios::app);
    fout << "Duong di: ";
    vector<bool> visited(n, false);
    // MIN HEAP priority queue
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    // sorting in pq gets done by first value of pair
    pq.push(make_pair(0, actual_Src));
    int s = actual_Src;
    visited[s] = true;
    while (!pq.empty()) {
        int x = pq.top().second;
        // Displaying the path having lowest cost
        fout << x << " ";
        pq.pop();
        if (x == target)
            break;
 
        for (int i = 0; i < graphBestFS[x].size(); i++) {
            if (!visited[graphBestFS[x][i].second]) {
                visited[graphBestFS[x][i].second] = true;
                pq.push(make_pair(graphBestFS[x][i].first,graphBestFS[x][i].second));
            }
        }
    }
    fout.close();
}

double bestFS::get_solution(bool is_ds)
{
    clock_t start = clock();
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "Best First Search\n";
    fout.close();
	InitBestFS(Constants::FILEIN);
    best_first_search(Constants::start, Constants::end, Constants::n_nodes);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout.open("output.out", ios::app);
    fout << "\nDuration time best first search: " << time_taken * 1000 << " miliseconds";
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    fout.close();
	return 0.0;
}
