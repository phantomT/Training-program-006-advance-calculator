#ifndef CALCULATORDEC_H
#define CALCULATORDEC_H

#include <QString>
#include <QQueue>
#include <QStack>
#include "ICalculator.h"

class CalculatorDec : public ICalculator
{
public:
    CalculatorDec();
    ~CalculatorDec();
    bool expression(const QString & exp);
    QString expression();
    QString result();
private:
    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);
    QQueue<QString> split(const QString& exp);
    bool match(QQueue<QString>& exp);
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);
    QString calculate(QQueue<QString>& exp);
    QString calculate(QString l, QString op, QString r);
private:
    QString m_exp;
    QString m_result;
};

#endif // CALCULATORDEC_H
