#ifndef _DBTABLE_VIEW_H_
#define _DBTABLE_VIEW_H_

#include <QTableView>
#include <QSqlDatabase>
#include <QModelIndex>
#include <QKeyEvent>
#include <QMenu>

class QSqlTableModel;
class QSortFilterProxyModel;

class DBTableView : public QTableView
{
    Q_OBJECT
private:
    QMenu menu;
    QSortFilterProxyModel* proxyModel;
    QSqlTableModel* sqlmodel;
    QSqlDatabase db;
public:
    explicit DBTableView(QWidget *parent = 0);
    ~DBTableView();
    virtual void keyReleaseEvent(QKeyEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    QList<QStringList> getCurrentItems();
signals:
    void requestContextMenu(QPoint point);
public slots:
    void enableDataWidget( bool enable );
    void selectDataBaseTable(QString table);
    void copyToClipBoard();
private slots:
    void showContextMenu(QPoint point);
    void menuActionTriggered(QAction* act);
};


#endif // _DBTABLE_VIEW_H_
