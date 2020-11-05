#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;

bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcValue));

    QPushButton *numButtons[10]; // 0 to 9

    for (int i = 0; i < 10; i++) {
        QString btnName = "btn" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName); // Cast to QPushButton

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
