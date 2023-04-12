// #include"tictactoe_class.h"
#include<iostream>
using std::cout;
#include<qapplication.h>
#include<qlabel.h>
#include<qpushbutton.h>
int main( int argc, char *argv[] )
{
  QApplication app( argc, argv );
  QLabel *label = new QLabel( &app," New! " );
  label->show();
  cout << app.exec();
  return 0;
}