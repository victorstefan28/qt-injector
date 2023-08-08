#include "qtloader.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include "DllInjectionService.h"
#include <QTextBlock>



QTLoader::QTLoader(QWidget* parent)
    : QMainWindow(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    if (db.isValid()) {
        // The driver was loaded successfully.
    }
    else {
        // Failed to load the driver.
        qDebug() << "Failed to load database driver.";
    }
    /// connecting to a postgre sql-> to do
    usernameLabel = QSharedPointer<QLabel>(new QLabel("Username:"));
    usernameLineEdit = QSharedPointer<QLineEdit>(new QLineEdit());

    passwordLabel = QSharedPointer<QLabel>(new QLabel("Password:"));
    passwordLineEdit = QSharedPointer<QLineEdit>(new QLineEdit());
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = QSharedPointer<QPushButton>(new QPushButton("Login"));
    connect(loginButton.data(), &QPushButton::clicked, this, &QTLoader::onLoginButtonClicked);
    connect(&fileBrowser, &FileBrowser::filePathSelected, this, &QTLoader::onFilePathSelected);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(usernameLabel.data());
    layout->addWidget(usernameLineEdit.data());
    layout->addWidget(passwordLabel.data());
    layout->addWidget(passwordLineEdit.data());
    layout->addWidget(loginButton.data());

    loginWidget = QSharedPointer<QWidget>(new QWidget);
    loginWidget->setLayout(layout);
    setCentralWidget(loginWidget.data());

    setWindowTitle("Login Example");
}

void QTLoader::onLoginButtonClicked()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    
    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Login Error", "Username and password cannot be empty.");
        return;
    }

    if (username == "user" && password == "password")
    {
        //Injection layout-> path browser and process name
        QVBoxLayout* injectLayout = new QVBoxLayout;
        QLabel* processNameWidget = new QLabel("Input the process name");
        QLabel* loginDetails = new QLabel("Logged in as: " + username);
        
        injectLayout->addWidget(loginDetails);
        fileBrowserWidget = QSharedPointer<FileBrowserWidget>(new FileBrowserWidget);
        injectLayout->addWidget(fileBrowserWidget.data());
        injectLayout->addWidget(processNameWidget);
        injectTextEdit = QSharedPointer<QLineEdit>(new QLineEdit());
        
        injectLayout->addWidget(injectTextEdit.data());
        
        injectButton = QSharedPointer<QPushButton>(new QPushButton("Inject"));
        injectButton->setStyleSheet(InjectButtonStyle);
        QScreen* screen = QGuiApplication::primaryScreen();
        
        injectLayout->addWidget(injectButton.data());
        connect(injectButton.data(), &QPushButton::clicked, this, &QTLoader::onInjectButtonClicked);

        injectWidget = QSharedPointer<QWidget>(new QWidget);
        injectWidget->setLayout(injectLayout);
        setCentralWidget(injectWidget.data());


        setWindowTitle("Injection Interface");
    }
    else
    {
        QMessageBox::critical(this, "Login Error", "Invalid username or password.");
    }
}

void QTLoader::onInjectButtonClicked()
{
    injectButton->hide();

    QString injectText = injectTextEdit->text();
    std::string dllPath = fileBrowserWidget->getSelectedFilePath().toStdString();
   
    
    DllInjectionService& injector = DllInjectionService::getInstance(dllPath.c_str());
    DWORD pid = injector.GetProcessIdByName(injectTextEdit->text().toStdWString());
    qDebug() << dllPath.c_str() << ' '<<pid;
    if (injector.Inject(pid))
    {
        // DLL injection successful
        QMessageBox::information(this, "Injection", "Injected successfully " + injectText);
    }
    else
    {
        // DLL injection failed
        QMessageBox::critical(this, "Injection", "Injection failed " + injectText);
    }

    
    
}
void QTLoader::onFilePathSelected(const QString& filePath)
{
    injectTextEdit->setText(filePath); // Display the selected file path in the text edit
}

QTLoader::~QTLoader()
{
    
}
