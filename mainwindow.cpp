#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ctunes.h"
#include "Generos.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"

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

//Combo devuelve String
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

    //"ints"
    QString price=ui->lineEdit_3->text();
    QString minutes=ui->lineEdit_9->text();
    QString seconds=ui->lineEdit_10->text();

    //bools
    bool isNumeric;
    bool isNumeric2;
    bool isNumeric3;

    //"ints" are ints?
    price.toDouble(&isNumeric);
    minutes.toInt(&isNumeric2);
    seconds.toInt(&isNumeric3);

    //letra o simbolo en precio
    if(!isNumeric){
        QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero en el precio!");
        ui->lineEdit_3->clear();
    }else{
        //precio negativo
        if(price.toInt()<0){
            QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero valido en el precio!");
            ui->lineEdit_3->clear();
        }else{
            //min y sec- letra o simbolo
            if(!isNumeric2 && !isNumeric3){
                QMessageBox::warning(nullptr, "Advertencia", "Ingrese un número válido en Minutos y Segundos.");
                ui->lineEdit_9->clear();
                ui->lineEdit_10->clear();
                //min y no sec
            }else if(!isNumeric2 && isNumeric3){
                QMessageBox::warning(nullptr, "Advertencia", "Ingrese un número válido en Minutos.");
                ui->lineEdit_9->clear();
                //sec y no min
            }else if(isNumeric2 && !isNumeric3){
                QMessageBox::warning(nullptr, "Advertencia", "Ingrese un número válido en Segundos.");
                ui->lineEdit_10->clear();
            }else{
                //min y sec, son -
                if(minutes.toInt()<0 || seconds.toInt()<0){
                    QMessageBox::warning(nullptr, "Advertencia", "Ingrese un número válido en Minutos o Segundos.");
                    ui->lineEdit_9->clear();
                    ui->lineEdit_10->clear();
                    //duracion 0
                }else if(minutes.toInt()==0 && seconds.toInt()==0){
                    QMessageBox::warning(nullptr, "Advertencia", "La duracion de la cancion no puede ser 0.");
                    ui->lineEdit_9->clear();
                    ui->lineEdit_10->clear();
                    //min o sec tercera edad
                }else if(minutes.toInt()>60 || seconds.toInt()>60){
                    QMessageBox::warning(nullptr, "Advertencia", "Minutos o Segundos fuera de rango!");
                    ui->lineEdit_9->clear();
                    ui->lineEdit_10->clear();
                    //okokokokokokokokokokokokokok
                }else{

                    QString nombre=ui->lineEdit->text();
                    QString cantante=ui->lineEdit_2->text();

                    double precio=ui->lineEdit_3->text().toDouble();
                    QString selectedGenre = ui->comboBox->currentText();

                    Generos::Genero genre=stringToGender(selectedGenre);
                    QString duracion=minutes+":"+seconds;

                    //+
                    ctunes.addSong(nombre,cantante,genre,precio,duracion);

                    QMessageBox::information(nullptr, "Message", "Se ha creado la cancion correctamente!");

                    //reset
                    ui->lineEdit->clear();
                    ui->lineEdit_2->clear();
                    ui->lineEdit_3->clear();
                    ui->lineEdit_9->clear();
                    ui->lineEdit_10->clear();
                }
            }
        }
    }








}


void MainWindow::on_pushButton_5_pressed()
{
    ui->panel->setCurrentIndex(2);
}


void MainWindow::on_pushButton_8_pressed()
{
    //"int"
    int codeSong;
    QString text=ui->lineEdit_4->text();

    //impostor?
    bool isNumeric;
    //test
    text.toInt(&isNumeric);

    //si
    if (!isNumeric) {
        QMessageBox::warning(nullptr, "Advertencia", "Por favor, ingrese un numero valido en Codigo.");
        ui->lineEdit_4->clear();
    }else{
        //no
        codeSong=ui->lineEdit_4->text().toInt();
        QString text=ctunes.infoSong(codeSong);
        ui->textEdit->setText(text);
    }



}


void MainWindow::on_pushButton_2_pressed()
{
    ui->panel->setCurrentIndex(3);
}


void MainWindow::on_pushButton_9_pressed()
{
    ui->panel->setCurrentIndex(0);
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}


void MainWindow::on_pushButton_11_pressed()
{
    ui->panel->setCurrentIndex(0);
    ui->lineEdit_4->clear();
    ui->textEdit->clear();
}


void MainWindow::on_pushButton_12_pressed()
{
    ui->panel->setCurrentIndex(0);
}


void MainWindow::on_pushButton_14_pressed()
{
    ui->panel->setCurrentIndex(0);
    ui->textEdit_2->clear();
    ui->lineEdit_11->clear();
}


void MainWindow::on_pushButton_4_pressed()
{
    ui->panel->setCurrentIndex(5);
}


void MainWindow::on_pushButton_10_pressed()
{
    //"ints"
    QString code=ui->lineEdit_5->text();
    QString stars=ui->lineEdit_6->text();

    //bool
    bool isNumeric;
    bool isNumeric2;

    //si o no?
    code.toDouble(&isNumeric);
    stars.toInt(&isNumeric2);
    //no no
    if(!isNumeric && !isNumeric2){
        QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero valido en Codigo y Stars.");
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        //no si
    }else if(!isNumeric && isNumeric2){
        QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero valido en Codigo.");
        ui->lineEdit_5->clear();
        //si no
    }else if(isNumeric && !isNumeric2){
        QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero valido en Stars.");
        ui->lineEdit_6->clear();
    }else{
        //si si,
        int codigoz=ui->lineEdit_5->text().toInt();
        int estrellaz=ui->lineEdit_6->text().toInt();

        //estrella pasada
        if(estrellaz<0 || estrellaz>5){
            QMessageBox::warning(nullptr, "Advertencia", "Ingrese un numero valido en Stars.");
            ui->lineEdit_6->clear();
        }else{
            //bien
            ctunes.reviewSong(codigoz,estrellaz);
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
        }

    }

}


void MainWindow::on_pushButton_13_pressed()
{
    //"?"
    QString code=ui->lineEdit_7->text();
    QString customer=ui->lineEdit_8->text();
    //
    bool isNumeric;

    //v
    code.toInt(&isNumeric);
    //no
    if(!isNumeric){
        QMessageBox::warning(nullptr, "Advertencia", "Ingresar un codigo valido!");
        ui->lineEdit_7->clear();
        //si
    }else if(isNumeric){
        //no code
        if(!ctunes.downloadSong(code.toInt(),customer)){
            QMessageBox::warning(nullptr, "Advertencia", "Codigo no encontrado!");
        }
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
    }

}


void MainWindow::on_pushButton_3_pressed()
{
    ui->panel->setCurrentIndex(4);
}


void MainWindow::on_pushButton_15_pressed()
{
    //agarra
    QString texto=ctunes.Song(ui->lineEdit_11->text());

    //lo pone
    ui->textEdit_2->setText(texto);
    qDebug()<<texto;
}

