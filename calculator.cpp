#include "calculator.h"
#include "./ui_calculator.h"
#include <iostream>


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

//Memory vars
double memoryVal = 0.0;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));

    //Connect Number Buttons
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()),this, SLOT(NumPressed()));
    }

    //Connect Math Buttons
    //add
    QPushButton *addButton = Calculator::findChild<QPushButton *>("Add");
    connect(addButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    //substract
    QPushButton *subButton = Calculator::findChild<QPushButton *>("Substract");
    connect(subButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    //multiply
    QPushButton *multButton = Calculator::findChild<QPushButton *>("Multiply");
    connect(multButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    //Divide
    QPushButton *divButton = Calculator::findChild<QPushButton *>("Divide");
    connect(divButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    //Connect Equals Button
    QPushButton *eqButton = Calculator::findChild<QPushButton *>("Equals");
    connect(eqButton, SIGNAL(released()), this, SLOT(EqualButton()));

    //Connect Change sign Button
    QPushButton *changeSignButton = Calculator::findChild<QPushButton *>("ChangeSign");
    connect(changeSignButton, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    //Connect SaveToMemoryPos Button
    QPushButton *memAddButton = Calculator::findChild<QPushButton *>("MemAdd");
    connect(memAddButton, SIGNAL(released()), this, SLOT(SaveToMemoryPos()));

    //Connect SaveToMemoryNeg Button
    QPushButton *memNegButton = Calculator::findChild<QPushButton *>("MemNeg");
    connect(memNegButton, SIGNAL(released()), this, SLOT(SaveToMemoryNeg()));

    //Connect LoadFromMemory Button
    QPushButton *loadMemButton = Calculator::findChild<QPushButton *>("MemLoad");
    connect(loadMemButton, SIGNAL(released()), this, SLOT(LoadFromMemory()));

    //Connect AClear Button
    QPushButton *AClearButton = Calculator::findChild<QPushButton *>("Clear");
    connect(AClearButton, SIGNAL(released()), this, SLOT(AClear()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0 ){
        ui->Display->setText(butVal);
    }else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));


    }
}

void Calculator::MathButtonPressed(){
    //Set all the triggers to false first
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    //get the value in the diplay
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    //Check what button was pressed
    QPushButton *button = (QPushButton *)sender(); //we get who's sending the signal (what button triggered this)
    QString butVal = button->text();

    if(QString::compare(butVal, "/",Qt::CaseInsensitive)==0){
        divTrigger = true;
    }else if(QString::compare(butVal, "*",Qt::CaseInsensitive)==0){
        multTrigger = true;
    }else if(QString::compare(butVal, "+",Qt::CaseInsensitive)==0){
        addTrigger = true;
    }else {
        subTrigger = true;
    }
    // std::cout << "test" << std::endl;

    ui->Display->setText("");
}

void Calculator::EqualButton(){
    // std::cout << "equals button" << std::endl;
    double solution = 0.0;
    QString displayVal = ui ->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }else {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));

}
void Calculator::ChangeNumberSign(){
    // std::cout << "change sign" << std::endl;
    double solution = 0.0;
    QString displayVal = ui ->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    solution = - dblDisplayVal;
    ui->Display->setText(QString::number(solution));

}

void Calculator::SaveToMemoryPos(){
    QString displayVal = ui ->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    memoryVal = dblDisplayVal;

}

void Calculator::SaveToMemoryNeg(){
    QString displayVal = ui ->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    memoryVal = -dblDisplayVal;

}
void Calculator::LoadFromMemory(){
    //Clear display
    // ui->Display->setText("");
    // double dblNewVal = memoryVal;
    ui->Display->setText(QString::number(memoryVal,'g',16));


}
void Calculator::AClear(){
    //Clear display
    ui->Display->setText("");
    calcVal = 0.0;
}


