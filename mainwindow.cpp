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

//HINT TO OPEN LINK IN PREDEFINED APPLICATION:
//@QDesktopServices::openUrl(QUrl("file:///home/fstigre/fileName.pdf"));@

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

    if ( str_csvName != "" && str_toSearch != "" )
    {
        processCSV( str_csvName, str_toSearch );
    }
}
//-----------------------------------------------------------------------
void MainWindow::processCSV( QString str_fileName , QString str_toSearch )
{
    QFile inputFile( str_fileName );
    QVector<QStringList> vec_lines;
    if ( inputFile.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &inputFile );

        while ( !in.atEnd() )
        {
            QString str_line = in.readLine();
            QStringList strl_temp =  processLine( str_line, str_toSearch );

            if( strl_temp.length() > 0 )
            {
                vec_lines.append( strl_temp );
            }
        }

        inputFile.close();

        if ( vec_lines.length() > 0 )
        {
            processVector( vec_lines, str_toSearch );
        }
    }
}
//-----------------------------------------------------------------------
QStringList MainWindow::processLine( QString str_line , QString str_toSearch )
{
    QStringList strl_temp;

    if ( str_line.indexOf ( str_toSearch, 0, Qt::CaseSensitivity::CaseInsensitive ) > -1 )
    {
        strl_temp.append( str_line.split( "," ) );
    }

    return strl_temp;
}
//-----------------------------------------------------------------------
void MainWindow::processVector ( QVector<QStringList> vec_temp, QString str_toFind )
{
    QString str_fileName = ".\\" + str_toFind + "_results.txt";
    QFile file( str_fileName) ;
    QTextStream stream( &file );

    if (!file.open( QFile::Append | QFile::Text ))
    {
        QMessageBox::warning(this, "Error"," Unable to create/open results txt file ");
        return;
    }

    //    stream<<"*********************SESSION START*********************\n";
    stream<<"SESSION:" + QDate::currentDate().toString() + "\n";
    for ( int ii = 0; ii < vec_temp.length(); ii++ )
    {
        QString str_out;
        str_out.append(vec_temp[ii][2]);
        str_out.append(" ; ");
        str_out.append(vec_temp[ii][5]);
        str_out.append(" ; ");
        str_out.append(vec_temp[ii][8]);
        str_out.append("\n");
        stream<<str_out;
    }

    file.close();

    if( vec_temp.length() > 0)
    {
        QMessageBox::information( this, "INFO", "Operation was successful" );
        QDesktopServices::openUrl( QUrl( "file:"+str_fileName ) );
    }

}
