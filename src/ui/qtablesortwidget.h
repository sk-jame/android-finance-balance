#ifndef QTABLESORTWIDGET_H
#define QTABLESORTWIDGET_H

#include <QTableWidget>

class QTableSortWidget : public QTableWidget
{
	Q_OBJECT
public:
	typedef void (*ConvertFunction)(QTableWidgetItem* item);

	enum ESortType{
		sort_float,
		sort_hex,
		sort_strings
	};

	QTableSortWidget(QWidget *parent = Q_NULLPTR);
	QTableSortWidget(int rows, int columns, QWidget *parent = Q_NULLPTR);

	QList<QTableWidgetItem *> itemsInARow(int row);
	QList<QTableWidgetItem *> takeRow(int row);
	void setRow(int row, const QList<QTableWidgetItem *> &rowItems);
protected:
		// Declare typedef
	typedef bool (*sortFunctionType)(QTableWidgetItem* item1, QTableWidgetItem* item2);

	enum ESortDirection{
		less,
		greater
	};

	QVector<ESortDirection> sortDirections;
	QList<ESortType> sortTypeList;

    bool searchDialogCreated;
    QString lastSearchString;
public slots:
	virtual void setSortType(int col, QTableSortWidget::ESortType type);
	virtual void convertColumnValue(int col, ConvertFunction func);
protected slots:
	virtual void sortColumn(int num);
    virtual void find(QString searchStr);
	// QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *ke);

    void copyToClipBoard();
    void showFindPopup();

    inline void swapFunction(int rowAindex, int rowBindex);
    inline bool cmpDir(QTableWidgetItem* i1, QTableWidgetItem* i2, sortFunctionType cmp, int column);
};





#endif // QTABLESORTWIDGET_H
