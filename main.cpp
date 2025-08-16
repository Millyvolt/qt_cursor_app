#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QFrame>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Load UI from designer file
        if (!loadUI()) {
            qWarning() << "Failed to load UI file, creating fallback UI";
            createFallbackUI();
        }
        
        // Load additional stylesheet
        loadStylesheet();
        
        // Connect button signals
        connectSignals();
        
        // Set window properties
        setWindowTitle("iOS Style Qt Application");
        setFixedSize(500, 700);
    }

private:
    bool loadUI()
    {
        // Add more comprehensive path detection
        QStringList searchPaths = {
            "mainwindow.ui",                                    // Current directory
            QDir::currentPath() + "/mainwindow.ui",            // Current working directory
            QCoreApplication::applicationDirPath() + "/mainwindow.ui",  // Executable directory
            QCoreApplication::applicationDirPath() + "/bin/mainwindow.ui", // Build output directory
            QCoreApplication::applicationDirPath() + "/../mainwindow.ui", // Parent of executable directory
            QCoreApplication::applicationDirPath() + "/../../mainwindow.ui", // Grandparent of executable directory
            "../mainwindow.ui",                                // Parent directory
            "../../mainwindow.ui",                             // Grandparent directory
            "../../../mainwindow.ui",                          // Great-grandparent directory
            QDir::homePath() + "/Projects/qt_two_buttons_app/mainwindow.ui", // Specific project path
            "C:/Users/vovik/Projects/qt_two_buttons_app/mainwindow.ui"  // Absolute path
        };
        
        qDebug() << "Current working directory:" << QDir::currentPath();
        qDebug() << "Application directory:" << QCoreApplication::applicationDirPath();
        qDebug() << "Home directory:" << QDir::homePath();
        
        for (const QString &path : searchPaths) {
            qDebug() << "Trying to load UI from:" << path;
            QFile uiFile(path);
            
            if (uiFile.exists()) {
                qDebug() << "UI file found at:" << path;
                if (uiFile.open(QFile::ReadOnly)) {
                    QUiLoader loader;
                    QWidget *uiWidget = loader.load(&uiFile, this);
                    uiFile.close();
                    
                    if (uiWidget) {
                        // Set the loaded UI as the main widget
                        QVBoxLayout *layout = new QVBoxLayout(this);
                        layout->addWidget(uiWidget);
                        layout->setContentsMargins(0, 0, 0, 0);
                        setLayout(layout);
                        
                        // Store references to UI elements
                        m_primaryButton = uiWidget->findChild<QPushButton*>("primaryButton");
                        m_primaryButton2 = uiWidget->findChild<QPushButton*>("primaryButton2");
                        m_primaryButton3 = uiWidget->findChild<QPushButton*>("primaryButton3");
                        m_secondaryButton = uiWidget->findChild<QPushButton*>("secondaryButton");
                        m_secondaryButton2 = uiWidget->findChild<QPushButton*>("secondaryButton2");
                        m_secondaryButton3 = uiWidget->findChild<QPushButton*>("secondaryButton3");
                        m_destructiveButton = uiWidget->findChild<QPushButton*>("destructiveButton");
                        m_destructiveButton2 = uiWidget->findChild<QPushButton*>("destructiveButton2");
                        m_destructiveButton3 = uiWidget->findChild<QPushButton*>("destructiveButton3");
                        
                        qDebug() << "UI loaded successfully from:" << path;
                        qDebug() << "Primary button found:" << (m_primaryButton != nullptr);
                        qDebug() << "Primary button 2 found:" << (m_primaryButton2 != nullptr);
                        qDebug() << "Primary button 3 found:" << (m_primaryButton3 != nullptr);
                        qDebug() << "Secondary button found:" << (m_secondaryButton != nullptr);
                        qDebug() << "Secondary button 2 found:" << (m_secondaryButton2 != nullptr);
                        qDebug() << "Secondary button 3 found:" << (m_secondaryButton3 != nullptr);
                        qDebug() << "Destructive button found:" << (m_destructiveButton != nullptr);
                        qDebug() << "Destructive button 2 found:" << (m_destructiveButton2 != nullptr);
                        qDebug() << "Destructive button 3 found:" << (m_destructiveButton3 != nullptr);
                        
                        return true;
                    } else {
                        qWarning() << "Failed to load UI from:" << path << "- loader failed";
                    }
                } else {
                    qWarning() << "Could not open UI file:" << path << "-" << uiFile.errorString();
                }
            } else {
                qDebug() << "UI file not found at:" << path;
            }
        }
        
        qWarning() << "Could not load mainwindow.ui from any location";
        return false;
    }
    
    void createFallbackUI()
    {
        qDebug() << "Creating fallback UI programmatically";
        
        // Create main layout
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(16);
        
        // Create header card
        QFrame *headerCard = new QFrame(this);
        headerCard->setObjectName("headerCard");
        QVBoxLayout *headerLayout = new QVBoxLayout(headerCard);
        
        QLabel *titleLabel = new QLabel("Settings", this);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);
        
        QLabel *subtitleLabel = new QLabel("Navigate through different sections", this);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignCenter);
        subtitleLabel->setWordWrap(true);
        
        headerLayout->addWidget(titleLabel);
        headerLayout->addWidget(subtitleLabel);
        
        // Create tab widget
        QTabWidget *tabWidget = new QTabWidget(this);
        
        // Create three tabs with different content
        createPrimaryTab(tabWidget);
        createSecondaryTab(tabWidget);
        createDestructiveTab(tabWidget);
        
        // Add widgets to main layout
        mainLayout->addWidget(headerCard);
        mainLayout->addWidget(tabWidget);
        
        setLayout(mainLayout);
    }
    
    void createPrimaryTab(QTabWidget *tabWidget)
    {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);
        
        // Create content card
        QFrame *contentCard = new QFrame(tab);
        contentCard->setObjectName("card");
        QVBoxLayout *contentLayout = new QVBoxLayout(contentCard);
        
        QLabel *descriptionLabel = new QLabel("This is the primary action tab. Click the buttons below to perform different primary actions.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_primaryButton = new QPushButton("Primary Action", tab);
        m_primaryButton2 = new QPushButton("Primary Action 2", tab);
        m_primaryButton3 = new QPushButton("Primary Action 3", tab);
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_primaryButton);
        contentLayout->addWidget(m_primaryButton2);
        contentLayout->addWidget(m_primaryButton3);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        tabWidget->addTab(tab, "Primary");
    }
    
    void createSecondaryTab(QTabWidget *tabWidget)
    {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);
        
        // Create content card
        QFrame *contentCard = new QFrame(tab);
        contentCard->setObjectName("card");
        QVBoxLayout *contentLayout = new QVBoxLayout(contentCard);
        
        QLabel *descriptionLabel = new QLabel("This is the secondary action tab. These buttons have different styling with a light background.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_secondaryButton = new QPushButton("Secondary Action", tab);
        m_secondaryButton->setObjectName("secondaryButton");
        m_secondaryButton2 = new QPushButton("Secondary Action 2", tab);
        m_secondaryButton2->setObjectName("secondaryButton2");
        m_secondaryButton3 = new QPushButton("Secondary Action 3", tab);
        m_secondaryButton3->setObjectName("secondaryButton3");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_secondaryButton);
        contentLayout->addWidget(m_secondaryButton2);
        contentLayout->addWidget(m_secondaryButton3);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        tabWidget->addTab(tab, "Secondary");
    }
    
    void createDestructiveTab(QTabWidget *tabWidget)
    {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(16);
        
        // Create content card
        QFrame *contentCard = new QFrame(tab);
        contentCard->setObjectName("card");
        QVBoxLayout *contentLayout = new QVBoxLayout(contentCard);
        
        QLabel *descriptionLabel = new QLabel("This is the destructive action tab. Be careful with these buttons as they will ask for confirmation before proceeding.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_destructiveButton = new QPushButton("Destructive Action", tab);
        m_destructiveButton->setObjectName("destructiveButton");
        m_destructiveButton2 = new QPushButton("Destructive Action 2", tab);
        m_destructiveButton2->setObjectName("destructiveButton2");
        m_destructiveButton3 = new QPushButton("Destructive Action 3", tab);
        m_destructiveButton3->setObjectName("destructiveButton3");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_destructiveButton);
        contentLayout->addWidget(m_destructiveButton2);
        contentLayout->addWidget(m_destructiveButton3);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        tabWidget->addTab(tab, "Destructive");
    }
    
    void loadStylesheet()
    {
        QStringList searchPaths = {
            "styles.qss",                                    // Current directory
            QDir::currentPath() + "/styles.qss",            // Current working directory
            QCoreApplication::applicationDirPath() + "/styles.qss",  // Executable directory
            QCoreApplication::applicationDirPath() + "/bin/styles.qss", // Build output directory
            "../styles.qss",                                // Parent directory
            "../../styles.qss"                              // Grandparent directory
        };
        
        bool stylesheetLoaded = false;
        
        for (const QString &path : searchPaths) {
            QFile file(path);
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                QTextStream stream(&file);
                QString stylesheet = stream.readAll();
                setStyleSheet(stylesheet);
                file.close();
                qDebug() << "Stylesheet loaded successfully from:" << path;
                stylesheetLoaded = true;
                break;
            } else {
                qDebug() << "Could not open stylesheet from:" << path << "-" << file.errorString();
            }
        }
        
        if (!stylesheetLoaded) {
            qWarning() << "Could not load styles.qss from any location. Using fallback styles.";
            // Apply minimal fallback styles
            setStyleSheet(R"(
                QWidget {
                    background-color: #f2f2f7;
                    color: #1d1d1f;
                    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
                }
                QPushButton {
                    background-color: #007aff;
                    border: none;
                    border-radius: 12px;
                    color: white;
                    padding: 16px 24px;
                    margin: 8px;
                }
                QPushButton:hover {
                    background-color: #0056cc;
                }
            )");
        }
    }
    
    void connectSignals()
    {
        if (m_primaryButton) {
            connect(m_primaryButton, &QPushButton::clicked, this, &MainWindow::onPrimaryButtonClicked);
            qDebug() << "Primary button signal connected";
        } else {
            qWarning() << "Primary button not found for signal connection";
        }
        if (m_primaryButton2) {
            connect(m_primaryButton2, &QPushButton::clicked, this, &MainWindow::onPrimaryButton2Clicked);
            qDebug() << "Primary button 2 signal connected";
        } else {
            qWarning() << "Primary button 2 not found for signal connection";
        }
        if (m_primaryButton3) {
            connect(m_primaryButton3, &QPushButton::clicked, this, &MainWindow::onPrimaryButton3Clicked);
            qDebug() << "Primary button 3 signal connected";
        } else {
            qWarning() << "Primary button 3 not found for signal connection";
        }
        if (m_secondaryButton) {
            connect(m_secondaryButton, &QPushButton::clicked, this, &MainWindow::onSecondaryButtonClicked);
            qDebug() << "Secondary button signal connected";
        } else {
            qWarning() << "Secondary button not found for signal connection";
        }
        if (m_secondaryButton2) {
            connect(m_secondaryButton2, &QPushButton::clicked, this, &MainWindow::onSecondaryButton2Clicked);
            qDebug() << "Secondary button 2 signal connected";
        } else {
            qWarning() << "Secondary button 2 not found for signal connection";
        }
        if (m_secondaryButton3) {
            connect(m_secondaryButton3, &QPushButton::clicked, this, &MainWindow::onSecondaryButton3Clicked);
            qDebug() << "Secondary button 3 signal connected";
        } else {
            qWarning() << "Secondary button 3 not found for signal connection";
        }
        if (m_destructiveButton) {
            connect(m_destructiveButton, &QPushButton::clicked, this, &MainWindow::onDestructiveButtonClicked);
            qDebug() << "Destructive button signal connected";
        } else {
            qWarning() << "Destructive button not found for signal connection";
        }
        if (m_destructiveButton2) {
            connect(m_destructiveButton2, &QPushButton::clicked, this, &MainWindow::onDestructiveButton2Clicked);
            qDebug() << "Destructive button 2 signal connected";
        } else {
            qWarning() << "Destructive button 2 not found for signal connection";
        }
        if (m_destructiveButton3) {
            connect(m_destructiveButton3, &QPushButton::clicked, this, &MainWindow::onDestructiveButton3Clicked);
            qDebug() << "Destructive button 3 signal connected";
        } else {
            qWarning() << "Destructive button 3 not found for signal connection";
        }
    }

private slots:
    void onPrimaryButtonClicked()
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Primary Action");
        msgBox.setText("Primary action completed successfully!");
        msgBox.setInformativeText("This is the main action of your application.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onPrimaryButton2Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Primary Action 2");
        msgBox.setText("Primary action 2 completed successfully!");
        msgBox.setInformativeText("This is the second primary action of your application.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onPrimaryButton3Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Primary Action 3");
        msgBox.setText("Primary action 3 completed successfully!");
        msgBox.setInformativeText("This is the third primary action of your application.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onSecondaryButtonClicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("secondaryDialog");
        msgBox.setWindowTitle("Secondary Action");
        msgBox.setText("Secondary action completed!");
        msgBox.setInformativeText("This is a secondary action with different styling.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onSecondaryButton2Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("secondaryDialog2");
        msgBox.setWindowTitle("Secondary Action 2");
        msgBox.setText("Secondary action 2 completed!");
        msgBox.setInformativeText("This is the second secondary action with different styling.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onSecondaryButton3Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("secondaryDialog3");
        msgBox.setWindowTitle("Secondary Action 3");
        msgBox.setText("Secondary action 3 completed!");
        msgBox.setInformativeText("This is the third secondary action with different styling.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    
    void onDestructiveButtonClicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("destructiveDialog");
        msgBox.setWindowTitle("Destructive Action");
        msgBox.setText("Are you sure you want to perform this action?");
        msgBox.setInformativeText("This action cannot be undone.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        
        int result = msgBox.exec();
        if (result == QMessageBox::Yes) {
            QMessageBox::information(this, "Action Confirmed", "Destructive action has been performed.");
        }
    }
    
    void onDestructiveButton2Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("destructiveDialog2");
        msgBox.setWindowTitle("Destructive Action 2");
        msgBox.setText("Are you sure you want to perform this second destructive action?");
        msgBox.setInformativeText("This action cannot be undone and may have serious consequences.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        
        int result = msgBox.exec();
        if (result == QMessageBox::Yes) {
            QMessageBox::information(this, "Action Confirmed", "Second destructive action has been performed.");
        }
    }
    
    void onDestructiveButton3Clicked()
    {
        QMessageBox msgBox(this);
        msgBox.setObjectName("destructiveDialog3");
        msgBox.setWindowTitle("Destructive Action 3");
        msgBox.setText("Are you sure you want to perform this third destructive action?");
        msgBox.setInformativeText("This action cannot be undone and will permanently delete data.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        
        int result = msgBox.exec();
        if (result == QMessageBox::Yes) {
            QMessageBox::information(this, "Action Confirmed", "Third destructive action has been performed.");
        }
    }

private:
    QPushButton *m_primaryButton = nullptr;
    QPushButton *m_primaryButton2 = nullptr;
    QPushButton *m_primaryButton3 = nullptr;
    QPushButton *m_secondaryButton = nullptr;
    QPushButton *m_secondaryButton2 = nullptr;
    QPushButton *m_secondaryButton3 = nullptr;
    QPushButton *m_destructiveButton = nullptr;
    QPushButton *m_destructiveButton2 = nullptr;
    QPushButton *m_destructiveButton3 = nullptr;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application-wide style to Fusion for better cross-platform consistency
    app.setStyle(QStyleFactory::create("Fusion"));
    
    MainWindow window;
    window.show();
    
    return app.exec();
}

#include "main.moc"
