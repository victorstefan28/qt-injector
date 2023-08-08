#pragma once

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QtWidgets/QMainWindow>
#include <QSharedPointer>
#include "ui_QTLoader.h"
#include "FileBrowser.h"
#include "FileBrowserWidget.h"

class QTLoader : public QMainWindow
{
    Q_OBJECT

public:
    QTLoader(QWidget *parent = nullptr);
    ~QTLoader();

private slots:
    void onLoginButtonClicked();
    void onInjectButtonClicked();
    void onFilePathSelected(const QString& filePath);

private:
    QSharedPointer<QLabel> usernameLabel;
    QSharedPointer<QLineEdit> usernameLineEdit;
    QSharedPointer<QLabel> passwordLabel;
    QSharedPointer<QLineEdit> passwordLineEdit;
    QSharedPointer<QPushButton> loginButton;
    QSharedPointer<QLineEdit> injectTextEdit;
    QSharedPointer<QPushButton> injectButton;
    QSharedPointer<QWidget> loginWidget;
    QSharedPointer<QWidget> injectWidget;
    FileBrowser fileBrowser;
    QSharedPointer<FileBrowserWidget> fileBrowserWidget;
};

#define InjectButtonStyle "QPushButton { background-color: #4CAF50; color: white; border: 2px solid #4CAF50; padding: 8px 16px; border-radius: 4px; width: 30%; position: absolute; }" \
            "QPushButton:hover { background-color: #45a049; }"\
            "QPushButton:pressed { background-color: #367d39; }"\
                "QPushButton:disabled {background-color: grey;}"