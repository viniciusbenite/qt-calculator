#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

// Constructor. *parent = 0 means that this widget has no parent.
public:
    Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

// Slots are executed when a signal is submited
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void ClearSign();
    void AddToMemory();
    void RemoveFromMemory();
    void DisplayMemory();
    void Backspace();
    void ChangeMode();
    void PowerOperation();
    void SqrtOperation();
    void Inverse();
    void LogOperation();
    void LnOperation();
    double FactorialOperation(double);
    void on_btnMode_clicked(int);
};
#endif // CALCULATOR_H
