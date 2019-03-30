#include "Graph.h"

Graph::Graph(int V) {
    this->V=V;
    adj= new vector<int>[V];
}
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}
void Graph::addEdge2(int v, vector<string> str)
{
    for (int i = 1; i <str.size() ; ++i) {
        int w=stoi(str[i]);
        addEdge(v,w);
    }

}

void Graph::SCCUtil(int u, int disc[], int low[], stack<int>* st,
                    bool stackMember[],vector<int>& gulru)
{


    static int time = 0;


    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;


    for (int i = 0; i < adj[u].size(); ++i)
    {


        int v = adj[u][i];


        vector<int>::iterator itere=gulru.begin();
        while(itere!=end(gulru)){

            if(*itere==v&&u!=v){
            itere=gulru.erase(itere);
            }
           else{
                itere++;
            }

        }

            if (disc[v] == -1)
            {

                SCCUtil(v, disc, low, st, stackMember,gulru);
                low[u]  = min(low[u], low[v]);
            }


            else if (stackMember[v] == true)
                low[u]  = min(low[u], disc[v]);



    }


    int w = 0;
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();

            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();

        stackMember[w] = false;
        st->pop();

    }

}
void Graph::SCC()
{
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();


    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }


    for (int i = 1; i <V; i++){
        if (disc[i] == -1){


                gulru.push_back(i);
                SCCUtil(i, disc, low, st, stackMember,gulru);


        }

    }

}

void Graph::write() {

    for (int i = 0; i <V ; ++i) {
        if(adj[i].empty()){
        }else{
            cout<<i<<". ";
            for (int j = 0; j <adj[i].size() ; ++j) {
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }

    }
}