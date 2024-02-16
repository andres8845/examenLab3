#include "ctunes.h"
#include <iostream>
#include "fstream"
#include "ctunes.h"
#include "Generos.h"
#include "QString"
#include "QFile"
#include "QDataStream"
#include "QDebug"
#include "QMessageBox"


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
    canciones<<structFormat.code<<structFormat.song<<structFormat.singer<<structFormat.duracion<<structFormat.gender
              <<structFormat.price<<structFormat.stars<<structFormat.reviews;
    songs.flush();

};

QString CTunes::infoSong(int codeSong){
    songs.seek(0);
    while(!songs.atEnd()){
        CTunes::songFormat formato;
        CTunes::downloadFormat format;
        QString msg;
        canciones>>formato.code>>formato.song>>formato.singer>>formato.duracion>>formato.gender>>formato.price>>formato.stars>>formato.reviews;

        if(formato.code==codeSong){
            downloads.seek(0);
            msg+="Código: "+QString::number(formato.code)+" - Nombre: "+formato.song+" - Cantante: "+formato.singer+
                   " - Duracion: "+formato.duracion+" - Género: "+formato.gender+" - Precio: "+
                   QString::number(formato.price)+" - Estrellas: "+QString::number(formato.stars)+" - Reseñas: "+
                   QString::number(formato.reviews)+"\n--------------------------------------------";
            while(!downloads.atEnd()){

                descargas>>format.DCode>>format.date>>format.SCode>>format.nameCustomer>>format.priceSong;

                int dia=format.date.day();
                int mes=format.date.month();
                int ano=format.date.year();

                QString fecha=QString::number(dia)+"/"+QString::number(mes)+"/"+QString::number(ano);
                if(codeSong==format.SCode){
                    msg+="\n"+format.nameCustomer+" descargo cancion con codigo: "+QString::number(format.SCode)+", en "+fecha;
                }
            }
            return msg;
        }
    }
    return "No se ha encontrado la cancion!!!!!!!!!!";
}

void CTunes::reviewSong(int codeSong,int stars){
    songs.seek(0);
    while(!songs.atEnd()){
        long posicion=songs.pos();
        int code;
        QString name;
        QString singer;
        QString gender;
        QString duracion;
        double price;
        int starz;
        int reviews;

        canciones>>code>>name>>singer>>duracion>>gender>>price>>starz>>reviews;

        if(code==codeSong){
            songs.seek(posicion);
            starz+=stars;
            reviews+=1;
            canciones<<code<<name<<singer<<duracion<<gender<<price<<starz<<reviews;
            QMessageBox::information(nullptr, "Message", "Se ha dado un review correctamente!");
            return;
        }
    }
     QMessageBox::warning(nullptr, "Advertencia", "Codigo inexistente!");
}


bool CTunes::downloadSong(int codeSongs,QString cliente){
    songs.seek(0);
    CTunes::songFormat formato;
    CTunes::downloadFormat format;
    while(!songs.atEnd()){
        canciones>>formato.code>>formato.song>>formato.singer>>formato.duracion>>formato.gender>>formato.price>>formato.stars>>formato.reviews;
        if(formato.code==codeSongs){
            downloads.seek(downloads.size());
            int newCode= getCodigo(4);

            QDate date=QDate::currentDate();

            descargas<<newCode<<date<<codeSongs<<cliente<<formato.price;

            QMessageBox::information(nullptr,"Message","GRACIAS "+cliente+" por bajar "+formato.song+" a un costo de Lps."+
            QString::number(formato.price));
            return true;
        }
    }
    return false;
}

QString CTunes::Song(QString textFile){
    QFile textArchive(textFile+".txt");
    textArchive.open(QIODevice::ReadWrite);
    QTextStream write(&textArchive);
    CTunes::songFormat f;
    songs.seek(0);
    textArchive.seek(0);
    QString message;
    while(!songs.atEnd()){
        canciones>>f.code>>f.song>>f.singer>>f.duracion>>f.gender>>f.price>>f.stars>>f.reviews;
        double ztarz = static_cast<double>(f.stars);
        double reviewz = static_cast<double>(f.reviews);
        double rating=ztarz/reviewz;

        qDebug()<<QString::number(rating,'f',1);
        write<<QString::number(f.code)+" - "<<f.song+" - "<<f.singer+" - "<<f.duracion+" - "<<QString::number(f.price)+" - "<<QString::number(rating,'f',1)+" |\n";
        message+="\n"+QString::number(f.code)+" - "+f.song+" - "+f.singer+" - "+f.duracion+" - "+QString::number(f.price)+" - "+QString::number(rating,'f',1);
    }

    return message;
}


