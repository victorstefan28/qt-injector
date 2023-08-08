#include "FileBrowser.h"
#include <QFileDialog>

FileBrowser::FileBrowser(QObject* parent) : QObject(parent)
{
}

QString FileBrowser::browseFilePath()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "", tr("All Files (*)"));
    if (!filePath.isEmpty())
        emit filePathSelected(filePath);

    return filePath;
}
