#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QDebug>
#include <QMutex>
#include "stdarg.h"


class Logger
{
public:
    typedef void (*LoggerCallback)(QString text);

private:
    static QMutex *mutex;
    static FILE *pFile;
    static LoggerCallback callBackFunction;
    static bool m_callbackEvents;
public:

    Logger(bool redirect, QString filename = QString());
    ~Logger();

    /**
     * @brief init перенаправляет stderr в файл @param filename, если @param redirect
     *	установлен в true
     * @param redirect true/false
     * @param filename QString
     */
    static void init(bool redirect, QString filename = QString());
    static void deinit();

    static void out(const char * format, ...);
    static void out_ex(QString fun, int line, const char * format, ...);

    static void setCallBackFunction(const LoggerCallback &value);
    static void saveSlip(bool sendFromRouter, const QByteArray &data);

    static bool callbackEvents();
    static void setCallbackEvents(bool callbackEvents);

protected:
    static void addTimeToMsg();
};

#define DEBUG_OUT(...)    { Logger::out(__VA_ARGS__); }
#define DEBUG_OUT_EX(...) { Logger::out_ex(__FUNCTION__, __LINE__, __VA_ARGS__); }

#endif // LOGGER_H
