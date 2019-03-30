#include <iostream>
#include <cstdio>
#include <string>
#include<fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;
class Graph {


    public:

    int V;
    int size;
    vector<pair<int,int>> *adj;
        Graph(int V);
};
Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<pair<int,int>>[V];
    size=V;
}

void rabinKarp(string str, string pat,Graph& g3) {
    if (str.length() && pat.length()) {
        int n = str.length();
        int m = pat.length();
        int i, j;
        int s = 0, p = 0;
        const int pm = 256;
        const int q =101;
        int h = 1;
        bool flag = false;


        for (i = 0; i < m-1; i++)
            h = (h * pm) % q;


        for (i = 0; i < m; i++) {
            s = (pm * s + str[i]) % q;
            p = (pm * p + pat[i]) % q;
        }

        for (i = 0; i <= n-m; i++) {
            if (s == p) {
                for (j = 0; j < m; j++)
                    if (str[i+j] != pat[j])
                        break;
                if (j == m) {
    				g3.adj[i].emplace_back(make_pair(i,i+j));
                    flag = true;
                }
            }
            s = (pm * (s - h * str[i]) + str[i+m]) % q;
            if (s < 0)
                s = s + q;
        }
        if (!flag)
            cout<<"Pattern not found.."<<endl;
        return;
    }
    cout<<"Text or pattern cannot be empty.."<<endl;
    return ;
}
long long int recursive2(Graph g3,long long int **array,pair<int,int> root){

    if(root.second==g3.size){
        array[root.first][root.second]=1;
        return 1;
    }else{
        if(g3.adj[root.second].empty()){
            array[root.first][root.second]=0;
            return 0;

        }
    }

    long long int result=0;
    for (int i = 0; i <g3.adj[root.second].size() ; i++) {
           if(array[g3.adj[root.second][i].first][g3.adj[root.second][i].second]!=-1){
                result=result+array[g3.adj[root.second][i].first][g3.adj[root.second][i].second]%1000000007;
            }else if(array[g3.adj[root.second][i].first][g3.adj[root.second][i].second]==-1){
                result=(result+recursive2(g3,array,g3.adj[root.second][i])%1000000007);
            }

    }
        array[root.first][root.second]=(result%1000000007);
    return result;
}
long long int recursive1(Graph g3,long long int **array){
    int size=g3.adj[0].size();
    long long int toreturn=0;
    for (int i = 0; i <size ; ++i) {
        toreturn=toreturn+recursive2(g3,array,g3.adj[0][i]);
    }
    return toreturn;
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }


    ifstream read(argv[1]);
    string str, pat;
    string line;
    int N;
    read>>str;
    read>>N;

    Graph g3(str.size());
    long long **array;
    array=new long long int *[str.size()+5];
    for (int j = 0; j <str.size()+5 ; ++j) {
        array[j]=new long long int [str.size()+5];
    }
    for (int k = 0; k <str.size()+5 ; ++k) {
        for (int i = 0; i <str.size()+5 ; ++i) {
            array[k][i]=-1;
        }
    }
    for (int i = 0; i <N ; ++i) {
       read>>pat;
       rabinKarp(str,pat,g3);
    }

    ofstream myfile;
    myfile.open (argv[2]);
    myfile <<(recursive1(g3,array)%1000000007)<<endl;
    myfile.close();

    return 0;
}
