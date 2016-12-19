#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "syntaxhighlighter.h"

#include <QMainWindow>
#include <QPushButton>

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


private:
    Ui::MainWindow *ui;
    SyntaxHighlighter *syntaxHigh;
    QPushButton *openFileButton;
    QPushButton *aboutButton;
};

#endif // MAINWINDOW_H
