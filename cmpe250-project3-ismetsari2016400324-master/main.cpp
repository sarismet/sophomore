#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include "Graph.h"
#include <set>

using  namespace std;



template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
int main(int argc, char* argv[]) {

   ios_base::sync_with_stdio(false);
    if (argc != 3) {
        return 1;
    }
    ifstream read( argv[1]);
    
    string line;
    getline(read,line);
    Graph g3(stoi(line)+1);
    int raw=1;
    while(getline(read, line)){
        vector<string> words;
        split1(line,words);
        g3.addEdge2(raw,words);
        raw++;
    }

    g3.SCC();
    int size=g3.gulru.size();
    FILE *fp;
    fp = fopen(argv[2],"w");

    fprintf(fp,"%d %s",size," ");
    
    for(size_t i = 0; i <size; i++)
    {
       fprintf(fp,"%d %s",g3.gulru[i]," ");
    }
    



    return 0;
}
