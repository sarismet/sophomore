#ifndef ISMET_GRAPH_H
#define ISMET_GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include<bits/stdc++.h>
using namespace std;
class Graph {
    int V;
    vector<int> *adj;


    void SCCUtil(int u, int disc[], int low[],
                 stack<int>* st, bool stackMember[],vector<int>& gulru);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void addEdge2(int v, vector<string> str);
    void SCC();
    vector <int> gulru;
    void write();


};


#endif