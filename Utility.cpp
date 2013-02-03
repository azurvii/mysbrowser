/*
 * Utility.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: vincent
 */

#include "Utility.h"
#include <QtGui>
#include <QtSql>
#include <QWebFrame>

Utility *Utility::instance = 0;
QString Utility::dbLocation;
const QString Utility::pageTableName = "page_store";

Utility * Utility::getInstance() {
	if (!instance) {
		QDir().mkdir(
				QDesktopServices::storageLocation(
						QDesktopServices::DataLocation));
		dbLocation = QDesktopServices::storageLocation(
				QDesktopServices::DataLocation) + QDir::separator()
				+ "store.db";
		instance = new Utility();
	}
	return instance;
}

Utility::Utility(QObject *parent) :
		QObject(parent) {
	initDB();
}

Utility::~Utility() {
	killDB();
}

void Utility::saveFrame(const QWebPage &page) {
	insertTable(pageTableName, page.mainFrame()->url().toString(),
			page.mainFrame()->toHtml());
}

void Utility::initDB() {
	if (!db.isOpen()) {
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName(dbLocation);
		if (!db.open()) {
			log(tr("Failed to open database \"%1\"!").arg(dbLocation));
			killDB();
			exit(1);
		} else {
			log(tr("Successfully opened database \"%1\"!").arg(dbLocation));
		}
		QHash<QString, QString> scheme;
		scheme["url"] = "TEXT";
		scheme["html"] = "BLOB";
		scheme["timestamp"] = "INTEGER";
		createTable(pageTableName, scheme);
	}
}

void Utility::insertTable(const QString &tableName, const QString &url,
		const QString &html) {
	QSqlQuery q(db);
	q.prepare(QString("INSERT INTO \"%1\" "
			"(\"url\", \"html\", \"timestamp\") "
			"VALUES (:url, :html, :timestamp)").arg(tableName));
	q.bindValue(":url", url);
	q.bindValue(":html", html);
	q.bindValue(":timestamp", QDateTime::currentDateTime());
	if (!q.exec()) {
		logLastSqlError();
	}
}

void Utility::createTable(const QString &tableName,
		const QHash<QString, QString> &tableScheme) {
	log(tr("CREATE TABLE IF NOT EXISTS %1").arg(pageTableName));
	QString scheme;
	QHashIterator<QString, QString> i(tableScheme);
	while (i.hasNext()) {
		i.next();
		scheme += ", \"" + i.key() + "\" " + i.value();
	}
	QSqlQuery q(db);
	q.prepare(
			QString("CREATE TABLE IF NOT EXISTS %1 "
					"(\"id\" INTEGER PRIMARY KEY AUTOINCREMENT %2)").arg(
					tableName).arg(scheme));
	if (!q.exec()) {
		logLastSqlError();
	}
}

void Utility::killDB() {
	log(tr("Closing database \"%1\"!").arg(dbLocation));
	db.close();
}

void Utility::log(const QString &message) {
	qDebug() << message;
}

void Utility::logLastSqlError() {
	log(db.lastError().text());
}

QList<PageRecord> Utility::getPageList() {
	QSqlQuery q(getInstance()->db);
	q.prepare(QString("SELECT \"url\", \"html\" FROM %1").arg(pageTableName));
	if (!q.exec()) {
		logLastSqlError();
		return QList<PageRecord>();
	} else {
		QList<PageRecord> pageList;
		while (q.next()) {
			PageRecord page;
			page.setUrl(q.value(0).toString());
			page.setHtml(q.value(1).toString());
			pageList.append(page);
		}
		return pageList;
	}
}
