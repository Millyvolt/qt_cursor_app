#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFont>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QTabWidget>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("iOS Style Qt Application");
        setFixedSize(500, 700);
        
        // Load stylesheet from external file
        loadStylesheet();
        
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

private:
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
        
        QPushButton *primaryButton = new QPushButton("Primary Action", tab);
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(primaryButton);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        connect(primaryButton, &QPushButton::clicked, this, &MainWindow::onPrimaryButtonClicked);
        
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
        
        QPushButton *secondaryButton = new QPushButton("Secondary Action", tab);
        secondaryButton->setObjectName("secondaryButton");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(secondaryButton);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        connect(secondaryButton, &QPushButton::clicked, this, &MainWindow::onSecondaryButtonClicked);
        
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
        
        QPushButton *destructiveButton = new QPushButton("Destructive Action", tab);
        destructiveButton->setObjectName("destructiveButton");
        
        contentLayout->addWidget(descriptionLabel);
        contentLayout->addWidget(destructiveButton);
        contentLayout->addStretch();
        
        layout->addWidget(contentCard);
        layout->addStretch();
        
        connect(destructiveButton, &QPushButton::clicked, this, &MainWindow::onDestructiveButtonClicked);
        
        tabWidget->addTab(tab, "Destructive");
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
