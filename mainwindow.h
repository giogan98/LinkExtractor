#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void processCSV( QString str_fileName, QString str_toSearch );
    QStringList processLine( QString str_line, QString str_toSearch );
    void processVector( QVector<QStringList> vec_temp, QString str_toFind );
};
#endif // MAINWINDOW_H
