#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include<newbutton.h>
#include <QDialog>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVector>
#include <QApplication>


class FindDialog : public QDialog
{
    Q_OBJECT

 public:
    FindDialog(QWidget *parent = 0);
    void ismet();
    void firststart();
    void run();
    bool ctr=true;
    bool ismetveirelia=false;
    QWidget windows;
    QLabel *labels[4];
    QWidget       window ;
    QButtonGroup  buttongroup ;
    QTimer *m_myLongTimer;
     QTimer *m_myLongTimer2;
    QTimer *controltimer;
    bool isitX=false;
    QGridLayout   layout0 ;
    QGridLayout   layout1 ;
    Newbutton *button[45];
    Newbutton *kartus;
    QVector<int> clener;
    QVector<QString> control;
    bool lacasadapapel=false;
    bool isitwin=false;

private slots:
     void showinfo(int);
     void makeempty();
     void al(int a);
     void besiktas();
     void theendofthedream();
     void closeinfowindow();







};
#endif
