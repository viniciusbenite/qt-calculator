#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class ScientificCalculator; }
QT_END_NAMESPACE

class ScientificCalculator : public QMainWindow
{
    Q_OBJECT

public:
     ScientificCalculator(QWidget *parent = 0);
     ~ScientificCalculator();

private:
    Ui::ScientificCalculator *ui;

private slots:

signals:

};

#endif // SCIENTIFICCALCULATOR_H
