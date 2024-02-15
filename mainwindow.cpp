#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ctunes.h"
#include "Generos.h"
#include "QString"
#include "QDebug"

using namespace std;


CTunes ctunes;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    ui->panel->setCurrentIndex(1);
}


void MainWindow::on_pushButton_6_pressed()
{
    ui->panel->setCurrentIndex(0);
}


Generos::Genero stringToGender(QString genero){
    if(genero=="POP"){
        return Generos::POP;
    }else if(genero=="ROCK"){
        return Generos::ROCK;
    }else if(genero=="RAP"){
        return Generos::RAP;
    }else if(genero=="DANCE"){
        return Generos::DANCE;
    }else if(genero=="REGGAE"){
        return Generos::REGGAE;
    }else if(genero=="ELECTRONICA"){
        return Generos::ELECTRONICA;
    }else{
        return Generos::RANCHERA;
    }

}

void MainWindow::on_pushButton_7_pressed()
{

    QString nombre=ui->lineEdit->text();
    QString cantante=ui->lineEdit_2->text();
    double precio=ui->lineEdit_3->text().toDouble();
    QString selectedGenre = ui->comboBox->currentText();
    Generos::Genero genre=stringToGender(selectedGenre);
    ctunes.addSong(nombre,cantante,genre,precio);

}


void MainWindow::on_pushButton_5_pressed()
{
    ui->panel->setCurrentIndex(2);
}


void MainWindow::on_pushButton_8_pressed()
{
    int codeSong;
    codeSong=ui->lineEdit_4->text().toInt();
    QString text=ctunes.infoSong(codeSong);
    ui->textEdit->setText(text);
}


void MainWindow::on_pushButton_2_pressed()
{
    ui->panel->setCurrentIndex(3);
}


void MainWindow::on_pushButton_9_pressed()
{
    ui->panel->setCurrentIndex(0);
}


void MainWindow::on_pushButton_11_pressed()
{
    ui->panel->setCurrentIndex(0);
}


void MainWindow::on_pushButton_12_pressed()
{
    ui->panel->setCurrentIndex(0);
}


void MainWindow::on_pushButton_14_pressed()
{
    ui->panel->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_pressed()
{

}

