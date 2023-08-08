#include "FileBrowserWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

FileBrowserWidget::FileBrowserWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    filePathTextEdit = QSharedPointer<QLineEdit>(new QLineEdit());
    filePathTextEdit->setReadOnly(true);
    layout->addWidget(filePathTextEdit.data());

    QPushButton* browseButton = new QPushButton("Browse");
    layout->addWidget(browseButton);

    
    connect(browseButton, &QPushButton::clicked, this, &FileBrowserWidget::onBrowseButtonClicked);

   
    connect(&fileBrowser, &FileBrowser::filePathSelected, this, &FileBrowserWidget::onFilePathSelected);

    setLayout(layout);
}

void FileBrowserWidget::onBrowseButtonClicked()
{
    
    fileBrowser.browseFilePath();
}

void FileBrowserWidget::onFilePathSelected(const QString& filePath)
{

    filePathTextEdit->setText(filePath);
}

QString FileBrowserWidget::getSelectedFilePath() const
{
    return filePathTextEdit->text();
}