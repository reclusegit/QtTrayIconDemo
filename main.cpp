#include <QtGui/QApplication>
#include <QTranslator>
#include <QTextCodec>

#include "trayicondemo.h"

int main(int argc, char *argv[])
{
    // 让QMessageBox可用使用中文按钮
    QTranslator oTranslator;
    oTranslator.load(":/qt_zh_CN.qm");
    QApplication app(argc, argv);
    app.installTranslator(&oTranslator);

    // 让QT程序可以使用中文
    // 获取系统编码
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    TrayIconDemo w;
    w.show();
    
    return app.exec();
}
