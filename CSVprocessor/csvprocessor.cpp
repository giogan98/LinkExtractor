#include "csvprocessor.h"

#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>

CSVprocessor::CSVprocessor()
{

}
//------------------------------------------------------------------------------
QString CSVprocessor::processCSV(const QString &str_fileName,
                                 QString &str_toSearch)
{
    QFile inputFile(str_fileName);
    QVector<QStringList> vec_lines;
    bool bSucc = false;

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString str_line;
        QStringList strl_temp;
        while (!in.atEnd())
        {
            str_line = in.readLine();
            strl_temp = processLine(str_line, str_toSearch);

            if(strl_temp.size() > 0)
            {
                vec_lines.append(strl_temp);
            }
        }

        inputFile.close();

        if (vec_lines.length() > 0)
        {
            bSucc = processVector(vec_lines, str_toSearch);
        }
    }

    if (!bSucc) str_toSearch = "";
    return str_toSearch;
}
//------------------------------------------------------------------------------
QStringList CSVprocessor::processLine(const QString &str_line,
                                      const QString &str_toSearch)
{
    QStringList strl_temp;

    if (str_line.indexOf (str_toSearch, 0, Qt::CaseSensitivity::CaseInsensitive) > -1)
    {
        strl_temp.append(str_line.split(","));
    }

    return strl_temp;
}
//------------------------------------------------------------------------------
bool CSVprocessor::processVector(const QVector<QStringList> &vec_temp,
                                 QString &str_toFind)
{
    str_toFind = ".\\" + str_toFind + "_results.txt";
    QFile file(str_toFind) ;
    QTextStream stream(&file);
    bool bSucc = false;

    if (!file.open(QFile::Append | QFile::Text)) return false;

    stream<<"SESSION:" + QDate::currentDate().toString() + "\n";
    for (int ii = 0; ii < vec_temp.length(); ii++)
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

    if( vec_temp.length() > 0) bSucc = true;
    return bSucc;
}
//------------------------------------------------------------------------------
