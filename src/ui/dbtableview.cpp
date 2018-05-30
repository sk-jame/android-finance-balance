#include "dbtableview.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QClipboard>
#include <QApplication>
#include <QHeaderView>
#include <QDebug>
#include <QMouseEvent>
#include "data/databaseworker.h"

#define DB_CONNECTION_NAME ("dataWidget_connection")

DBTableView::DBTableView(QWidget *parent) :
    QTableView(parent),
    menu(this)
{

    setToolTip("Для смены типа показаний выберите в выпадающем списке на правую кнопку мыши");

    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setSortingEnabled( true );

    verticalHeader()->hide();

    proxyModel = NULL;
    sqlmodel = NULL;

    db = QSqlDatabase::addDatabase("QSQLITE", QString(DB_CONNECTION_NAME));
    db.setDatabaseName(DataBaseWorker::filename);

    foreach(QString table, DataBaseWorker::getTableList()){
        menu.addAction(table);
    }
    connect(&menu, &QMenu::triggered, this, &DBTableView::menuActionTriggered);
    enableDataWidget(true);
    selectDataBaseTable(DataBaseWorker::getTableList().first());
}

DBTableView::~DBTableView()
{
    enableDataWidget(false);
}

void DBTableView::keyReleaseEvent(QKeyEvent *ev){
    if ( ev->modifiers() == Qt::CTRL && ev->key() == Qt::Key_C ){
        copyToClipBoard();
    }
    QTableView::keyReleaseEvent( ev );
}

void DBTableView::mouseReleaseEvent(QMouseEvent *event){
    if ( event->button() == Qt::RightButton ){
        emit showContextMenu( event->screenPos().toPoint() );
    }
    QTableView::mouseReleaseEvent(event);
}

QList<QStringList> DBTableView::getCurrentItems(){
    QList<QStringList> res;
    for(int i = 0; i < this->model()->rowCount(); i++ ){
        QStringList temp;
        for( int j = 0; j < this->model()->columnCount(); j++ ){
            temp.push_back(this->model()->index(i,j).data().toString());
        }
        res << temp;
    }
    return res;
}

void DBTableView::enableDataWidget(bool enable){
    if ( enable ){
        db.open();
        sqlmodel = new QSqlTableModel(parent(), db);
        proxyModel = new QSortFilterProxyModel(parent());
        proxyModel->setSourceModel( sqlmodel );
        setModel( proxyModel );
        connect( this, SIGNAL(destroyed()), sqlmodel, SLOT(deleteLater()));
        connect( this, SIGNAL(destroyed()), proxyModel, SLOT(deleteLater()));
        selectDataBaseTable(0);
    }
    else{
        db.close();
    }
    this->setEnabled( enable );
}

void DBTableView::selectDataBaseTable(QString table){
    QStringList head;
    head << "#" << "Date" << "Time" << "Reason" << "Amount";
    sqlmodel->setTable(table );
    sqlmodel->select();
    for(int i = 0; i < head.count(); i++ ){
        sqlmodel->setHeaderData(i, Qt::Horizontal, QVariant(head.at(i)));
    }
    hide();
    show();
}

/**
 * @brief QDataTableWidget::copyToClipBoard копирует выделенные строки таблицы в буфер обмена приложения
 */

void DBTableView::copyToClipBoard(){

    QString cbStr;
    QClipboard *cb = QApplication::clipboard();
    QModelIndexList list =  selectionModel()->selectedIndexes();
    int firstRow;
    int lastRow;
    int rowCount;

    if( list.isEmpty() ) return;


    firstRow = list.first().row();
    lastRow = list.last().row();
    rowCount = lastRow - firstRow + 1;

    int i = 0;
    while( i < rowCount ){
        foreach(QModelIndex index, list){
            if( index.row() == ( i + firstRow ) ){
                cbStr += index.data().toString() + '\t';
            }
        }
        cbStr += '\n';
        i++;
    }

    cb->setText( cbStr );
}

void DBTableView::showContextMenu(QPoint point)
{
    menu.show();
    menu.move(point);
}

void DBTableView::menuActionTriggered(QAction *act)
{
    selectDataBaseTable(act->text());
}
