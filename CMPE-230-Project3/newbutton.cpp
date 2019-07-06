#include <QPushButton>
#include<newbutton.h>

//it is the constructor of the button class and I assign the value parent into hard.The parent variable determined by computer and the hard varianle is like button's ıd
Newbutton::Newbutton(QString parent) :
    QPushButton(parent)

{
hard=parent;

}
Newbutton::~Newbutton()
{

}
