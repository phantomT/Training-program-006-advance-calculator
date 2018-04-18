#include "Calculator.h"

Calculator::Calculator()
{
}

bool Calculator::construct()
{
    m_ui = CalculatorUI::newInstance();
    if(m_ui != NULL)
    {
        m_ui->setCalculator(&m_cal);
    }
    return (m_ui != NULL);
}

Calculator* Calculator::newInstance()
{
    Calculator *ret = new Calculator();
    if((ret == NULL) || (!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void Calculator::show()
{
    m_ui->show();
}

Calculator::~Calculator()
{
    delete m_ui;
}
