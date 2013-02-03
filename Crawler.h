/*
 * Crawler.h
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#ifndef CRAWLER_H_
#define CRAWLER_H_

#include <QObject>
#include <QThread>
#include <QNetworkReply>
#include "Utility.h"

class Crawler: public QThread {
Q_OBJECT
public:
	Crawler(QObject *parent = 0);
	Crawler(const QString &startUrl);
	virtual ~Crawler();

public slots:
	void crawl();
	void setStartUrl(const QString &url);
	void getReply(QNetworkReply *reply);

signals:
	void finished(bool successful);
	void startCrawling(const QString &url);

protected:
	void run();

private:
	void crawl(const QString &url);
	QStringList parseForUrls(const QByteArray &data);

private:
	QString startUrl;
	QNetworkAccessManager *crawlman;
};

#endif /* CRAWLER_H_ */
