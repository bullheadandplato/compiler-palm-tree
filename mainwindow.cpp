#include "mainwindow.h"

#include "syntaxhighlighter.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    syntaxHigh=new SyntaxHighlighter(ui->plainTextEdit->document());
    //add button to main toolbar
    this->addWidgetsToolBar();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    syntaxHigh->highlightBlock(ui->plainTextEdit->toPlainText());
}
void MainWindow::addWidgetsToolBar(){
     this->openFileButton=new QPushButton("Open File");
    this->aboutButton=new QPushButton("About");
    ui->mainToolBar->addWidget(openFileButton);
    ui->mainToolBar->addWidget(aboutButton);
    //add action listeners to buttons
    connect(openFileButton,SIGNAL(clicked()),this,SLOT(openFileButtonClicked()));
}
void MainWindow::openFileButtonClicked(){
    //open file and set code editor text to it
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");

    if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text))
                ui->plainTextEdit->setPlainText(file.readAll());
        }
}
