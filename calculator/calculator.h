#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

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
    void PowerOperation();
};
#endif // CALCULATOR_H
