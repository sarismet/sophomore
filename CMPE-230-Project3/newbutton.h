#ifndef NEWBUTTON_H
#define NEWBUTTON_H
#include <QPushButton>
#include<QString>
//this class is the one that every QPushButton funtions is included but I add some bool and QString variables here
class Newbutton : public QPushButton
{
    Q_OBJECT

public:
    QString closedstring="asdasd";
        QString hard;
    bool ispressed=false;
    Newbutton(QString parent = "");
    ~Newbutton();

};

#endif // NEWBUTTON_H
