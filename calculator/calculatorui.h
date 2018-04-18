#ifndef CALCULATORUI_H
#define CALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "ICalculator.h"

class CalculatorUI : public QWidget
{
    Q_OBJECT
public:
    static CalculatorUI* newInstance();
    ~CalculatorUI();
    void show();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
private:
    CalculatorUI();
    bool Construct();

private slots:
    void onCalculate();
private:
    QLineEdit *m_edit;
    QPushButton *m_buttons[20];
    ICalculator *m_cal;
};

#endif // CALCULATORUI_H
