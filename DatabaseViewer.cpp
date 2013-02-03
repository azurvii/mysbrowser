/*
 * DatabaseViewer.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#include "DatabaseViewer.h"
#include "Utility.h"
#include <QWebFrame>

DatabaseViewer::DatabaseViewer(QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);
}

DatabaseViewer::~DatabaseViewer() {
}

void DatabaseViewer::on_refreshButton_clicked() {
	loadList();
}

void DatabaseViewer::loadList() {
	pageList = Utility::getInstance()->getPageList();
	ui.pageList->clear();
	for (int i = 0; i < pageList.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem;
		item->setData(Qt::DisplayRole, pageList[i].getUrl());
		item->setData(Qt::UserRole, i);
		ui.pageList->addItem(item);
	}
}

void DatabaseViewer::on_pageList_currentItemChanged(QListWidgetItem * current,
		QListWidgetItem *) {
	ui.textBrowser->setPlainText(
			pageList[current->data(Qt::UserRole).toInt()].getHtml());
}

void DatabaseViewer::on_lineWrapCheck_clicked(bool wrap) {
	ui.textBrowser->setLineWrapMode(
			wrap ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
}
