#include <QApplication>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator *cal = Calculator::newInstance();
    int ret = 0;
    if(cal != NULL)
    {
        cal->show();
        ret = a.exec();
        delete cal;
    }
    return ret;
}
