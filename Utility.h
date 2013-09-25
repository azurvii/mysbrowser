/*
 * Utility.h
 *
 *  Created on: Jan 31, 2013
 *      Author: vincent
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <QObject>
#include <QWebPage>
#include <QList>
#include <QSqlDatabase>
#include <QHash>
#include <QNetworkAccessManager>
#include "PageRecord.h"

class QTextBrowser;

class Utility: public QObject {
Q_OBJECT
public:
	static Utility *getInstance();
	Utility(QObject *parent = 0);
	virtual ~Utility();
	void log(const QString &message);
	QList<PageRecord> getPageList();
	QNetworkAccessManager *getCrawlman();
	bool hasUrl(const QString &url);

public:
	void savePage(const QWebPage &frame);
	void createTable(const QString &tableName,
			const QHash<QString, QString> &tableScheme);
	void insertTable(const QString &tableName, const QString &url,
			const QByteArray &html);
	void savePage(const QString &url, const QByteArray &data);

private:
	void initDB();
	void killDB();
	void logLastSqlError();

private:
	static Utility *instance;
	static QString dbLocation;
	static const QString pageTableName;
	QSqlDatabase db;
	QNetworkAccessManager crawlman;
};

#endif /* UTILITY_H_ */
