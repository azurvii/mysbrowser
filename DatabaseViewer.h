/*
 * DatabaseViewer.h
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#ifndef DATABASEVIEWER_H_
#define DATABASEVIEWER_H_

#include "build/ui_DatabaseViewer.h"
#include <QList>
#include <QWebPage>
#include "PageRecord.h"

class DatabaseViewer: public QDialog {
Q_OBJECT
public:
	DatabaseViewer(QWidget *parent = 0);
	virtual ~DatabaseViewer();

public slots:
	void on_refreshButton_clicked();
	void on_pageList_currentItemChanged(QListWidgetItem * current,
			QListWidgetItem *);
	void on_lineWrapCheck_clicked(bool wrap);

private:
	void loadList();

private:
	Ui::DatabaseViewer ui;
	QList<PageRecord> pageList;
};

#endif /* DATABASEVIEWER_H_ */
