
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    // Load QSS style sheet
    QString executablePath = QCoreApplication::applicationDirPath();
    QString qssFilePath = executablePath + "/myStyles.qss";
    QFile styleFile(qssFilePath);
    if (!styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed to open QSS file: " << styleFile.errorString();
        return -1;
    }
    QString style = QLatin1String(styleFile.readAll());
    styleFile.close();

    // Set the application's style sheet
    app.setStyleSheet(style);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("MovieandFood");
    mainWindow.show();
    return app.exec();
}