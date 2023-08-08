#include "QTLoader.h"
#include <QtWidgets/QApplication>

#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile("Fibrary.qss"); 
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        styleFile.close();
    }
    else
    {
        qDebug() << "Failed to load style.qss";
    }
    QTLoader w;
    w.show();
    return a.exec();
}
