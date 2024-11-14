// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "token.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Analyzer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_analyzeButton_clicked();
    void on_openButton_clicked();
    void on_saveButton_clicked();
    void on_clearButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Analyzer> analyzer;

    void displayResults(const std::vector<Token> &tokens);
    void displayErrors(const std::vector<std::string> &errors);
     void exportResultsToTxt(const std::vector<Token> &tokens, const std::vector<std::string> &errors);
};

#endif
