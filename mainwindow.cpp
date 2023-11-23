#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize timer
    timer = new QTimer(this);
    timer->setInterval(0); // 1 second
    connect(timer, SIGNAL(timeout()), this, SLOT(onIdleTimerTimeout()));

    // connect buttons to slots
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(ui->btn_pause, SIGNAL(clicked()), this, SLOT(onPauseButtonClicked()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartButtonClicked()
{
    qDebug() << "Start button clicked";
    ui->progressBar->setValue(0);
    ui->le_output->clear();

    // read input value
    int inputVal = ui->le_input->text().toInt();
    if (inputVal == 0) {
        decimalPlaces = 0;
    } else if (inputVal > 0) {
        decimalPlaces = inputVal;
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a positive integer or zero.");
        return;
    }

    QString outputString = QString::number(M_PI, 'f', decimalPlaces);
    ui->le_output->setText(outputString);

    timer->start();
}

void MainWindow::onPauseButtonClicked()
{
    qDebug() << "Pause button clicked";
    timer->stop();
}


void MainWindow::onStopButtonClicked()
{
    qDebug() << "Stop button clicked";
    timer->stop();
    ui->progressBar->setValue(0);
    ui->le_output->clear();
}


void MainWindow::onIdleTimerTimeout()
{
    static int count = 0;
    qDebug() << "Timer has timed out";
    count++;
    ui->le_output->append("Timer has timed out.");
    ui->progressBar->setValue(count);
    if (count < 100 && timer->isActive()) {
        timer->start(1000);
    } else {
        timer->stop();
        ui->le_output->append("Calculation completed.");
    }
}

