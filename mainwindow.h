#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void number_pressed();
    void operator_pressed();
    void equals_pressed();
    void clear_pressed();

private:
    Ui::MainWindow *ui;
    double firstOperand;
    QString pendingOperator;
    bool waitingForSecondOperand;
};
#endif // MAINWINDOW_H
