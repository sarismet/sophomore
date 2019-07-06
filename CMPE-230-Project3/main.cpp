#include <QApplication>
#include<QTimer>

#include "finddialog.h"


int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     FindDialog *dialog = new FindDialog();
     dialog->ismet();

     return app.exec();
}
