#ifndef CIENTIFICCALCULATOR_H
#define CIENTIFICCALCULATOR_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class CientificCalculator; }
QT_END_NAMESPACE

class CientificCalculator : public QMainWindow
{
    Q_OBJECT

public:
     CientificCalculator(QWidget *parent = 0);

private:
    Ui::CientificCalculator *ui;

private slots:

signals:

};

#endif // CIENTIFICCALCULATOR_H
