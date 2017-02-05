#include "mainwindow.h"

#include "syntaxhighlighter.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <LexicalAnalyzer/LexAn.h>
#include<vector>
#include<string>
#include <QStandardItem>

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
    // first check if code editor has text
    if(ui->plainTextEdit->toPlainText().length()<=0){
                QMessageBox::information(this,"No code to analyze","Pleaase include some code in code area to analyze.");
                return;
    }
    // it is the analyze button.
    //create a file and write all the text from code editor in it
    QFile file("in.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out <<ui->plainTextEdit->toPlainText() << "\n";
        file.close();
        //start analyzing
        analyzer.scanwords();
        //now get analyzerults
        QString tmp=QString::number(analyzer.getTotalCharacterCount());
        ui->totalWordCountlbl->setText(tmp);
        tmp=QString::number(analyzer.getNumberOfIdentifiers());
        ui->idenLbl->setText(tmp);
        tmp=QString::number(analyzer.getNumberOfKeywords());
        ui->keywordLbl->setText(tmp);
        tmp=QString::number(analyzer.getNumberOfOperators());
        ui->operLbl->setText(tmp);
        tmp=QString::number(analyzer.getNumberOfOtherSymbols());
        ui->otherLbl->setText(tmp);
        tmp=QString::number(analyzer.getNumberOfComments());
        ui->commLbl->setText(tmp);


}

void MainWindow::on_viewButton_clicked()
{
    //open the file
    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox messageBox;
        messageBox.setText("Cannot open file for reading");
        messageBox.setButtonText(QMessageBox::Ok,"Okay");
        messageBox.exec();
        return;
    }

    int choice=ui->comboBox->currentIndex();
    switch (choice) {
    case 0:{
        // I have to show identififers
        populateTableView(analyzer.getIdentifiers(),"identifier");

        break;
    }
      case 1:{
        populateTableView(analyzer.getKeywords(),"keyword");
        break;
    }
    case 2:{
        populateTableView(analyzer.getOperators(),"operator");
        break;
    }
    case 3:{
        populateTableView(analyzer.getComments(),"comment");
        break;
    }
    default:
        break;
    }
}
void MainWindow::populateTableView(std::vector<std::string> temp, std::__cxx11::string attr){
    QTableView *table=ui->tableView;

    QStandardItemModel *model = new QStandardItemModel(temp.size(),2,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Attribute")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));
    table->setModel(model);
    table->setColumnWidth(1,200);
    model->setColumnCount(2);
    model->setRowCount(temp.size());

    QString attrs;
    attrs=attrs.fromStdString(attr);

    for(std::size_t i=0;i<temp.size();i++){
        QString tmp;
        tmp=tmp.fromStdString(temp[i]);
        QStandardItem *firstRow = new QStandardItem(tmp);

        QStandardItem *secondRow = new QStandardItem(attrs);
        secondRow->setEditable(false);
        firstRow->setEditable(false);

        model->setItem(i,1,firstRow);
        model->setItem(i,0,secondRow);
    }
}
