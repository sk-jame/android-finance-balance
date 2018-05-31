#ifndef LOGGERDIALOG_H
#define LOGGERDIALOG_H

#include <QDialog>
#include <QMutex>
#include <QTimer>

namespace Ui {
class LoggerDialog;
}

class LoggerDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool follow READ follow WRITE setFollow NOTIFY followChanged)
    Q_PROPERTY(bool showed READ isShowed WRITE setShowed NOTIFY showedChanged)

public:
    explicit LoggerDialog(QWidget *parent = 0);
    ~LoggerDialog();
    bool follow() const;

    bool isShowed() const;

public slots:
    virtual void open();
    void addText(QString str);
    void setFollow(bool follow);
    void setShowed(bool showed);

signals:
    void followChanged(bool follow);
    void showedChanged(bool showed);
private slots:
    void onTimerTo();
    void on_cbFollow_toggled(bool checked);
    void on_pbShowType_clicked();
    void colorAppend(QString str);

private:
    QTimer timer;
    QMutex mutex;
    Ui::LoggerDialog *ui;
    QString queue;
    bool m_follow;
    bool m_showEvents;
    bool m_showed;
};

#endif // LOGGERDIALOG_H
