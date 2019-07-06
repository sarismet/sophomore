This project has resemblance to the game in http://mypuzzle.org/find-the-pair web site, however if you are here to see the QT code then there are some notes below
In order to run this code you can use QT creator.
Important Notes:
in this project there are two window. The first window is always open and
the second one will be open if the user succeeds.
there is 9000m time for user to see the table in the beginning if the user
click the reset button in 9000ms the time will be stop and the related
slot will be in process
if the user click reset button the time again 9000ms for user to see the
table if the user click reset in 9000ms the interval will be again 9000 as
if I reset it.
The user click two button there is a process to make two button "" or
concert them their old version so in this interval the lacasadapapel
variable will be true and after process it will be false
this is design to prohibit the user give any click in this interval.
you can close the second window by clicking the reset button in the first
window or by clicking the button that shows you how many tries did you do
in the socond windows itself
Classes FindDialog Newbutton
I write Newbutton to have some extra bool QString variables and all
QPushButton properties.
bool ispressed: I designed to understand if a button is pressed like if
the button 4 pressed then this will be true and if the user presses again
reset then the timer will be set to 9000 ms again.
QString closedstring:it is like the second text of a button.if I create
button with letter A then the closedstring X and they will be changed with
each other
QStrings hard:this is like ID's of button. I used it after the user click
reset I set all buttons's text their Ä±d which is hard and then change
with an other button.
