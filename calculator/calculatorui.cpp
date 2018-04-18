#include "CalculatorUI.h"

CalculatorUI::CalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{
    m_cal = NULL;
}

CalculatorUI* CalculatorUI::newInstance()
{
    CalculatorUI *ret = new CalculatorUI();
    if(NULL == ret || !ret->Construct())
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

CalculatorUI::~CalculatorUI()
{
}

void CalculatorUI::show()
{
    QWidget::show();
    setFixedSize(width(), height());
}

bool CalculatorUI::Construct()
{
    bool ret = true;
    m_edit = new QLineEdit(this);
    if(m_edit != NULL)
    {
        m_edit->move(10, 10);
        m_edit->resize(240, 30);
        m_edit->setReadOnly(true);
    }
    else
    {
        ret = false;
    }

    const char *buttontext[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C"
    };
    for(int i = 0; (i < 4) && ret; i++)
    {
        for(int j = 0; (j < 5) && ret; j++)
        {
            m_buttons[5*i + j] = new QPushButton(this);
            if(m_buttons[5*i + j] != NULL)
            {
                m_buttons[5*i + j]->move(10 + (10 + 40)*j, 50 + (10 + 40)*i);
                m_buttons[5*i + j]->resize(40, 40);
                m_buttons[5*i + j]->setText(buttontext[5*i + j]);
                connect(m_buttons[5*i + j], SIGNAL(clicked()), this, SLOT(onCalculate()));
            }
            else
            {
                ret = false;
            }
        }
    }
    return ret;
}

void CalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

ICalculator* CalculatorUI::getCalculator()
{
    return m_cal;
}

void CalculatorUI::onCalculate()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());

    if( button != NULL )
    {
        QString buttontext = button->text();

        if( buttontext == "<-" )
        {
            QString text = m_edit->text();

            if( text.length() > 0 )
            {
                text.remove(text.length()-1, 1);
                m_edit->setText(text);
            }
        }
        else if( buttontext == "C" )
        {
            m_edit->setText("");
        }
        else if( buttontext == "=" )
        {
            if( m_cal != NULL )
            {
                m_cal->expression(m_edit->text());
                m_edit->setText(m_cal->result());
            }
        }
        else
        {
            m_edit->setText(m_edit->text() + buttontext);
        }
    }
}
