#include "qtablesortwidget.h"
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include "logger.h"
#include <QMenu>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>


QTableSortWidget::QTableSortWidget(QWidget *parent)
	: QTableWidget(parent){

	connect(horizontalHeader(), SIGNAL(sectionClicked(int)),
			this,				SLOT(sortColumn(int)));

	qRegisterMetaType<ConvertFunction>("ConvertFunction");
    searchDialogCreated = false;
}

QTableSortWidget::QTableSortWidget(int rows, int columns, QWidget *parent)
	: QTableWidget(rows, columns, parent){

	connect(horizontalHeader(), SIGNAL(sectionClicked(int)),
			this,				SLOT(sortColumn(int)));
	qRegisterMetaType<ConvertFunction>("ConvertFunction");
    searchDialogCreated = false;
}


void QTableSortWidget::setSortType(int col, ESortType type){
	if ( col < sortTypeList.count()){
		sortTypeList[col] = type;
	}
	else{
		sortTypeList.insert(col, type);
	}
}

void QTableSortWidget::convertColumnValue(int col, QTableSortWidget::ConvertFunction func){
	for(int i = 0; i < this->rowCount(); i++){
		func(this->item(i, col));
    }
}

typedef void (*swapFunctionType)(int rowAindex, int rowBindex);
void QTableSortWidget::sortColumn(int column){

	if ( column >= sortDirections.count()){
		sortDirections.resize(column+1);
		sortDirections[column] = less;
	}

    sortFunctionType sortStringAsFloat = [](QTableWidgetItem* i1,QTableWidgetItem* i2)->bool {
		double num1 = i1->text().toDouble();
		double num2 = i2->text().toDouble();
		return num1 < num2;
	};

    sortFunctionType sortStringAsHex = [](QTableWidgetItem* i1,QTableWidgetItem* i2)->bool {
		bool ok;
        QString str1 = i1->text().remove("x");
        QString str2 = i2->text().remove("x");
        long long num1 = str1.toLongLong(&ok, 16);
        long long num2 = str2.toLongLong(&ok, 16);
		return num1 < num2;
	};

	if (column >= sortTypeList.count() || sortTypeList.at(column) == sort_strings){
		this->sortByColumn(column);
		return;
	}

	sortFunctionType cmp;
	cmp = (sortTypeList.at(column) == sort_hex)?(sortStringAsHex):(sortStringAsFloat);

	QApplication::setOverrideCursor(Qt::BusyCursor);

	int i, j;
	for (i = 1; i < rowCount(); ++i){
		QList<QTableWidgetItem*> tmp = this->takeRow(i);
        for (j = i - 1; j >= 0 && cmpDir(tmp.at(column), item(j, column), cmp, column); --j){
			swapFunction(j+1, j);
		}
		setRow(j + 1, tmp);
	}


	if (sortDirections[column] == less){
		sortDirections[column] = greater;
	}
	else{
		sortDirections[column] = less;
	}
	QApplication::restoreOverrideCursor();

}

void QTableSortWidget::find(QString searchStr){
    DEBUG_OUT_EX("Find request %s\n", searchStr.toStdString().c_str());
    if (searchStr.isEmpty() ||
        searchStr.count() < lastSearchString.count()){

        int count = this->rowCount();
        for(int i = 0; i < count; i++){
            this->showRow(i);
        }
    }
    lastSearchString = searchStr;


    QList<QTableWidgetItem*> foundList = findItems(searchStr, Qt::MatchContains);
    QSet<int> rows;
    foreach (QTableWidgetItem* item, foundList) {
        rows.insert(item->row());
    }

    DEBUG_OUT_EX("Matched: %i from %i\n", rows.count(), this->rowCount());
    int count = this->rowCount();
    for(int i = 0; i < count; i++){
        if (!rows.contains(i)) this->hideRow(i);
    }
}

void QTableSortWidget::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        QMenu menu(this);
        menu.addAction("Копировать в буфер обмена");
        QAction* actFind = menu.addAction("Найти...");
        QRect rect = menu.geometry();
        rect.moveTopLeft(event->screenPos().toPoint());
        menu.setGeometry(rect);
        QAction* res = menu.exec();
        if (res == Q_NULLPTR){
            QTableWidget::mouseReleaseEvent(event);
            return;
        }
        if (res != actFind){
            copyToClipBoard();
        }
        else{
            showFindPopup();
        }
    }
    QTableWidget::mouseReleaseEvent(event);
}


QList<QTableWidgetItem *> QTableSortWidget::itemsInARow(int row){
	QList<QTableWidgetItem*> rowItems;
	for (int col = 0; col < columnCount(); col++){
		rowItems << item(row, col);
	}
	return rowItems;
}

QList<QTableWidgetItem*> QTableSortWidget::takeRow(int row){
	QList<QTableWidgetItem*> rowItems;
	for (int col = 0; col < columnCount(); col++){
		rowItems << takeItem(row, col);
	}
	return rowItems;
}

void QTableSortWidget::setRow(int row, const QList<QTableWidgetItem*>& rowItems){
	for (int col = 0; col < columnCount(); col++){
		setItem(row, col, rowItems.at(col));
	}
}

/**
 * @brief QTableSortWidget::copyToClipBoard копирует выделенные строки таблицы в буфер обмена приложения
 */
void QTableSortWidget::copyToClipBoard(){
	QString cbStr;
	QClipboard *cb = QApplication::clipboard();
    cb->clear();
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
    cb->clear();
    cb->setText( cbStr );
}

void QTableSortWidget::showFindPopup(){
    if (searchDialogCreated) return;

    DEBUG_OUT_EX("Find dialog created\n");

    QDialog* dialog = new QDialog(this);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::FramelessWindowHint);
    QVBoxLayout* lay = new QVBoxLayout(dialog);
    QLineEdit* leFind = new QLineEdit(dialog);
    QLabel* label = new QLabel("Введите фильтр или пустую строку,\n"
                               "чтобы показать все записи:", dialog);
    leFind->setText(lastSearchString);
    lay->addWidget(label);
    lay->addWidget(leFind);

    connect(leFind, &QLineEdit::editingFinished, [this]{this->searchDialogCreated = false;});
    connect(leFind, &QLineEdit::editingFinished, dialog, &QDialog::close);
    connect(leFind, &QLineEdit::editingFinished, dialog, &QDialog::deleteLater);
    connect(leFind, &QLineEdit::textChanged, this,  &QTableSortWidget::find);

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
    searchDialogCreated = true;
}


void QTableSortWidget::keyPressEvent(QKeyEvent *ke){
    if (ke->matches(QKeySequence::Copy)){
        //copy
        copyToClipBoard();
    }
    else if (ke->key() == Qt::Key_F && ke->modifiers() == Qt::CTRL){
        showFindPopup();
    }
    else if (ke->key() == Qt::Key_Escape){
        clearSelection();
    }
    else if (ke->matches(QKeySequence::SelectAll)){
        this->selectAll();
    }
}

void QTableSortWidget::swapFunction(int rowAindex, int rowBindex){
    for(int col = 0; col < this->columnCount(); col++){
        QTableWidgetItem* itemA = this->takeItem(rowAindex, col);
        QTableWidgetItem* itemB = this->takeItem(rowBindex, col);
        this->setItem(rowAindex, col, itemB);
        this->setItem(rowBindex, col, itemA);
    }
}

bool QTableSortWidget::cmpDir(QTableWidgetItem *i1,
                              QTableWidgetItem *i2,
                              QTableSortWidget::sortFunctionType cmp,
                              int column){
    if (sortDirections[column] == less){
        return cmp(i1, i2);
    }
    else{
        return !cmp(i1,i2);
    }
}
