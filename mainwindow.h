#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer2;
    int decimalPlaces;

private slots:
    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();
    void onIdleTimerTimeout();
};

#endif // MAINWINDOW_H
