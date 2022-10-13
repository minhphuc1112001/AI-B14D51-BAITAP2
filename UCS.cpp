#include<iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
#include "UCS.h"
#include "Constants.h"
#include "memory.h"
using namespace std;

UCS::UCS(Network * g) : Framework(g)
{
}

UCS::~UCS()
{
}

// graph
vector<vector<int> > graph;
// map to store cost of edges
map<pair<int, int>, int> cost;

void UCS::InitUCS(string filein) {
    // create the graph
    graph.resize(Constants::n_nodes);

    fstream fin;
    fin.open(filein, ios::in);

    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        // add edge
        graph[u].push_back(v);
        // add the cost
        cost[make_pair(u, v)] = w;
    }
    fin.close();
}

// returns the minimum cost in a vector( if
// there are multiple goal states)
vector<int> UCS::uniform_cost_search(vector<int> goal, int start)
{
    // minimum cost upto
    // goal state from starting
    // state
    vector<int> answer;
 
    // create a priority queue
    priority_queue<pair<int, int> > queue;
 
    // set the answer vector to max value
    for (int i = 0; i < goal.size(); i++)
        answer.push_back(INT_MAX);
 
    // insert the starting index
    queue.push(make_pair(0, start));
 
    // map to store visited node
    map<int, int> visited;
 
    // count
    int count = 0;
 
    // while the queue is not empty
    while (queue.size() > 0) {
 
        // get the top element of the
        // priority queue
        pair<int, int> p = queue.top();
 
        // pop the element
        queue.pop();
 
        // get the original value
        p.first *= -1;
 
        // check if the element is part of
        // the goal list
        if (find(goal.begin(), goal.end(), p.second) != goal.end()) {
 
            // get the position
            int index = find(goal.begin(), goal.end(),
                             p.second) - goal.begin();
 
            // if a new goal is reached
            if (answer[index] == INT_MAX)
                count++;
 
            // if the cost is less
            if (answer[index] > p.first)
                answer[index] = p.first;
 
            // pop the element
            queue.pop();
 
            // if all goals are reached
            if (count == goal.size())
                return answer;
        }
 
        // check for the non visited nodes
        // which are adjacent to present node
        if (visited[p.second] == 0)
            for (int i = 0; i < graph[p.second].size(); i++) {
 
                // value is multiplied by -1 so that
                // least priority is at the top
                queue.push(make_pair((p.first +
                  cost[make_pair(p.second, graph[p.second][i])]) * -1,
                  graph[p.second][i]));
            }
 
        // mark as visited
        visited[p.second] = 1;
    }
    return answer;
}

double UCS::get_solution(bool is_ds){
    clock_t start = clock();
    InitUCS(Constants::FILEIN);
    // goal state
    vector<int> goal;
    goal.push_back(Constants::end);
    // get the answer
    vector<int> answer = uniform_cost_search(goal, Constants::start);

    // print the answer
    fstream fout;
    fout.open("output.out", ios::out | ios::trunc);
    fout << "UCS\n";
    fout << "Minimum cost from " << Constants::start << " to " << Constants::end << " is = " << answer[0];
    double vm, rss;
    process_mem_usage(vm, rss);
    fout << "\nMemory: " << "VM: " << vm << " KB" << "; RSS: " << rss << "KB" << endl;
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout << "Duration time UCS: " << time_taken * 1000 << " miliseconds";
    fout.close();
    return 0.0;
}