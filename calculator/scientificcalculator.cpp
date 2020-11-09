#include "scientificcalculator.h"
#include "ui_cientific_calculator.h"

double defaultValue = 0.0;

ScientificCalculator::ScientificCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScientificCalculator)
{
    // Create the UI (Display)
    ui->setupUi(this);
    qDebug() << "SCIENTIFIC CALCULATOR INITIATED";

    ui->display->setText(QString::number(defaultValue));
}

ScientificCalculator::~ScientificCalculator()
{
    delete ui;
}
