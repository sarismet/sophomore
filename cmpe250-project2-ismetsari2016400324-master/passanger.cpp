
#include "passanger.h"

passanger::passanger() {

}

passanger::passanger(const passanger & other) {
    this->ftime = other.ftime;
    this->comingtime = other.comingtime;
    this->checktime = other.checktime;
    this->securitytime = other.securitytime;

    this->vip = other.vip;
    this->online = other.online;

    this->checkingtime = other.checkingtime;
    this->securitingtime = other.securitingtime;

    this->timepass = other.timepass;
    this->waiting = other.waiting;
}

passanger::passanger(passanger && other) {
    this->ftime = move(other.ftime);
    this->comingtime = move(other.comingtime);
    this->checktime = move(other.checktime);
    this->securitytime = move(other.securitytime);

    this->vip = move(other.vip);
    this->online = move(other.online);

    this->checkingtime = move(other.checkingtime);
    this->securitingtime = move(other.securitingtime);

    this->timepass = move(other.timepass);
    this->waiting = move(other.waiting);
    other.ftime = 0;
    other.comingtime = 0;
    other.checktime = 0;
    other.securitytime = 0;
    other.vip = false;
    other.online = false;
    other.checkingtime = 0;
    other.securitingtime = 0;
    other.timepass = 0;
    other.waiting = 0;

}

passanger passanger::operator=(passanger && other) {
    this->ftime = move(other.ftime);
    this->comingtime = move(other.comingtime);
    this->checktime = move(other.checktime);
    this->securitytime = move(other.securitytime);

    this->vip = move(other.vip);
    this->online = move(other.online);

    this->checkingtime = move(other.checkingtime);
    this->securitingtime = move(other.securitingtime);

    this->timepass = move(other.timepass);
    this->waiting = move(other.waiting);
    other.ftime = 0;
    other.comingtime = 0;
    other.checktime = 0;
    other.securitytime = 0;
    other.vip = false;
    other.online = false;
    other.checkingtime = 0;
    other.securitingtime = 0;
    other.timepass = 0;
    other.waiting = 0;
    return *this;

}

passanger passanger::operator=(const passanger & other) {
    this->ftime = other.ftime;
    this->comingtime = other.comingtime;
    this->checktime = other.checktime;
    this->securitytime = other.securitytime;

    this->vip = other.vip;
    this->online = other.online;

    this->checkingtime = other.checkingtime;
    this->securitingtime = other.securitingtime;

    this->timepass = other.timepass;
    this->waiting = other.waiting;


    return *this;

}

bool  passanger::operator<(const passanger& other)  {
        return other.comingtime>this->comingtime;
}