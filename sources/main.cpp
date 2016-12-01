/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <QApplication>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTranslator>

#include "mainwindow.h"
#include "datasingleton.h"

void printHelpMessage()
{
    qDebug()<<"EasyPaint - simple graphics painting program\n"
              "Usage: easypaint [options] [filename]\n\n"
              "Options:\n"
              "\t-h, --help\t\tshow this help message and exit\n"
              "\t-v, --version\t\tshow program's version number and exit";
}

void printVersion()
{
    qDebug()<<"0.1.0";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("EasyPaint");
    a.setApplicationVersion("0.1.0");

    QStringList args = a.arguments();

    QRegExp rxArgHelp("--help");
    QRegExp rxArgH("-h");
    QRegExp rxArgVersion("--version");
    QRegExp rxArgV("-v");

    bool isHelp(false), isVer(false);
    QStringList filePaths;

    for(int i(1); i < args.size(); ++i)
    {
        if (rxArgHelp.indexIn(args.at(i)) != -1  ||
                rxArgH.indexIn(args.at(i)) != -1)
        {
            isHelp = true;
        }
        else if (rxArgVersion.indexIn(args.at(i)) != -1  ||
                 rxArgV.indexIn(args.at(i)) != -1)
        {
            isVer = true;
        }
        else
        {
            if(QFile::exists(args.at(i)))
            {
                filePaths.append(args.at(i));
            }
            else
            {
                qDebug()<<QString("File %1 not found").arg(args.at(i));
            }
        }

    }

    if(isHelp)
    {
        printHelpMessage();
        return 0;
    }
    else if(isVer)
    {
        printVersion();
        return 0;
    }

    QTranslator appTranslator;
    QString translationsPath("/usr/share/easypaint/translations/");
    QString appLanguage = DataSingleton::Instance()->getAppLanguage();
    if(appLanguage == "system")
    {
        appTranslator.load(translationsPath + "easypaint_" + QLocale::system().name());
    }
    else
    {
        appTranslator.load(translationsPath + appLanguage);
    }
    a.installTranslator(&appTranslator);

    MainWindow w(filePaths);
    w.show();

    return a.exec();
}
