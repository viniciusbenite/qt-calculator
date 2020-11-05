#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;

// Booleans to store triggers to math op's
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    // Create the UI (Display)
    ui->setupUi(this);

    // The default value of display: 0.0
    ui->display->setText(QString::number(calcValue));

    QPushButton *numButtons[10]; // Numbers 0 to 9

    for (int i = 0; i < 10; i++) {
        QString btnName = "btn" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName); // Cast to QPushButton

        // When the btn is released, the slot function NumPressed() is called
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
}

// Deconstructor
Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();
    QString displayValue = ui->display->text();

    if ((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0))
    {
        ui->display->setText(btnValue);
    } else
    {
        QString newValue = displayValue + btnValue;
        double doubleNewValue = newValue.toDouble();
        ui->display->setText(QString::number(doubleNewValue, 'g', 16));
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multiTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString currentValue = ui->display->text();
    calcValue = currentValue.toDouble();

    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();

    if (QString::compare(btnValue, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(btnValue, "*", Qt::CaseInsensitive) == 0)
    {
        multiTrigger = true;
    }
    else if (QString::compare(btnValue, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }

    // After an operation, we can clear our display (new number)
    ui->display->setText("");
}

void Calculator::EqualButton()
{
    double result = 0.0;

    QString currentvalue = ui->display->text();
    double doubleCurrentValue = currentvalue.toDouble();

    if (divTrigger || multiTrigger || addTrigger || subTrigger)
    {
        if (divTrigger)
        {
            result = calcValue / doubleCurrentValue;
        } else if (multiTrigger)
        {
            result = doubleCurrentValue * calcValue;
        } else if (addTrigger)
        {
            result = doubleCurrentValue + calcValue;
        } else
        {
            result = calcValue - doubleCurrentValue;
        }
    }

    ui->display->setText(QString::number(result));
}
