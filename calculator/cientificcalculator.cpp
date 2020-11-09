#include "cientificcalculator.h"
#include "ui_cientific_calculator.h"

CientificCalculator::CientificCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CientificCalculator)
{
    // Create the UI (Display)
    ui->setupUi(this);
    qDebug() << "CALCULATOR INITIATED";
}
