#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include "FileBrowser.h"
#include <QLineEdit>

class QLineEdit;

class FileBrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowserWidget(QWidget* parent = nullptr);
    QString getSelectedFilePath() const; 

private slots:
    void onBrowseButtonClicked();
    void onFilePathSelected(const QString& filePath);

private:
    FileBrowser fileBrowser;
    QSharedPointer<QLineEdit> filePathTextEdit;
};

#endif // FILEBROWSERWIDGET_H
