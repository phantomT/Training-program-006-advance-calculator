#include "CalculatorDec.h"

CalculatorDec::CalculatorDec()
{
    m_exp = "";
    m_result = "";
}

CalculatorDec::~CalculatorDec()
{
}

bool CalculatorDec::expression(const QString & exp)
{
    bool ret = false;
    QQueue<QString> spExp = split(exp);
    QQueue<QString> postExp;

    m_exp = exp;
    if( transform(spExp, postExp) )
    {
        m_result = calculate(postExp);
        ret = (m_result != "Error");
    }
    else
    {
        m_result = "Error";
    }
    return ret;
}

QString CalculatorDec::expression()
{
    QString ret;

    return ret;
}

QString CalculatorDec::result()
{
    return m_result;
}

bool CalculatorDec::isDigitOrDot(QChar c)
{
    return (('0' <= c) && (c <= '9') )|| (c == '.');
}

bool CalculatorDec::isSymbol(QChar c)
{
    return isOperator(c) || ('(' == c) || (')' == c);
}

bool CalculatorDec::isSign(QChar c)
{
    return ('+' == c) || ('-' == c);
}

bool CalculatorDec::isNumber(QString s)
{
    bool ret = false;
    s.toDouble(&ret);
    return ret;
}

bool CalculatorDec::isOperator(QString s)
{
    return ("+" == s) || ("-" == s) || ("*" == s) || ("/" == s);
}

bool CalculatorDec::isLeft(QString s)
{
    return ("(" == s);
}

bool CalculatorDec::isRight(QString s)
{
    return (")" == s);
}

int CalculatorDec::priority(QString s)
{
    int ret = -1;
    if(s == "+" || s == "-")
    {
        ret = 1;
    }
    if(s == "*" || s == "/")
    {
        ret = 2;
    }
    return ret;
}

QQueue<QString> CalculatorDec::split(const QString& exp)
{
    QQueue<QString> ret;
    QString pre = "";
    QString num = "";
    for(int i=0; i<exp.length(); i++)
    {
        if(isDigitOrDot(exp[i]))
        {
            num += exp[i];
            pre = exp[i];
        }
        else if(isSymbol(exp[i]))
        {
            if(!num.isEmpty())
            {
                ret.enqueue(num);

                num.clear();
            }
            if(isSign(exp[i]) && ((pre == "") || (pre == "(") || isOperator(pre)))
            {
                num += exp[i];
            }
            else
            {
                ret.enqueue(exp[i]);
            }
            pre = exp[i];
        }
    }

    if(!num.isEmpty())
    {
        ret.enqueue(num);
    }
    return ret;
}

bool CalculatorDec::match(QQueue<QString>& exp)
{
    bool ret = true;
    int len = exp.length();
    QStack<QString> stack;

    for(int i=0; i<len; i++)
    {
        if( isLeft(exp[i]) )
        {
            stack.push(exp[i]);
        }
        else if( isRight(exp[i]) )
        {
            if( !stack.isEmpty() && isLeft(stack.top()) )
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
    }

    return ret && stack.isEmpty();
}

bool CalculatorDec::transform(QQueue<QString>& exp, QQueue<QString>& output)
{
    bool ret = match(exp);
    QStack<QString> stack;

    output.clear();
    while( ret && !exp.isEmpty() )
    {
        QString e = exp.dequeue();
        if( isNumber(e) )
        {
            output.enqueue(e);
        }
        else if( isOperator(e) )
        {
            while( !stack.isEmpty() && (priority(e) <= priority(stack.top())) )
            {
                output.enqueue(stack.pop());
            }

            stack.push(e);
        }
        else if( isLeft(e) )
        {
            stack.push(e);
        }
        else if( isRight(e) )
        {
            while( !stack.isEmpty() && !isLeft(stack.top()) )
            {
                output.enqueue(stack.pop());
            }
            if( !stack.isEmpty() )
            {
                stack.pop();
            }
        }
        else
        {
            ret = false;
        }
    }
    while( !stack.isEmpty() )
    {
        output.enqueue(stack.pop());
    }
    if( !ret )
    {
        output.clear();
    }

    return ret;
}


QString CalculatorDec::calculate(QString l, QString op, QString r)
{
    QString ret = "Error";

    if( isNumber(l) && isNumber(r) )
    {
        double lp = l.toDouble();
        double rp = r.toDouble();

        if( op == "+" )
        {
            ret.sprintf("%f", lp + rp);
        }
        else if( op == "-" )
        {
            ret.sprintf("%f", lp - rp);
        }
        else if( op == "*" )
        {
            ret.sprintf("%f", lp * rp);
        }
        else if( op == "/" )
        {
            const double P = 0.000000000000001;

            if( (-P < rp) && (rp < P) )
            {
                ret = "Error";
            }
            else
            {
                ret.sprintf("%f", lp / rp);
            }
        }
        else
        {
            ret = "Error";
        }
    }

    return ret;
}

QString CalculatorDec::calculate(QQueue<QString>& exp)
{
    QString ret = "Error";
    QStack<QString> stack;

    while( !exp.isEmpty() )
    {
        QString e = exp.dequeue();
        if( isNumber(e) )
        {
            stack.push(e);
        }
        else if( isOperator(e) )
        {
            QString rp = !stack.isEmpty() ? stack.pop() : "";
            QString lp = !stack.isEmpty() ? stack.pop() : "";
            QString result = calculate(lp, e, rp);

            if( result != "Error" )
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if( exp.isEmpty() && (stack.size() == 1) && isNumber(stack.top()) )
    {
        ret = stack.pop();
    }

    return ret;
}
