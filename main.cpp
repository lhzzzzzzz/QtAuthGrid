#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <mysql.h>  // 添加MariaDB C连接器头文件

int main(int argc, char *argv[])
{
    // 初始化MySQL库
    if (mysql_library_init(0, nullptr, nullptr)) {
        // 初始化失败，但仍继续运行应用
        qWarning("无法初始化MySQL库！");
    }

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "firstDemo_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    
    int result = a.exec();
    
    // 清理MySQL库资源
    mysql_library_end();
    
    return result;
}
