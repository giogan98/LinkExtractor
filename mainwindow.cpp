#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDate>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

//FORMATTING:
//0)Informazioni cronologiche,
//1)Cognome e nome docente,
//2)Titolo Insegnamento,
//3)Codice Insegnamento,
//4)Dipartimento di afferenza Insegnamento,
//5)Data lezione live,
//6)Ora inizio lezione live,
//7)Ora fine lezione live,
//8)Collegamento sessione live  Microsoft Teams

//we need 2, 5 and 8

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//-----------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------
void MainWindow::on_pbn_go_clicked()
{
    QString str_csvName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                       "/home",
                                                       tr("CSV file (*.csv)"));
    QString str_toSearch = ui->lne_search->text();

    if (str_csvName != "" && str_toSearch != "")
    {
        csvProc.processCSV(str_csvName, str_toSearch);

        if (str_toSearch.length() > 0)
        {
            QMessageBox::information(this, "INFO", "Operation was successful");
            QDesktopServices::openUrl(QUrl("file:" + str_toSearch));
        }
        else
        {
            QMessageBox::warning(this, "Error"," Unable to create/open results txt file ");
        }
    }
}
//-----------------------------------------------------------------------
