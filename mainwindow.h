#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "syntaxhighlighter.h"

#include <QMainWindow>
#include <QPushButton>
#include"LexicalAnalyzer/LexAn.h"

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

private:
    Ui::MainWindow *ui;
    SyntaxHighlighter *syntaxHigh;
    QPushButton *openFileButton;
    QPushButton *aboutButton;
    LexAn       analyzer;
    void populateTableView(std::vector<std::string> temp);
};

#endif // MAINWINDOW_H
