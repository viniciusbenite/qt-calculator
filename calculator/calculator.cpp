#include "calculator.h"
#include "ui_calculator.h"

#include <math.h>

double calcValue = 0.0;

// Booleans to store triggers to math op's
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;
bool backSpaceTrigger = false;

// flag to reset display or continue to make operations on the result
bool displayFlag = false;

// Memory vars
double storedValue = 0.0;

//   Calculator mode
//   0 -> normal
//   1 -> scifi
int mode = 0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    // Create the UI (Display)
    ui->setupUi(this);
    qDebug() << "CALCULATOR INITIATED";

    if (mode == 0)
    {
        ui->btnLog->setVisible(0);
        ui->btnLog10->setVisible(0);
        ui->btnPow->setVisible(0);
        ui->btnFactorial->setVisible(0);
    }

    // The default value of display: 0.0
    ui->display->setText(QString::number(calcValue));

    QPushButton *numButtons[10]; // Numbers 0 to 9
    for (int i = 0; i < 10; i++) {
        QString btnName = "btn" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName); // Cast to QPushButton

        // When the btn is released, the slot function NumPressed() is called
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    // Operation signals
    connect(ui->btnSum, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnSubtraction, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnDivide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnMultiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnSquare, SIGNAL(released()), this, SLOT(PowerOperation()));
    connect(ui->btnSquareRoot, SIGNAL(released()), this, SLOT(SqrtOperation()));
    connect(ui->btnInverse, SIGNAL(released()), this, SLOT(Inverse()));
    connect(ui->btnLog, SIGNAL(released()), this, SLOT(LogOperation()));
    connect(ui->btnLog10, SIGNAL(released()), this, SLOT(LnOperation()));
    connect(ui->btnFactorial, SIGNAL(released()), this, SLOT(FactorialOperation(calcValue)));

    connect(ui->btnEquals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->btnChangeSignal, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->btnErase, SIGNAL(released()), this, SLOT(ClearSign()));

    connect(ui->btnAddMemory, SIGNAL(released()), this, SLOT(AddToMemory()));
    connect(ui->btnRemoveMemory, SIGNAL(released()), this, SLOT(RemoveFromMemory()));
    connect(ui->btnRetrieveMemory, SIGNAL(released()), this, SLOT(DisplayMemory()));

    connect(ui->btnBackspace, SIGNAL(released()), this, SLOT(Backspace()));

    connect(ui->btnDot, SIGNAL(released()), this, SLOT(NumPressed()));

    if (mode == 0)
    {
        connect(ui->btnMode, SIGNAL(released()), this, SLOT(on_btnMode_clicked(1)));
        mode = 1;
    }
    else
    {
        connect(ui->btnMode, SIGNAL(released()), this, SLOT(on_btnMode_clicked(0)));
        mode = 0;
    }


}

// Deconstructor
Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_btnMode_clicked(int value)
{
    qDebug() << "BTN MODE CLICKED";
    ui->btnLog->setVisible(value);
    ui->btnLog10->setVisible(value);
    ui->btnPow->setVisible(value);
    ui->btnFactorial->setVisible(value);
}

void Calculator::NumPressed()
{
    if (displayFlag)
    {
        ui->display->clear();
        displayFlag = false;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();
    QString displayValue = ui->display->text();

    qDebug() << "Number pressed" << btnValue;
    if ((displayValue.toDouble() == 0.0))
    {
        ui->display->setText(btnValue);
    }
    else if (QString::compare(btnValue, ".", Qt::CaseInsensitive) == 0)
    {
        qDebug() << "IT WAS A DOT" << btnValue;
        QString newValue = displayValue + btnValue;
        ui->display->setText(newValue);
    }
    else
    {
        QString newValue = displayValue + btnValue;
        double doubleNewValue = newValue.toDouble();
        ui->display->setText(QString::number(doubleNewValue, 'g', 16));
    }
    if (QString::compare(displayValue, ".", Qt::CaseInsensitive) == 0)
    {
        qDebug() << "DISPLAY HAS A DOT" << displayValue;
        QString newValue = "0" + displayValue + btnValue;
        //double doubleNewValue = newValue.toDouble();
        ui->display->setText(newValue);
    }
}

void Calculator::Backspace()
{
    QString currentValue = ui->display->text();
    currentValue.chop(1); // remove last
    if (currentValue.length() == 0)
    {
        ui->display->setText("0");
    } else
    {
        ui->display->setText(currentValue);
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
    else if (QString::compare(btnValue, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    else if(QString::compare(btnValue, "x^y", Qt::CaseInsensitive) == 0)
    {
        powTrigger = true;
    }

    // After an operation, we can clear our display (new number)
    ui->display->setText(QString::number(calcValue) + " " + btnValue);;
}

void Calculator::EqualButton()
{
    double result = 0.0;

    QString currentvalue = ui->display->text();
    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();
    double doubleCurrentValue = currentvalue.toDouble();

    if (divTrigger || multiTrigger || addTrigger || subTrigger)
    {
        if (divTrigger)
        {
            result = calcValue / doubleCurrentValue;
        }
        else if (multiTrigger)
        {
            result = doubleCurrentValue * calcValue;
        }
        else if (addTrigger)
        {
            result = doubleCurrentValue + calcValue;
        }
        else if (subTrigger)
        {
            result = calcValue - doubleCurrentValue;
        }
        else if (powTrigger)
        {
            result = pow(calcValue, doubleCurrentValue);
        }
    }
    else
    {
        result = doubleCurrentValue;
    }

    ui->display->setText(QString::number(result));

    displayFlag = true;
}

void Calculator::ChangeNumberSign()
{
    QString currentDisplay = ui->display->text();
    double doubleCurrentDisplay = currentDisplay.toDouble();
    double doubleCurrentDisplaySign = (-1) * doubleCurrentDisplay;
    ui->display->setText(QString::number(doubleCurrentDisplaySign));
}

void Calculator::ClearSign()
{
    ui->display->clear();
    ui->display->setText(QString::number(0));
}

void Calculator::AddToMemory()
{
    QString currentValue = ui->display->text();
    storedValue = currentValue.toDouble();
}

void Calculator::RemoveFromMemory()
{
    storedValue = 0.0;
}

void Calculator::DisplayMemory()
{
    ui->display->setText(QString::number(storedValue));
}

void Calculator::PowerOperation()
{
    QString currentValue = ui->display->text();
    double result = currentValue.toDouble() * currentValue.toDouble();
    ui->display->setText(QString::number(result));

    displayFlag = true;
}

void Calculator::SqrtOperation()
{
    QString currentValue = ui->display->text();
    double result = sqrt(currentValue.toDouble());
    ui->display->setText(QString::number(result));

    displayFlag = true;
}

void Calculator::Inverse()
{
    QString currentValue = ui->display->text();
    double result = 1 / currentValue.toDouble();
    ui->display->setText(QString::number(result));

    displayFlag = true;
}

void Calculator::LogOperation()
{
    QString currentValue = ui->display->text();
    double result = log(currentValue.toDouble());
    ui->display->setText(QString::number(result));

    displayFlag = true;
}

void Calculator::LnOperation()
{
    QString currentValue = ui->display->text();
    double result = log10(currentValue.toDouble());
    ui->display->setText(QString::number(result));

    displayFlag = true;
}

double Calculator::FactorialOperation(double n)
{
    n = ui->display->text().toDouble();
    double result;

    if (n <= 1.0)
    {
        result = 1;
    }
    else
    {
        result = n * FactorialOperation(n - 1);
    }

    ui->display->setText(QString::number(result));
    displayFlag = true;

    return 0.0;
}

void Calculator::ChangeMode()
{
    qDebug() << "Mode changed to " << mode;
    if (mode == 0)
    {
        mode = 1;
    }
    else
    {
        mode = 0;
    }
}
