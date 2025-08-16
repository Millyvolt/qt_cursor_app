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
        QStringList searchPaths = {
            "mainwindow.ui",                                    // Current directory
            QDir::currentPath() + "/mainwindow.ui",            // Current working directory
            QCoreApplication::applicationDirPath() + "/mainwindow.ui",  // Executable directory
            QCoreApplication::applicationDirPath() + "/bin/mainwindow.ui", // Build output directory
            "../mainwindow.ui",                                // Parent directory
            "../../mainwindow.ui"                              // Grandparent directory
        };
        
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
                        m_secondaryButton = uiWidget->findChild<QPushButton*>("secondaryButton");
                        m_destructiveButton = uiWidget->findChild<QPushButton*>("destructiveButton");
                        
                        qDebug() << "UI loaded successfully from:" << path;
                        qDebug() << "Primary button found:" << (m_primaryButton != nullptr);
                        qDebug() << "Secondary button found:" << (m_secondaryButton != nullptr);
                        qDebug() << "Destructive button found:" << (m_destructiveButton != nullptr);
                        
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
        
        QLabel *descriptionLabel = new QLabel("This is the primary action tab. Click the button below to perform the main action of your application.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_primaryButton = new QPushButton("Primary Action", tab);
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_primaryButton);
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
        
        QLabel *descriptionLabel = new QLabel("This is the secondary action tab. This button has a different styling with a light background.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_secondaryButton = new QPushButton("Secondary Action", tab);
        m_secondaryButton->setObjectName("secondaryButton");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_secondaryButton);
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
        
        QLabel *descriptionLabel = new QLabel("This is the destructive action tab. Be careful with this button as it will ask for confirmation before proceeding.", tab);
        descriptionLabel->setAlignment(Qt::AlignCenter);
        descriptionLabel->setWordWrap(true);
        descriptionLabel->setStyleSheet("QLabel { color: #86868b; font-size: 15px; margin: 10px; }");
        
        m_destructiveButton = new QPushButton("Destructive Action", tab);
        m_destructiveButton->setObjectName("destructiveButton");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(m_destructiveButton);
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
        if (m_secondaryButton) {
            connect(m_secondaryButton, &QPushButton::clicked, this, &MainWindow::onSecondaryButtonClicked);
            qDebug() << "Secondary button signal connected";
        } else {
            qWarning() << "Secondary button not found for signal connection";
        }
        if (m_destructiveButton) {
            connect(m_destructiveButton, &QPushButton::clicked, this, &MainWindow::onDestructiveButtonClicked);
            qDebug() << "Destructive button signal connected";
        } else {
            qWarning() << "Destructive button not found for signal connection";
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

private:
    QPushButton *m_primaryButton = nullptr;
    QPushButton *m_secondaryButton = nullptr;
    QPushButton *m_destructiveButton = nullptr;
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
