#include <iostream>
#include <algorithm>
#include "passanger.h"
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <list>
#include <queue>
#include <cstdlib>
auto start = chrono::steady_clock::now();
using  namespace std;
void insertionSort( vector<passanger>& a )
{

    for( int p = 1; p <a.size(); ++p )
    {
        passanger tmp =  a[ p ] ;
        int j;
        for( j = p; j > 0 && tmp.comingtime<a[ j - 1 ].comingtime; --j ){
            a[ j ] =  a[ j - 1 ] ;
        }

        a[ j ] = ( tmp );
    }
}

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
passanger fic(const vector<string> words){
    passanger passanger1;
    for(int i=0;i<words.size();i++){
        if(i==0) passanger1.comingtime=(stoi(words[i]));
        if(i==1) passanger1.ftime=(stoi(words[i]));
        if(i==2) passanger1.checktime=(stoi(words[i]));
        if(i==3) passanger1.securitytime=(stoi(words[i]));
        if(i==4) {if(words[i]=="N") passanger1.vip=(false); else passanger1.vip=(true);}
        if(i==5) {if(words[i]=="N") passanger1.online=(false); else passanger1.online=(true);}
    }
    return passanger1;
}
void pushtopass(vector<passanger>& pass,passanger& temp){
    if(!pass.empty()){
        vector<passanger>::iterator itere=pass.begin();
        while(itere!=end(pass)){
            if(temp.comingtime<=itere->comingtime){
                pass.insert(itere,temp);
                return;
            }
               itere++;
        }
        pass.emplace_back(temp);
    }
    else{
        pass.emplace_back(temp);
    }


}
void pushtoforcheck(list<passanger>& targetlist,passanger& temp ,int devir){

    if(!targetlist.empty()&&(devir==2||devir==4||devir==6||devir==8)){
        list<passanger>::iterator itere=targetlist.begin();
        while(itere!=end(targetlist)){
            if(temp.ftime<itere->ftime){
                targetlist.insert(itere,temp);
                return;
            }else if(temp.ftime==itere->ftime){

                if(temp.comingtime<itere->comingtime){
                    targetlist.insert(itere,temp);
                    return;
                }
            }
            itere++;
        }
        targetlist.emplace_back(temp);
    }else{
        targetlist.emplace_back(temp);
    }

}

void fromrawtoforcheckordirectlyforsecurity( list<passanger>::iterator& itereraw,list<passanger>& raw,list<passanger>& forcheck,list<passanger>& forsecurity,list<passanger>& lastcheck,int devir,int minute){


    if(itereraw!=end(raw)&&itereraw->comingtime==minute){
            passanger temp=*itereraw;
            if(devir==7||devir==8){
                if(itereraw->vip==true&&itereraw->online==false){
                    lastcheck.push_back(temp);
                }else if(itereraw->online==false&&itereraw->vip==false){
                    pushtoforcheck(forsecurity,temp,devir);
                }else {
                   pushtoforcheck(forcheck,temp,devir);

                }
            }
            else if(devir==5||devir==6){
                if(itereraw->online==false){
                    pushtoforcheck(forsecurity,temp,devir);
                }else{
                    pushtoforcheck(forcheck,temp,devir);
                }

            }
            else{

                pushtoforcheck(forcheck,temp,devir);
            }
        itereraw++;
    }
    return;

}

void fromforchecktocheck(list<passanger>& forcheck,vector<passanger>& check,int& numberofchecking,int devir ){

    list<passanger>::iterator itereforcheck;
    while(check.size()!=numberofchecking&&!(forcheck.empty())){
        itereforcheck=forcheck.begin();
        passanger temp=*itereforcheck;
        check.emplace_back(temp);
        forcheck.pop_front();

    }
}

void fromchecktoforsecurityordirectlylastcheck(vector<passanger>& check,list<passanger>& forsecurity,int devir,list<passanger>& lastcheck,list<passanger>& security,int numberofsecuritycheck){

    insertionSort(check);
    vector<passanger>::iterator iterecheck=check.begin();
    while(iterecheck!=check.end()){
        if(iterecheck->checkingtime==iterecheck->checktime){
            passanger temp=(*iterecheck);
            if((devir==3||devir==4||devir==7||devir==8)&&iterecheck->vip==true){
                lastcheck.emplace_back(temp);
            }
            else{
                if(security.size()!=numberofsecuritycheck&&forsecurity.empty()){
                    security.emplace_back(temp);
                }
                else{
                   pushtoforcheck(forsecurity,temp,devir);
                }
            }
            iterecheck=check.erase(iterecheck);


        }
        else{
            iterecheck++;
        }

    }
}

void fromforsecuritytosecurity(list<passanger>& forsecurity,list<passanger>& security,int& numberofsecuritycheck,int devir ){

    list<passanger>::iterator itereforsecurity;

    while(security.size()!=numberofsecuritycheck&&!(forsecurity.empty())){
        itereforsecurity=forsecurity.begin();
        passanger temp=(*itereforsecurity);
        security.emplace_back(temp);
        forsecurity.pop_front();


    }
}

void fromsecuritytolastcheck(list<passanger>& security,list<passanger>& lastcheck){

    list<passanger>::iterator iteresecurity=security.begin();
    while(iteresecurity!=security.end()){
        if(iteresecurity->securitytime==iteresecurity->securitingtime){
            passanger temp=(*iteresecurity);
            lastcheck.emplace_back(temp);
            iteresecurity=security.erase(iteresecurity);
        }
        else{
            iteresecurity++;
        }

    }
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;


    ifstream read( argv[1]);
    ofstream myfile;

    string line;  getline(read,line); stringstream stream(line);int numberofpassanger;  int numberofchecking;    int numberofsecuritycheck;stream>>numberofpassanger;
    stream>>numberofchecking;   stream>>numberofsecuritycheck;  list<passanger> raw;list<passanger> forcheck;vector<passanger> check;  list<passanger> forsecurity;
    list<passanger> security;list <passanger> lastcheck;
    while(getline(read, line)){
        vector<string> words;
        split1(line,words);
        raw.emplace_back(fic(words));
    }

    for (int devir = 1; devir <9 ; ++devir) {
        forcheck.clear();      check.clear();   forsecurity.clear();        security.clear();   lastcheck.clear();
        int total=0, misses=0;    float avg=0.0;
       int minute=(raw.begin())->comingtime;
        list<passanger> ::iterator itereraw=raw.begin();
        list<passanger> ::iterator itereraw2=raw.end();
        itereraw2--;
        int end=(itereraw2)->comingtime;
       while(true){
           fromsecuritytolastcheck(security,lastcheck);

           fromforsecuritytosecurity(forsecurity,security,numberofsecuritycheck,devir);

           fromchecktoforsecurityordirectlylastcheck(check,forsecurity,devir,lastcheck,security,numberofsecuritycheck);

           fromforchecktocheck(forcheck,check,numberofchecking,devir);

           fromrawtoforcheckordirectlyforsecurity(itereraw,raw,forcheck,forsecurity,lastcheck,devir,minute);

           fromforchecktocheck(forcheck,check,numberofchecking,devir);

           fromforsecuritytosecurity(forsecurity,security,numberofsecuritycheck,devir);

           if(!security.empty()){
               list<passanger>::iterator itereofsecurity=security.begin();
               while(itereofsecurity!=security.end()){
                   itereofsecurity->securitingtime++;
                   itereofsecurity++;
               }
           }

           if(!check.empty()){
               vector<passanger>::iterator itereofcheck=check.begin();
               while(itereofcheck!=check.end()){
                   itereofcheck->checkingtime++;
                   itereofcheck++;
               }
           }

           if(!lastcheck.empty()){
               list<passanger> ::iterator itere3=lastcheck.begin();

               while(itere3!=lastcheck.end()){

                       if(itere3->ftime<(minute)){
                           misses++;
                       }
                       total=total+(minute-itere3->comingtime);

                     itere3++;
               }
               lastcheck.clear();


           }

           minute++;
           if(minute>end&&forcheck.empty()&&check.empty()&&forsecurity.empty()&&security.empty()&&lastcheck.empty()){
               break;
           }

       }

        avg=total/(float)numberofpassanger;
        cout<<"avg : "<<avg<<"  misses : "<<misses<<endl;
         myfile.open (argv[2],ios::out|ios::in|ios::app);
        myfile << avg << " " << misses<< endl;
        myfile.close();

    }

    auto end = chrono::steady_clock::now();
    cout << chrono::duration <double, milli> ( (end-start)).count() << " ms" << endl;
    return 0;
}
