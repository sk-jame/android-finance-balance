#include "dbtableview.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QClipboard>
#include <QApplication>
#include <QHeaderView>
#include <QDebug>
#include <QMouseEvent>
#include "data/databaseworker.h"
#include <QPainter>
#define DB_CONNECTION_NAME ("dataWidget_connection")

//class MyDBDelegate : public QItemDelegate
//{
//public:
//    MyDBDelegate(QObject *parent = Q_NULLPTR)
//        : QItemDelegate(parent)
//    {
//    }

//    // QAbstractItemDelegate interface
//public:
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
//};

//void MyDBDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    if (index.column() == DataBaseWorker::db_columns().idx_reason){
//        QAbstractItemModel* model = const_cast<QAbstractItemModel*>(index.model());
//        model->setData(index, Operation::getTypesNames().at(index.data().toInt()), Qt::DisplayRole);
//    }
//    QItemDelegate::paint(painter, option, index);
//}

//QSize MyDBDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QFontMetrics fm(option.font);
//    if (index.column() == DataBaseWorker::db_columns().idx_reason){
//        return fm.size(0, Operation::getTypesNames().at(index.data().toInt()));
//    }

//    return fm.size(0, index.data().toString()); // QAbstractItemDelegate::sizeHint(option, index);
//}

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
    else if (indexAt(event->pos()).column() == DataBaseWorker::db_columns().idx_reason){
        setToolTip(Operation::getTypesNames().at(indexAt(event->pos()).data().toInt()));
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
//        this->setItemDelegateForColumn(DataBaseWorker::db_columns().idx_reason, new MyDBDelegate());
        db.open();
        sqlmodel = new QSqlTableModel(parent(), db);
        proxyModel = new QSortFilterProxyModel(parent());
        proxyModel->setSourceModel( sqlmodel );
        setModel( proxyModel );
        connect( this, SIGNAL(destroyed()), sqlmodel, SLOT(deleteLater()));
        connect( this, SIGNAL(destroyed()), proxyModel, SLOT(deleteLater()));
        selectDataBaseTable(DataBaseWorker::income_table_name);

    }
    else{
        db.close();
    }
    this->setEnabled(enable);
}

void DBTableView::selectDataBaseTable(QString table){
    sqlmodel->setTable(table );
    sqlmodel->select();
    static int init = 0;
    for(int i = 0; i < DataBaseWorker::db_columns().column_names.count(); i++ ){
//        if (init == 0){
//            this->setItemDelegateForColumn(i, new MyDBDelegate(this));
//        }
        sqlmodel->setHeaderData(i, Qt::Horizontal, QVariant(DataBaseWorker::db_columns().column_names.at(i)));
    }
    init = 1;
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
