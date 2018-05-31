#include <QDateTime>
#include <QFile>
#include <QDir>
#include <stdio.h>

#include "logger.h"

QMutex *Logger::mutex = Q_NULLPTR;
FILE *Logger::pFile = Q_NULLPTR;
bool Logger::m_callbackEvents = true;
Logger::LoggerCallback Logger::callBackFunction = Q_NULLPTR;

void Logger::setCallBackFunction(const LoggerCallback &value){
    if (callbackEvents()) callBackFunction = value;
}

void Logger::saveSlip(bool sendFromRouter, const QByteArray &data){
    QDateTime tv = QDateTime::currentDateTime();
    QString filename = QString("logs/slip_") + tv.date().toString("dd_MM_yyyy") + QString(".log");

    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)){
        static bool error = false;
        if (!error){
            DEBUG_OUT_EX("Неудалось открыть файл для сохранения slip!\n");
            error = true;
        }
        return;
    }
    QString str;
    str.append(tv.toString("dd.MM.yyyy hh:mm:ss.zzz\t"));
    str.append((sendFromRouter)?("s:\t"):("r:\t"));
    for(int i = 0; i < data.count(); i++){
        str.append(QString::number(quint8(data.at(i)), 16).rightJustified(2, '0'));
        str.append(" ");
    }

    str.append("\n");
    file.write(str.toStdString().c_str());
    if (!callbackEvents()) callBackFunction(str);
    file.flush();
    file.close();
}

bool Logger::callbackEvents(){
    return m_callbackEvents;
}

void Logger::setCallbackEvents(bool callbackEvents){
    m_callbackEvents = callbackEvents;
}

Logger::Logger(bool redirect, QString filename){
    init(redirect,filename);
}

Logger::~Logger(){
    deinit();
}

void Logger::init(bool redirect, QString filename){
    mutex = new QMutex();
    if (!redirect) return;
    if (filename.isNull()){
        QDir dir;
        dir.mkdir("logs");
        QDate date = QDate::currentDate();
        filename = QString("logs/r2t_") + date.toString("dd_MM_yyyy") + QString(".log");
    }
    QFile file(filename);
    if (!file.exists()){
        file.open(QIODevice::Append | QIODevice::Text);
        file.close();
    }

    if (pFile != Q_NULLPTR) fclose(pFile);


    pFile = freopen(filename.toStdString().c_str(), "a", stderr);
    setvbuf (pFile , NULL , _IONBF , 1024 );
}

void Logger::deinit(){
    fclose(stderr);
    if (mutex != Q_NULLPTR) delete mutex;
}

void Logger::out(const char * format, ...){
    if (mutex != Q_NULLPTR) mutex->lock();
    char buffer[1024];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    fprintf(stderr, buffer);
    va_end (args);
    if (callbackEvents()) callBackFunction(QString(buffer));
    if (mutex != Q_NULLPTR) mutex->unlock();
}

void Logger::out_ex(QString fun, int line, const char *format, ...){
    if (mutex != Q_NULLPTR) mutex->lock();
    addTimeToMsg();
    fprintf(stderr, "func:%s line:%i\t", fun.toStdString().c_str(), line);
    char buffer[4096];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    fprintf(stderr, buffer);
    fflush(stderr);
    va_end (args);
    if (callbackEvents()) callBackFunction(buffer);
    if (mutex != Q_NULLPTR) mutex->unlock();
}

void Logger::addTimeToMsg(){
    static QDate date = QDateTime::currentDateTime().date();
    QDateTime tv = QDateTime::currentDateTime();
    bool res = tv.date() != date;
    if (res){
        date = tv.date();
        init(true);
    }
    fprintf(stderr,"%s", tv.toString("dd.MM.yyyy hh:mm:ss.zzz\t").toStdString().c_str());
    if (callbackEvents()) callBackFunction(tv.toString("dd.MM.yyyy hh:mm:ss.zzz\t"));
}
