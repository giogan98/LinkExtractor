#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include <QString>


class CSVprocessor
{
public:
    CSVprocessor();
    QString processCSV(const QString &str_fileName, QString &str_toSearch);
    QStringList processLine(const QString &str_line, const QString &str_toSearch);
    bool processVector(const QVector<QStringList> &vec_temp, QString &str_toFind);
};

#endif // CSVPROCESSOR_H
