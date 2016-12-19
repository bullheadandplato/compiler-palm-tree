#include "mainwindow.h"

#include "syntaxhighlighter.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <LexicalAnalyzer/LexAn.h>
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

void MainWindow::on_pushButton_2_clicked()
{
    // it is the analyze button.
    //create a file and write all the text from code editor in it
    QFile file("in.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out <<ui->plainTextEdit->toPlainText() << "\n";
        file.close();
        //start analyzing
        LexAn res;
        res.scanwords();
        //now get results
        QString tmp=QString::number(res.getTotalCharacterCount());
        ui->totalWordCountlbl->setText(tmp);
        tmp=QString::number(res.getNumberOfIdentifiers());
        ui->idenLbl->setText(tmp);
        tmp=QString::number(res.getNumberOfKeywords());
        ui->keywordLbl->setText(tmp);
        tmp=QString::number(res.getNumberOfOperators());
        ui->operLbl->setText(tmp);
        tmp=QString::number(res.getNumberOfOtherSymbols());
        ui->otherLbl->setText(tmp);
        tmp=QString::number(res.getNumberOfComments());
        ui->commLbl->setText(tmp);


}
