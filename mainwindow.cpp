#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QPushButton*> numberButtons =
    {
        ui->pushButton_2, ui->pushButton_7, ui->pushButton_18, ui->pushButton_19, ui->pushButton_8, ui->pushButton_14, ui->pushButton_15, ui->pushButton_9, ui->pushButton_10, ui->pushButton_11
    };

    for (auto button : numberButtons)
    {
        connect(button, &QPushButton::clicked, this, &MainWindow::number_pressed);
    }

    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_sub, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_multi, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_modulo, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_decimal, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_sqrt, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::clear_pressed);
    connect(ui->pushButton_squared, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_eq, &QPushButton::clicked, this, &MainWindow::equals_pressed);
    connect(ui->pushButton_percent, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_pi, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_lftPar, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(ui->pushButton_rghtPar, &QPushButton::clicked, this, &MainWindow::operator_pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::number_pressed()
{
    QPushButton *pressedButton = qobject_cast<QPushButton*>(sender());
    QString numberValue = pressedButton->text();

    if (waitingForSecondOperand) {
        ui->display->clear();
        waitingForSecondOperand = false;
    }

    ui->display->setText(ui->display->text() + numberValue);
}

void MainWindow::operator_pressed()
{
    QPushButton *pressedButton = qobject_cast<QPushButton*>(sender());
    firstOperand = ui->display->text().toDouble();
    pendingOperator = pressedButton->text();
    waitingForSecondOperand = true;
}

void MainWindow::equals_pressed()
{
    double secondOperand = ui->display->text().toDouble();
    double result = 0.0;

    if (pendingOperator == "+") result = firstOperand + secondOperand;
    else if (pendingOperator == "-") result = firstOperand - secondOperand;
    else if (pendingOperator == "*") result = firstOperand * secondOperand;
    else if (pendingOperator == "/") {
        if (secondOperand != 0)
            result = firstOperand / secondOperand;
        else {
            ui->display->setText("Error");
            return;
        }
    }

    ui->display->setText(QString::number(result));
    waitingForSecondOperand = true;
}

void MainWindow::clear_pressed()
{
    ui->display->clear();
    firstOperand = 0;
    pendingOperator.clear();
    waitingForSecondOperand = false;
}

