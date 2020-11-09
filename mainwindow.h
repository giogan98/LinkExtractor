#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CSVprocessor/csvprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private slots:
    void on_pbn_go_clicked(void);

private:
    Ui::MainWindow *ui;
    CSVprocessor csvProc;
};
#endif // MAINWINDOW_H
