#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QObject>
#include <QString>

class FileBrowser : public QObject
{
    Q_OBJECT

public:
    explicit FileBrowser(QObject* parent = nullptr);

public slots:
    QString browseFilePath();

signals:
    void filePathSelected(const QString& filePath);
};

#endif // FILEBROWSER_H
