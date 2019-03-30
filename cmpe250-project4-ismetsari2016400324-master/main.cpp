#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
# define INF 0x3f3f3f3f


using namespace std;

int main(int argc, char* argv[]) {
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

 ifstream fin(argv[1]);
 
    int size1;
    int size2;
    int x1;int y1;int x2;int y2;
    long int num = 0;
    long int **mainarray;
     long int **adj;
      bool **checker;
    char buffer[8192];
    int i = 0;
    int bytes = 0;
    char *p;
    int hasnum = 0;
    int eof = 0;
    int a=0;
    int b=0;
    int nw=0;
  
    while(!eof)
    {
        fin.read(buffer, sizeof(buffer));
        p = buffer;
        bytes = 8192;
        while(bytes > 0)
        {
            if (*p == 26)   // End of file marker...
            {
                eof = 1;
                break;
            }
            if (*p == '\n' || *p == ' ')
            {
                if (hasnum){
                 if(nw==0){
                     size1=num;
                     nw++;
                 }
                 else if(nw==1){
                     size2=num;
                     nw++;
                     mainarray=new long int *[size2];
                     adj=new long int*[size2];
                       checker=new bool*[size2];

                     for(int i = 0; i < size1; i++) {
                         mainarray[i] = new long int[size2];
                          adj[i]=new long int[size2];
                       checker[i]=new bool[size2];
                         
                     }
                 }
                 else if(nw>=2&&nw<=size1*size2+1){
                     mainarray[a][b]=num;
                       adj[a][b]=INF;
                       checker[a][b++]=false;
                     if(b==size2){
                         b=0;
                         a++;
                     }
                     nw++;
                 }
                 else if(nw==size1*size2+2){
                     nw++;
                 }
                 else if(nw==size1*size2+3){
                    x1=num;
                     nw++;
                 }else if(nw==size1*size2+4){
                     y1=num;
                     nw++;
                 }else if(nw==size1*size2+5){
                     x2=num;
                     nw++;
                 }else if(nw==size1*size2+6){
                     y2=num;
                     nw++;
                     eof=1;
                     break;
                 }

                }


                num = 0;
                p++;
                bytes--;
                hasnum = 0;
            }
            else if (*p >= '0' &&  *p <= '9')
            {
                hasnum = 1;
                num *= 10;
                num += *p-'0';
                p++;
                bytes--;
            }
            else
            {
                cout << "Error..." << endl;
                exit(1);
            }
        }
        memset(buffer, 26, sizeof(buffer));  // To detect end of files.
    }
    
  
    adj[x1-1][y1-1]=0;
    adj[x1][y1-1]=abs(mainarray[x1][y1-1]-mainarray[x1-1][y1-1]);//DOWN
    adj[x1-2][y1-1]=abs(mainarray[x1-1][y1-1]-mainarray[x1-2][y1-1]);//UP
    adj[x1-1][y1]=abs(mainarray[x1-1][y1]-mainarray[x1-1][y1-1]);//RIGHT
    adj[x1-1][y1-2]=abs(mainarray[x1-1][y1-1]-mainarray[x1-1][y1-2]);//LEFT

    queue<pair<int,int>> myqueue;

   myqueue.push(make_pair(x1,(y1-1)));
    myqueue.push(make_pair((x1-2),(y1-1)));
    myqueue.push(make_pair((x1-1),(y1)));
    myqueue.push(make_pair((x1-1),(y1-2)));
    //myqueue.push(make_pair((x1-1),(y1-1)));


    while (!myqueue.empty()) {

            int x = myqueue.front().first;
            int y = myqueue.front().second;
            myqueue.pop();
            checker[x][y] = false;
            if (x == 0 && y == 0) {

                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));

                        }

                    }
                }
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
            } else if (x == (size1 - 1) && y == 0) {

                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));
                        }
                    }
                }

                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }
            } else if (x == 0 && y == (size2 - 1)) {
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
            } else if (x == (size1 - 1) && y == (size2 - 1)) {

                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }

            } else if (x == 0 && y < size2 - 1 && y > 0) {
                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));
                        }
                    }
                }
            } else if (y == size2 - 1 && x < size1 - 1 && x > 0) {
                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }
            } else if (x == size1 - 1 && y < size2 - 1 && y > 0) {
                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }
                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));
                        }
                    }
                }
            } else if (x == 0 && y < size2 - 1 && y > 0) {
                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));
                        }
                    }
                }
                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
            } else if (x > 0 && x < size1 - 1 && y < size2 - 1 && y > 0) {
                if (adj[x][y] < adj[x + 1][y]) {//asagıya bakıyorum eger kucukse farka bakıcam
                    long int downdiff = abs(mainarray[x][y] - mainarray[x + 1][y]);
                    if (downdiff < adj[x + 1][y]) {
                        if (adj[x][y] < downdiff) {

                            adj[x + 1][y] = downdiff;

                        } else if (adj[x][y] >= downdiff) {
                            adj[x + 1][y] = adj[x][y];
                        }
                        if (!checker[x + 1][y]) {
                            checker[x + 1][y] = true;
                            myqueue.push(make_pair((x + 1), y));
                        }
                    }

                }
                if (adj[x][y] < adj[x][y + 1]) {//saga bakıyorum eger kucukse farka bakıcam
                    long int rightdiff = abs(mainarray[x][y] - mainarray[x][y + 1]);
                    if (rightdiff < adj[x][y + 1]) {
                        if (adj[x][y] < rightdiff) {
                            adj[x][y + 1] = rightdiff;
                        } else if (adj[x][y] >= rightdiff) {
                            adj[x][y + 1] = adj[x][y];
                        }
                        if (!checker[x][y + 1]) {
                            checker[x][y + 1] = true;
                            myqueue.push(make_pair(x, (y + 1)));
                        }
                    }
                }
                if (adj[x][y] < adj[x - 1][y]) {//yukarıya bakıyorum eger kucukse farka bakıcam
                    long int updiff = abs(mainarray[x][y] - mainarray[x - 1][y]);
                    if (updiff < adj[x - 1][y]) {
                        if (adj[x][y] < updiff) {
                            adj[x - 1][y] = updiff;
                        } else if (adj[x][y] >= updiff) {
                            adj[x - 1][y] = adj[x][y];
                        }
                        if (!checker[x - 1][y]) {
                            checker[x - 1][y] = true;
                            myqueue.push(make_pair((x - 1), y));
                        }
                    }
                }
                if (adj[x][y] < adj[x][y - 1]) {//sola bakıyorum eger kucukse farka bakıcam
                    long int leftdiff = abs(mainarray[x][y] - mainarray[x][y - 1]);
                    if (leftdiff < adj[x][y - 1]) {
                        if (adj[x][y] < leftdiff) {

                            adj[x][y - 1] = leftdiff;

                        } else if (adj[x][y] >= leftdiff) {
                            adj[x][y - 1] = adj[x][y];
                        }
                        if (!checker[x][y - 1]) {
                            checker[x][y - 1] = true;
                            myqueue.push(make_pair(x, (y - 1)));
                        }
                    }

                }
            }


        }
 ofstream myfile;
    myfile.open (argv[2]);
    myfile<<adj[x2-1][y2-1];
 myfile.close();
    return 0;
    }


