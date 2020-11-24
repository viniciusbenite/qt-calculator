#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;

// Booleans to store triggers to math op's
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool backSpaceTrigger = false;

// flag to reset display or continue to make operations on the result
bool displayFlag = false;

// Memory vars
double storedValue = 0.0;

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

    // Operation signals
    connect(ui->btnSum, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnSubtraction, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnDivide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->btnMultiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->btnEquals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->btnChangeSignal, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->btnErase, SIGNAL(released()), this, SLOT(ClearSign()));

    connect(ui->btnAddMemory, SIGNAL(released()), this, SLOT(AddToMemory()));
    connect(ui->btnRemoveMemory, SIGNAL(released()), this, SLOT(RemoveFromMemory()));
    connect(ui->btnRetrieveMemory, SIGNAL(released()), this, SLOT(DisplayMemory()));

    connect(ui->btnBackspace, SIGNAL(released()), this, SLOT(Backspace()));

}

// Deconstructor
Calculator::~Calculator()
{
    delete ui;
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

    if ((displayValue.toDouble() == 0.0))
    {
        ui->display->setText(btnValue);
    } else
    {
        QString newValue = displayValue + btnValue;
        double doubleNewValue = newValue.toDouble();
        ui->display->setText(QString::number(doubleNewValue, 'g', 16));
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
    else
    {
        subTrigger = true;
    }

    // After an operation, we can clear our display (new number)
    ui->display->setText(QString::number(calcValue) + " " + btnValue);
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
