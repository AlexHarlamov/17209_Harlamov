#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../lab2/Includes.h"
#include "fieldwidget.h"
#include "dialog.h"


#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QString>

/*set point color by FLD/last_vivit(position);
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Field::getGlobal();
    ui->setupUi(this);
    FieldWidget *fld = new FieldWidget();
    ui->verticalLayout->addWidget(fld);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ListOfWarriors::getInstance()->Num_of_WRR() == 0){
        QMessageBox::StandardButton dm = QMessageBox::question
                (this,"Useless question","Sorry, we have no warriors :( \n want to continue?",
                 QMessageBox::Yes | QMessageBox::No);
        if(dm == QMessageBox::Yes){
            QMessageBox::critical(this,"Error","it still doesn't make sense :(");
        }
    }
    else{
        state = 0;
        while (state == 0)  {
           if(ListOfWarriors::getInstance()->Num_of_WRR() == 1){
               std::string s = "( ) Warrior wins!!";
               s[1] =(char)(48 + ListOfWarriors::getInstance()->first_warrior());
               QString qstr = QString::fromStdString(s);
               ui->statusBar->showMessage(qstr);
               state = 1;
           }

           ListOfWarriors::getInstance()->runAll();
           repaint();
           QCoreApplication::processEvents();
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton qt = QMessageBox::question
            (this,"Quit","Leave this app?",
             QMessageBox::Yes | QMessageBox::No);
    if(qt == QMessageBox::Yes){
        QApplication::quit();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QStringList f_names = QFileDialog::getOpenFileNames();

    std::ifstream inp;
    std::string sample;
    for (const auto& it : f_names){
        sample = it.toUtf8().constData();
        inp.open(sample);
        if(ListOfWarriors::getInstance()->CreateWarrior(inp))
            ui->statusBar->showMessage("Warrior added");
        else
            ui->statusBar->showMessage("Error: Invalid warrior");
        repaint();
    }
}


void MainWindow::on_actionresize_triggered()
{
    Dialog wnd;
    wnd.setModal(true);
    wnd.exec();
    repaint();
}

void MainWindow::on_actionclear_triggered()
{
    Field::getGlobal()->RestoreField(Field::getGlobal()->give_size());
    ListOfWarriors::getInstance()->kill_all_warriors();
    repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    state = 1;
}
