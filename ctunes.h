#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include "Generos.h"
#include "QString"
#include "QFile"
#include "QDate"

using namespace std;

class CTunes
{
public:

    //cons
    CTunes();

    //funcs
    int getCodigo(long offset);
    void addSong(QString nombre,QString cantante,Generos::Genero generoCantante,double precio,QString duracion);
    QString infoSong(int codeSong);
    void reviewSong(int code,int stars);
    bool downloadSong(int codeSongs,QString cliente);
    QString Song(QString fileText);

    //stru
    struct songFormat{
        int code;
        QString song;
        QString singer;
        QString duracion;
        QString gender;
        double price;
        int stars;
        int reviews;
    };

    //s
    struct downloadFormat{
        int DCode;
        QDate date;
        int SCode;
        QString nameCustomer;
        double priceSong;
    };
};



#endif // CTUNES_H
