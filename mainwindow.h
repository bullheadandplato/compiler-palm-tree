#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "syntaxhighlighter.h"

#include <QMainWindow>
#include <QPushButton>
#include"LexicalAnalyzer/LexAn.h"
#include "Parser/TableStack.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addWidgetsToolBar();

private slots:
    void on_plainTextEdit_textChanged();
    void openFileButtonClicked();


    void on_pushButton_2_clicked();

    void on_viewButton_clicked();

    void on_pushButton_3_clicked();

    void on_parseButton_clicked();

private:
    Ui::MainWindow *ui;
    SyntaxHighlighter *syntaxHigh;
    QPushButton *openFileButton;
    QPushButton *aboutButton;
    LexAn       analyzer;
    TableStack  parser;
    bool        isInParseMode;

    void populateTableView(std::vector<std::string> temp, std::string attr);
    void populateSets();
};

#endif // MAINWINDOW_H
