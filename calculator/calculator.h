#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "CalculatorUI.h"
#include "CalculatorDec.h"

class Calculator
{
private:
    CalculatorUI *m_ui;
    CalculatorDec m_cal;

    Calculator();
    bool construct();
public:
    static Calculator* newInstance();
    void show();
    ~Calculator();

};

#endif // CALCULATOR_H
