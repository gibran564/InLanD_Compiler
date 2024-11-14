/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *inputLabel;
    QTextEdit *inputTextEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *clearButton;
    QPushButton *analyzeButton;
    QPushButton *exitButton;
    QTabWidget *resultsTab;
    QWidget *tokensTab;
    QVBoxLayout *tokensLayout;
    QTableWidget *resultTable;
    QWidget *errorsTab;
    QVBoxLayout *errorsLayout;
    QPlainTextEdit *errorTextEdit;
    QWidget *syntaxTab;
    QVBoxLayout *syntaxLayout;
    QPlainTextEdit *syntaxTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1200, 800);
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto Mono")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        inputLabel = new QLabel(centralwidget);
        inputLabel->setObjectName("inputLabel");

        mainLayout->addWidget(inputLabel);

        inputTextEdit = new QTextEdit(centralwidget);
        inputTextEdit->setObjectName("inputTextEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputTextEdit->sizePolicy().hasHeightForWidth());
        inputTextEdit->setSizePolicy(sizePolicy);

        mainLayout->addWidget(inputTextEdit);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");

        buttonLayout->addWidget(openButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");

        buttonLayout->addWidget(clearButton);

        analyzeButton = new QPushButton(centralwidget);
        analyzeButton->setObjectName("analyzeButton");

        buttonLayout->addWidget(analyzeButton);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");

        buttonLayout->addWidget(exitButton);


        mainLayout->addLayout(buttonLayout);

        resultsTab = new QTabWidget(centralwidget);
        resultsTab->setObjectName("resultsTab");
        sizePolicy.setHeightForWidth(resultsTab->sizePolicy().hasHeightForWidth());
        resultsTab->setSizePolicy(sizePolicy);
        tokensTab = new QWidget();
        tokensTab->setObjectName("tokensTab");
        tokensLayout = new QVBoxLayout(tokensTab);
        tokensLayout->setObjectName("tokensLayout");
        resultTable = new QTableWidget(tokensTab);
        resultTable->setObjectName("resultTable");
        resultTable->setColumnCount(2);
        sizePolicy.setHeightForWidth(resultTable->sizePolicy().hasHeightForWidth());
        resultTable->setSizePolicy(sizePolicy);

        tokensLayout->addWidget(resultTable);

        resultsTab->addTab(tokensTab, QString());
        errorsTab = new QWidget();
        errorsTab->setObjectName("errorsTab");
        errorsLayout = new QVBoxLayout(errorsTab);
        errorsLayout->setObjectName("errorsLayout");
        errorTextEdit = new QPlainTextEdit(errorsTab);
        errorTextEdit->setObjectName("errorTextEdit");
        errorTextEdit->setReadOnly(true);
        sizePolicy.setHeightForWidth(errorTextEdit->sizePolicy().hasHeightForWidth());
        errorTextEdit->setSizePolicy(sizePolicy);

        errorsLayout->addWidget(errorTextEdit);

        resultsTab->addTab(errorsTab, QString());
        syntaxTab = new QWidget();
        syntaxTab->setObjectName("syntaxTab");
        syntaxLayout = new QVBoxLayout(syntaxTab);
        syntaxLayout->setObjectName("syntaxLayout");
        syntaxTextEdit = new QPlainTextEdit(syntaxTab);
        syntaxTextEdit->setObjectName("syntaxTextEdit");
        syntaxTextEdit->setReadOnly(true);
        sizePolicy.setHeightForWidth(syntaxTextEdit->sizePolicy().hasHeightForWidth());
        syntaxTextEdit->setSizePolicy(sizePolicy);

        syntaxLayout->addWidget(syntaxTextEdit);

        resultsTab->addTab(syntaxTab, QString());

        mainLayout->addWidget(resultsTab);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "InLanD - An\303\241lisis L\303\251xico y Sint\303\241ctico", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"    QMainWindow {\n"
"        background-color: #2E3440;\n"
"    }\n"
"    QLabel, QTableWidget, QPlainTextEdit, QTextEdit, QPushButton {\n"
"        color: #D8DEE9;\n"
"        font-family: 'Roboto Mono';\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #4C566A;\n"
"        border: 1px solid #4C566A;\n"
"        border-radius: 5px;\n"
"        padding: 8px;\n"
"        min-width: 80px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #5E81AC;\n"
"    }\n"
"    QTabWidget::pane {\n"
"        border: 1px solid #4C566A;\n"
"        padding: 5px;\n"
"    }\n"
"    QTabWidget::tab-bar {\n"
"        alignment: center;\n"
"    }\n"
"    QTabBar::tab {\n"
"        background: #3B4252;\n"
"        color: #D8DEE9;\n"
"        padding: 8px;\n"
"        margin: 2px;\n"
"    }\n"
"    QTabBar::tab:selected {\n"
"        background: #4C566A;\n"
"        border-bottom: 2px solid #88C0D0;\n"
"    }\n"
"    QHeaderView::section {\n"
"        background-color: #4C566A;\n"
"        color: #D"
                        "8DEE9;\n"
"        padding: 4px;\n"
"        border: none;\n"
"    }\n"
"   ", nullptr));
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Texto de Entrada:", nullptr));
        inputLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #88C0D0; font-weight: bold;", nullptr));
        inputTextEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"        background-color: #3B4252;\n"
"        color: #D8DEE9;\n"
"        border-radius: 5px;\n"
"        padding: 10px;\n"
"       ", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Limpiar", nullptr));
        analyzeButton->setText(QCoreApplication::translate("MainWindow", "Analizar", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        resultsTab->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #D8DEE9; background-color: #3B4252; border-radius: 5px;", nullptr));
        resultTable->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #3B4252; color: #D8DEE9; border-radius: 5px; padding: 5px;", nullptr));
        resultsTab->setTabText(resultsTab->indexOf(tokensTab), QCoreApplication::translate("MainWindow", "Tokens", nullptr));
        errorTextEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #3B4252; color: #D8DEE9; border-radius: 5px; padding: 10px;", nullptr));
        resultsTab->setTabText(resultsTab->indexOf(errorsTab), QCoreApplication::translate("MainWindow", "Errores", nullptr));
        syntaxTextEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #3B4252; color: #D8DEE9; border-radius: 5px; padding: 10px;", nullptr));
        resultsTab->setTabText(resultsTab->indexOf(syntaxTab), QCoreApplication::translate("MainWindow", "Sintaxis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
