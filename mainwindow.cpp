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
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    syntaxHigh=new SyntaxHighlighter(ui->plainTextEdit->document());
    //add button to main toolbar
    this->addWidgetsToolBar();
    // hide the second frame and third
    ui->frame_2->hide();
    ui->parserFrame->hide();
    //disable the clear button
    ui->pushButton_3->hide();


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
    connect(aboutButton,SIGNAL(clicked()),this,SLOT(aboutButtonClicked()));

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
void MainWindow::aboutButtonClicked(){
    QMessageBox::about(this,"About","Developed by Osama Bin Omar");
}

void MainWindow::on_pushButton_2_clicked()
{
    //hide the secod frame
        if(!ui->parserFrame->isHidden()){
            ui->parserFrame->hide();
        }

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
        ui->frame_2->show();
        //show the clear button
        ui->pushButton_3->show();
        //set the current mode for the clear button
        isInParseMode=false;

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

void MainWindow::on_pushButton_3_clicked()
{
    //this is the clear button
    //check if im in analyze or parse mode
    if(isInParseMode){
        //this is the parse mode
        ui->parserFrame->hide();
        ui->parseButton->setEnabled(true);
        isInParseMode=false;

    }else{
        //im in analyze mode
        ui->frame_2->hide();

    }
    ui->plainTextEdit->clear();
    ui->pushButton_3->hide();
    QMessageBox::information(this,"Clear","Everything cleared!!");


}

void MainWindow::on_parseButton_clicked()
{
    // first check if code editor has text
    if(ui->plainTextEdit->toPlainText().length()<=0){
                QMessageBox::information(this,"No code to parse","Please add production rules in code area to parse.");
                return;
    }
    isInParseMode=true;

    //disable the parse button
    ui->parseButton->setEnabled(false);
    //hide the secod frame
    if(!ui->frame_2->isHidden()){
        ui->frame_2->hide();
    }
    //show the parse frame
    ui->parserFrame->show();
    //show the clear button
    ui->pushButton_3->show();

      //get the total number of lines
    QString text=ui->plainTextEdit->toPlainText();
    QString temp;
    std::vector<std::string> productions;

    for(int i=0;i<text.length();i++){
        if(text[i]=='\n'){
            std::cout<<"temp is"<<temp.toStdString()<<std::endl;
            productions.push_back(temp.toStdString());
            temp="";
            continue;
        }else if(text[i]==' '){
            //do not add spaces
            continue;
        }
        temp.append(text[i]);
    }

    //set the parser options.
    parser.setProductions(productions);
    parser.setT(productions.size());
    parser.getAns();
    //populate the table
    populateSets();

}

void MainWindow::populateSets(){

    QTableView *table=ui->firstSetTable;
    vector<char> non_colt=parser.getNonColt();
    set<char>*   first_set=parser.getFirstSet();
    set<char>*   follow_set=parser.getFollowSet();

    QStandardItemModel *modelFirst = new QStandardItemModel(non_colt.size(),2,this);
    modelFirst->setHorizontalHeaderItem(0, new QStandardItem(QString("Symbol")));
    modelFirst->setHorizontalHeaderItem(1, new QStandardItem(QString("Set")));
    table->setModel(modelFirst);
    modelFirst->setColumnCount(2);
    modelFirst->setRowCount(non_colt.size());

    for (int i = 0; i<non_colt.size(); i++)
    {
        QString tmp="{ "; // opening bracket of set

        QStandardItem *secondRow = new QStandardItem(QString(QChar(non_colt[i])));
        secondRow->setEditable(false);
        modelFirst->setItem(i,0,secondRow);

        set<char>::iterator it;
        for (it = first_set[i].begin(); it != first_set[i].end(); it++){
            tmp[tmp.length()]=QChar(*it);
            tmp.append(", ");

        }
        //add the closing bracked in string
        tmp.replace(tmp.length()-2,tmp.length()," }");
        //set the item table
        QStandardItem *firstRow = new QStandardItem(tmp);
        firstRow->setEditable(false);
        modelFirst->setItem(i,1,firstRow);
    }

    //follow set
    QTableView *followTable=ui->followSetTable;
    QStandardItemModel *modelFollow = new QStandardItemModel(non_colt.size(),2,this);
    modelFollow->setHorizontalHeaderItem(0, new QStandardItem(QString("Symbol")));
    modelFollow->setHorizontalHeaderItem(1, new QStandardItem(QString("Set")));
    followTable->setModel(modelFollow);
    modelFollow->setColumnCount(2);
    modelFollow->setRowCount(non_colt.size());


    for (int i = 0; i<non_colt.size(); i++)
    {
        QString tmp="{ "; // opening bracket of set

        QStandardItem *secondRow = new QStandardItem(QString(QChar(non_colt[i])));
        secondRow->setEditable(false);
        modelFollow->setItem(i,0,secondRow);

        set<char>::iterator it;
        for (it = follow_set[i].begin(); it != follow_set[i].end(); it++){
            tmp[tmp.length()]=QChar(*it);
            tmp.append(", ");
        }
        //add the closing bracked in string
        tmp.replace(tmp.length()-2,tmp.length()," }");
        //set the item table
        QStandardItem *firstRow = new QStandardItem(tmp);
        firstRow->setEditable(false);
        modelFollow->setItem(i,1,firstRow);
    }
}


void MainWindow::on_parseStringButton_clicked()
{
    //parse the input string according to given rules
    std::string s=ui->symbolString->text().toStdString();
    if(s.length()<1){
        //string is empty
        QMessageBox::information(this,"No string to parse","Please input string to parse.");
        return;
    }
    // get the necessary fields
    vector<char>    left_any    = parser.getLeftAny();
    vector<char>    to_any      = parser.getRightAny();
    vector<char>    non_colt    = parser.getNonColt();
    node*           analy_str   = parser.getAnalyString();

    //set up the table ui
    QTableView *table=ui->parserResultTable;
    QStandardItemModel *model = new QStandardItemModel(non_colt.size(),3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Stack")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Remaining input")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Derivation")));

    table->setModel(model);
    model->setColumnCount(3);


    for (int i = s.length() - 1; i >= 0; i--)
        left_any.push_back(s[i]);

    to_any.push_back('#');
    to_any.push_back(non_colt[0]);
    int count=0;

    while (left_any.size()>0)
    {

        QString outs = "";
        for (int i = 0; i<to_any.size(); i++)
            outs[i]= to_any[i];
        QStandardItem *Row0 = new QStandardItem(outs);
        Row0->setEditable(false);
        model->setItem(count,0,Row0);


        outs = "";
        for (int i = left_any.size() - 1; i >= 0; i--)
            outs[i]= left_any[i];

        QStandardItem *Row1 = new QStandardItem(outs);
        Row1->setEditable(false);
        model->setItem(count,1,Row1);

        char char1 = to_any[to_any.size() - 1];
        char char2 = left_any[left_any.size() - 1];
        if (char1 == char2 && char1 == '#')
        {
            QMessageBox::information(this,"Accepted","Input string is recognizable by given grammer");

            return;
        }
        if (char1 == char2)
        {
            to_any.pop_back();
            left_any.pop_back();
            outs="";
            outs[0]=char1;
            outs.append(" match");
            QStandardItem *Row2 = new QStandardItem(outs);
            Row2->setEditable(false);
            model->setItem(count,2,Row2);
        }
        else if (parser.tableMap[parser.get_index(char1)][parser.get_nindex(char2)] != -1)
        {
            int tg = parser.tableMap[parser.get_index(char1)][parser.get_nindex(char2)];
            to_any.pop_back();

            if (analy_str[tg].right != "$")
            {
                for (int i = analy_str[tg].right.length() - 1; i >= 0; i--)
                    to_any.push_back(analy_str[tg].right[i]);
            }

           QString temp=temp.fromStdString(analy_str[tg].right);
           QStandardItem *Row2 = new QStandardItem(temp);
           Row2->setEditable(false);
           model->setItem(count,2,Row2);
        }
        else
        {
            QMessageBox::information(this,"Can't parse","Input string is not recognizable by given grammer");
            return;
        }
        count++;
    }

}
