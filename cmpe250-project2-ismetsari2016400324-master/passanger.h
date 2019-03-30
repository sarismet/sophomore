#ifndef GULRU_PASSANGER_H
#define GULRU_PASSANGER_H

#include <iostream>
using namespace std;
class passanger {
public:

    int ftime = 0;
    int comingtime = 0;
    int checktime = 0;
    int securitytime = 0;

    bool online = false;
    bool vip = false;

    int checkingtime = 0;
    int securitingtime = 0;


    int waiting = 0;
    int timepass = 0;

    passanger();
    passanger(const passanger&);
    passanger(passanger&&);
    passanger operator=(const passanger&);
    passanger operator=(passanger&&);
    bool operator <(const passanger& other) ;


};


#endif //GULRU_PASSANGER_H