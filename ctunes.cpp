#include "ctunes.h"
#include <iostream>
#include "fstream"
#include "ctunes.h"
#include "Generos.h"
#include "QString"
#include "QFile"
#include "QDataStream"
#include "QDebug"



QFile songs("songs.itn");
QFile codes("codigos.itn");
QFile downloads("downloads.itn");

QDataStream canciones(&songs);
QDataStream codigos(&codes);
QDataStream descargas(&downloads);

CTunes::CTunes() {
    codes.open(QIODevice::ReadWrite);
    if(codes.size()==0){
        codigos<<1<<1;
    }
    songs.open(QIODevice::ReadWrite);
    downloads.open(QIODevice::ReadWrite);

    if(!codes.isOpen()){
        qDebug()<<"No se pudo abrir el archivo de codigos.";
    }else if(!songs.isOpen()){
        qDebug()<<"No se pudo abrir el archivo de canciones.";
    }else if(!downloads.isOpen()){
        qDebug()<<"No se pudo abrir el archivo de descargas.";
    }

}



int CTunes::getCodigo(long offset){

    codes.seek(offset);
    int codigoActual;
    codigos>>codigoActual;
    int giveCode=codigoActual;
    codigoActual+=1;
    codes.seek(offset);
    codigos<<codigoActual;
    return giveCode;

}



void CTunes::addSong(QString nombre, QString cantante, Generos::Genero generoCantante, double precio, QString duracion){

    songFormat structFormat;
    int newCode=getCodigo(0);
    structFormat.code=newCode;
    structFormat.song=nombre;
    structFormat.singer=cantante;

    QString stringGenero;
    if(generoCantante==Generos::POP){
        stringGenero="Pop";
    }else if(generoCantante==Generos::RAP){
        stringGenero="Rap";
    }else if(generoCantante==Generos::ROCK){
        stringGenero="Rock";
    }else if(generoCantante==Generos::DANCE){
        stringGenero="Dance";
    }else if(generoCantante==Generos::REGGAE){
        stringGenero="Reggae";
    }else if(generoCantante==Generos::ELECTRONICA){
        stringGenero="Electronica";
    }else{
        stringGenero="Ranchera";
    }

    structFormat.gender=stringGenero;
    structFormat.price=precio;
    structFormat.duracion=duracion;
    structFormat.stars=0;
    structFormat.reviews=0;
    songs.seek(songs.size());
    canciones<<structFormat.code<<structFormat.song<<structFormat.singer<<structFormat.gender<<structFormat.price
             <<structFormat.stars<<structFormat.reviews;
    songs.flush();

};

QString CTunes::infoSong(int codeSong){
    songs.seek(0);
    while(!songs.atEnd()){
        int code;
        QString name;
        QString singer;
        QString gender;
        double price;
        int stars;
        int reviews;

        canciones>>code>>name>>singer>>gender>>price>>stars>>reviews;

        if(code==codeSong){
            return "Código: "+QString::number(code)+", Nombre: "+name+", Cantante: "+singer+", Género: "+gender+
            ", Precio: "+QString::number(price)+", Estrellas: "+QString::number(stars)+", Reseñas: "+QString::number(reviews);
            songs.seek(songs.size());
        }
    }
    return "No se ha encontrado la cancion!!!!!!!!!!";
}


