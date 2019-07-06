#include <QtGui>
#include <sstream>
#include <string>
#include <QtGlobal>
#include<QTimer>
#include<QDebug>
#include "finddialog.h"
using namespace std;

//this is the constructor of FindDialog.I get the click signal here and send them into showinfo and al slots.
FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{

    //first we call the firststart to create the all utton values and properties.
    firststart();

    //then we create a time interval and then make the buttons 'X'
    controltimer = new QTimer(this);
    controltimer->setInterval(9000);
    controltimer->setSingleShot(true);
    connect(controltimer, SIGNAL(timeout()), SLOT(besiktas()));
    controltimer->start();
    QObject::connect(&buttongroup, SIGNAL(buttonClicked(int)),
                       this, SLOT(al(int)));

    QObject::connect(&buttongroup, SIGNAL(buttonClicked(int)),
                       this, SLOT(showinfo(int)));

 }
//closeinfowindow is to close the window that would open after the user complete the table.
void FindDialog::closeinfowindow(){
    windows.close();
        isitwin=false;
}
//this is designed to create the window if the user complete the table
void FindDialog::run(){

    QString bas="You win. You found 12 different pairs in ";
    bas.append(labels[3]->text());
    bas.append(" Tries");
    //first the remove the old layout and
    layout1.removeWidget(kartus);
    //create an other new button and add it to the new layout
    kartus= new Newbutton(bas);
    layout1.addWidget(kartus);
    windows.setLayout(&layout1);
    windows.resize(320, 240);
    windows.show();
    windows.setWindowTitle("PairsGame result");
    //if you click the button the window will be closed.
    QObject::connect(kartus, SIGNAL(clicked()),
                       this, SLOT(closeinfowindow()));

}
//this is to design the first table's properties.
void FindDialog::firststart(){
    //they are QVector consisting QString each of them has a duplicate letter.
    QVector<QString> A(2);A.fill("A");
    QVector<QString> B(2);B.fill("B");
    QVector<QString> C(2);C.fill("C");
    QVector<QString> D(2);D.fill("D");
    QVector<QString> E(2);E.fill("E");
    QVector<QString> F(2);F.fill("F");
    QVector<QString> G(2);G.fill("G");
    QVector<QString> H(2);H.fill("H");
    QVector<QString> I(2);I.fill("I");
    QVector<QString> K(2);K.fill("K");
    QVector<QString> L(2);L.fill("L");
    QVector<QString> M(2);M.fill("M");

    QVector< QVector< QString > > vectors;
    vectors.append(A);vectors.append(B);vectors.append(C);vectors.append(D);vectors.append(E);vectors.append(F);vectors.append(G);vectors.append(H);vectors.append(I);vectors.append(K);vectors.append(L);vectors.append(M);


        //they are QLabels to show the values of Pairs and Tries
        labels[0]= new QLabel();labels[0]->setText("Pairs");layout0.addWidget(labels[0],0,0);
         labels[1]= new QLabel();labels[1]->setText("0");layout0.addWidget(labels[1],0,1);
          labels[2]= new QLabel();labels[2]->setText("Tries");layout0.addWidget(labels[2],0,2);
           labels[3]= new QLabel();labels[3]->setText("0");layout0.addWidget(labels[3],0,3);

        //this is reset button
           button[4] = new Newbutton("Reset");
           layout0.addWidget(button[4],0,4,1,2);
            buttongroup.addButton(button[4],4) ;

        //the all of the for loop to create the buttons in 1'th - 5 'th rows
            for(int i=0;i<6;i++){
                int randomValue = qrand() % vectors.size();
                QString sa=vectors[randomValue].back();
                vectors[randomValue].pop_back();
                if(vectors[randomValue].size()==0){
                    QVector<QString> temp=vectors[vectors.size()-1];
                    vectors[randomValue]=temp;
                    vectors.pop_back();
                }
                button[5+i] = new Newbutton(sa);
                button[5+i]->closedstring="X";
                layout0.addWidget(button[5+i],1,i);
                buttongroup.addButton(button[5+i],5+i) ;
            }

            for(int i=0;i<6;i++){
                int randomValue = qrand() % vectors.size();
                QString sa=vectors[randomValue].back();
                vectors[randomValue].pop_back();
                if(vectors[randomValue].size()==0){
                    QVector<QString> temp=vectors[vectors.size()-1];
                    vectors[randomValue]=temp;
                    vectors.pop_back();
                }
                button[11+i] = new Newbutton(sa);
                  button[11+i]->closedstring="X";
                layout0.addWidget(button[11+i],2,i);
                buttongroup.addButton(button[11+i],11+i) ;
            }

            for(int i=0;i<6;i++){
                int randomValue = qrand() % vectors.size();
                QString sa=vectors[randomValue].back();
                vectors[randomValue].pop_back();
                if(vectors[randomValue].size()==0){
                    QVector<QString> temp=vectors[vectors.size()-1];
                    vectors[randomValue]=temp;
                    vectors.pop_back();
                }
                button[17+i] = new Newbutton(sa);
                  button[17+i]->closedstring="X";
                layout0.addWidget(button[17+i],3,i);
                buttongroup.addButton(button[17+i],17+i) ;
            }

            for(int i=0;i<6;i++){
                int randomValue = qrand() % vectors.size();
                QString sa=vectors[randomValue].back();
                vectors[randomValue].pop_back();
                if(vectors[randomValue].size()==0){
                    QVector<QString> temp=vectors[vectors.size()-1];
                    vectors[randomValue]=temp;
                    vectors.pop_back();
                }
                button[23+i] = new Newbutton(sa);
                  button[23+i]->closedstring="X";
                layout0.addWidget(button[23+i],4,i);
                buttongroup.addButton(button[23+i],23+i) ;
            }
                 window.setLayout(&(layout0));




}

//this slot is to make all buttons text 'X
void FindDialog::besiktas()
 {
    // we set the 2. and 4. label 0
    labels[1]->setText("0");
    labels[3]->setText("0");
     button[4]->ispressed=false;
    //make the all buttons 'X'
    for(int i=5;i<29;i++){

        QString temp=button[i]->text();
        button[i]->setText(button[i]->closedstring);
        button[i]->closedstring=temp;
    }
    //clean the all clener and control vectors and the reset button unpressed to take the click
clener.clear();
control.clear();
button[4]->ispressed=false;

//this bool variable is to determine if the all buttons is 'X'
isitX=true;
}
//this is to show the main window
void FindDialog::ismet(){
    window.show();

}
//this slot is the main slot to take and process the clicked button
void FindDialog::showinfo(int a)
 {
    //we first look if tje isitX  is true or not bucause once we press the reset button the interval like 3000ms should pass then the user can press the button so we restrict
    if(isitX||a==4){
        //if the window that will open after the user complete the table is open it will be closed
    if(windows.isEnabled()){
        windows.close();
    }
    // if the first timer is active then user click the reset button we stop the first timer
    if(controltimer->isActive()){
        controltimer->stop();
    }
    //is the user click the reset button then this if will be in process
    if(a==4&&!(lacasadapapel)&&button[a]->text()!=""){
        // first I set isitX false and set the 2. and 4. labes 0 and the other buttons closedstrings 'X'
        isitX=false;
        labels[1]->setText("0");
        labels[3]->setText("0");
        for(int i=5;i<29;i++){
            button[i]->setText(button[i]->hard);
             button[i]->closedstring="X";
        }

        // we determine a pairs to mix some buttons

         int bir=0 ;
         int iki=0 ;
       for(int i=0;i<=41;i++){
        bir = (qrand() % 24)+5;
         iki = (qrand() % 24)+5;
        while(bir==iki){
             bir = (qrand() % 24)+5;
              iki = (qrand() % 24)+5;
        }
        //then swap the buttons
        QString temptext=button[bir]->text();
        QString hardtemp=button[bir]->hard;
        button[bir]->setText(button[iki]->text());
        button[bir]->hard=button[iki]->hard;
        button[iki]->setText(temptext);
        button[iki]->hard=hardtemp;

         }



       if(!button[4]->ispressed){
               button[4]->ispressed=true;
           m_myLongTimer = new QTimer(this);
           m_myLongTimer->setInterval(9000);
           m_myLongTimer->setSingleShot(true);
           connect(m_myLongTimer, SIGNAL(timeout()), SLOT(besiktas()));
           m_myLongTimer->start();
       }else if(m_myLongTimer->isActive()){
            m_myLongTimer->setInterval(9000);
              m_myLongTimer->start();


       }

    }
    //if the user click a button rather than reset and the button's texy is not empty and there is no condition like the user wins the game this will be activated
    else if(a>=5&&!(lacasadapapel)&&button[a]->text()!=""&&!isitwin){

            QString temp=button[a]->closedstring;
           if(temp!=""&&control.size()==0){
            button[a]->closedstring=button[a]->text();
            button[a]->setText(temp);
            control.push_back(temp);
            }
          else if(temp!=""&&control.size()==1){
                // I increse the fourth label
              int tempno=labels[3]->text().toInt()+1;
                QString qstr = QString::number(tempno);
                labels[3]->setText(qstr);
                button[a]->closedstring=button[a]->text();
                button[a]->setText(temp);
                control.push_back(temp);
             if(control[0]==control[1]){
                 // I increse the second label
                 int tempno=labels[1]->text().toInt()+1;
                   QString qstr = QString::number(tempno);
                   labels[1]->setText(qstr);
                   //after the process ends the program will continue in makeempty slot
              QTimer::singleShot(1000, this, SLOT(makeempty()));

             }
              else if(control[0]!=control[1]){
               //if the openned buttons are not pairs then we continue in  theendofthedream slot to convert them old versions
               QTimer::singleShot(1000, this, SLOT(theendofthedream()));

             }

         }

      }
    }

}
//makes the openned buttons old versions
void FindDialog::theendofthedream()
 {
    QString temp2=button[clener[0]]->closedstring;
    button[clener[0]]->closedstring=button[clener[0]]->text();
    button[clener[0]]->setText(temp2);

    QString temp3=button[clener[1]]->closedstring;
    button[clener[1]]->closedstring=button[clener[1]]->text();
    button[clener[1]]->setText(temp3);
    clener.clear();
    control.clear();

    lacasadapapel=false;

}


//this slot is designed to take and push the ıd to clener vector.To make sure I set clse the second window here.
void FindDialog::al(int a)
 {
    if(isitX){
    if(windows.isEnabled()){
        windows.close();
    }
    if(a>=4&&!(lacasadapapel)&&clener.size()<2&&button[a]->text()!=""){
          clener.push_back(a);


    }
    if(clener.size()>2){
         lacasadapapel=true;
    }
    else if(a!=4){
        button[4]->ispressed=false;
    }
    }
}

//if the user find the pairs this make them empty

void FindDialog::makeempty()
 {

    button[clener[0]]->setText("");
    button[clener[1]]->setText("");
    clener.clear();
    control.clear();
    lacasadapapel=false;
         bool ctr=true;
    for(int i=5;i<29;i++){
        QString a=button[i]->text();
        if(a!=""){
            ctr=false;
        }
    }
    if(ctr){
    ismetveirelia=true;
    }
    if(ismetveirelia){
    run();
    ismetveirelia=false;
    }

}
