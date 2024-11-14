#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analyzer.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), analyzer(std::make_unique<Analyzer>())
{
    ui->setupUi(this);
    ui->resultTable->setColumnCount(2);
    QStringList headers;
    headers << "Lexema" << "Gramema";
    ui->resultTable->setHorizontalHeaderLabels(headers);
    ui->resultTable->horizontalHeader()->setStretchLastSection(true);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->errorTextEdit->setReadOnly(true);
    ui->syntaxTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_analyzeButton_clicked()
{
    QString inputText = ui->inputTextEdit->toPlainText().trimmed();

    if (inputText.isEmpty()) {
        QMessageBox::information(this, tr("Información"), tr("La entrada está vacía. Por favor, ingresa texto para analizar."));
        return;
    }

    std::string input = inputText.toStdString();

    std::vector<Token> tokens = analyzer->analyzeString(input);

    displayResults(tokens);

    std::vector<std::string> errors = analyzer->getErrors();

    if (errors.empty()) {
        ui->errorTextEdit->setPlainText("No se encontraron errores.");
    } else {
        displayErrors(errors);
    }

    exportResultsToTxt(tokens, errors);
}

void MainWindow::displayResults(const std::vector<Token> &tokens)
{
    ui->resultTable->setRowCount(tokens.size());
    ui->resultTable->setColumnCount(2);

    for (size_t row = 0; row < tokens.size(); ++row) {
        const auto &token = tokens[row];
        ui->resultTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(token.lexema)));
        ui->resultTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(token.gramema)));
    }
}

void MainWindow::displayErrors(const std::vector<std::string> &errors)
{
    ui->errorTextEdit->clear();
    int errorNumber = 1;
    for (const auto &error : errors) {
        QString formattedError = QString::number(errorNumber++) + ". " + QString::fromStdString(error);
        ui->errorTextEdit->appendPlainText(formattedError);
    }
}

void MainWindow::exportResultsToTxt(const std::vector<Token> &tokens, const std::vector<std::string> &errors)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar Resultados"), "", tr("Archivos de Texto (*.txt);;Todos los Archivos (*)"));
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".txt", Qt::CaseInsensitive)) {
        fileName += ".txt";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo guardar el archivo. Verifica los permisos o el espacio disponible."));
        return;
    }

    QTextStream out(&file);

    out << "Resultados del Análisis:\n";
    out << "======================\n";
    for (const auto &token : tokens) {
        out << "Lexema: " << QString::fromStdString(token.lexema) << "\t Gramema: " << QString::fromStdString(token.gramema) << "\n";
    }

    out << "\nErrores Encontrados:\n";
    out << "===================\n";
    if (errors.empty()) {
        out << "No se encontraron errores.\n";
    } else {
        int errorNumber = 1;
        for (const auto &error : errors) {
            out << errorNumber++ << ". " << QString::fromStdString(error) << "\n";
        }
    }

    file.close();

    QMessageBox::information(this, tr("Éxito"), tr("Resultados exportados correctamente."));
}

void MainWindow::on_openButton_clicked()
{
    // Filtrar para abrir solo archivos .ild
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "", tr("Archivos InLanD (*.ild);;Todos los Archivos (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.exists()) {
        QMessageBox::warning(this, tr("Error"), tr("El archivo seleccionado no existe."));
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo abrir el archivo. Verifica los permisos o el estado del archivo."));
        return;
    }

    QTextStream in(&file);
    ui->inputTextEdit->setPlainText(in.readAll());
    file.close();
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar Archivo"), "", tr("Archivos InLanD (*.ild);;Todos los Archivos (*)"));
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".ild", Qt::CaseInsensitive)) {
        fileName += ".ild";
    }

    QFile file(fileName);
    if (file.exists()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirmar Sobrescritura"), tr("El archivo ya existe. ¿Deseas sobrescribirlo?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes) {
            return;
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo guardar el archivo. Verifica los permisos o el espacio disponible."));
        return;
    }

    QTextStream out(&file);
    out << ui->inputTextEdit->toPlainText();
    file.close();

    QMessageBox::information(this, tr("Éxito"), tr("Archivo guardado correctamente."));
}

void MainWindow::on_clearButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirmar Limpieza"), tr("¿Estás seguro de que deseas limpiar todas las áreas?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->inputTextEdit->clear();
        ui->resultTable->setRowCount(0);
        ui->errorTextEdit->clear();
        ui->syntaxTextEdit->clear();
    }
}

void MainWindow::on_exitButton_clicked()
{
    if (!ui->inputTextEdit->toPlainText().isEmpty() || ui->resultTable->rowCount() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirmar Salida"), tr("Hay datos sin guardar. ¿Deseas salir de todas formas?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes) {
            return;
        }
    }
    QApplication::quit();
}
