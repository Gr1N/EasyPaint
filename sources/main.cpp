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
#include <QRegularExpression>

#include "mainwindow.h"
#include "datasingleton.h"

void printHelpMessage() {
    qDebug() << "EasyPaint - simple graphics painting program\n"
            "Usage: easypaint [options] [filename]\n\n"
            "Options:\n"
            "\t-h, --help\t\tshow this help message and exit\n"
            "\t-v, --version\t\tshow program's version number and exit";
}

void printVersion() {
    qDebug() << "0.1.1";
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("EasyPaint");
    a.setApplicationVersion("0.1.1");

    QStringList args = a.arguments();

    QRegularExpression rxArgHelp("--help");
    QRegularExpression rxArgH("-h");
    QRegularExpression rxArgVersion("--version");
    QRegularExpression rxArgV("-v");

    bool isHelp(false), isVer(false);
    QStringList filePaths;

    for (int i = 1; i < args.size(); i++) {
        QString arg = args.at(i);
        QRegularExpressionMatch matchHelp = rxArgHelp.match(arg);
        QRegularExpressionMatch matchH = rxArgH.match(arg);
        QRegularExpressionMatch matchVersion = rxArgVersion.match(arg);
        QRegularExpressionMatch matchV = rxArgV.match(arg);
        if (matchHelp.hasMatch() || matchH.hasMatch()) {
            isHelp = true;
        }
        else if (matchVersion.hasMatch() || matchV.hasMatch()) {
            isVer = true;
        }
        else {
            if (QFile::exists(arg)) {
                filePaths.append(arg);
            }
            else {
                qDebug() << QString("File %1 not found").arg(arg);
            }
        }
    }

    if (isHelp) {
        printHelpMessage();
        return 0;
    }
    else if (isVer) {
        printVersion();
        return 0;
    }

    QTranslator appTranslator;
    QString translationsPath("/usr/share/easypaint/translations/");
    QString appLanguage = DataSingleton::Instance()->getAppLanguage();
    if (appLanguage == "system") {
        appTranslator.load(translationsPath + "easypaint_" + QLocale::system().name());
    }
    else {
        appTranslator.load(translationsPath + appLanguage);
    }
    a.installTranslator(&appTranslator);

    MainWindow w(filePaths);
    w.show();

    return a.exec();
}
