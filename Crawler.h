/*
 * Crawler.h
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#ifndef CRAWLER_H_
#define CRAWLER_H_

#include <QObject>
#include <QNetworkReply>
#include "Utility.h"

class Crawler: public QObject {
Q_OBJECT
public:
	Crawler(QObject *parent = 0);
	Crawler(const QString &startUrl);
	virtual ~Crawler();
	void setStartUrl(const QString &url);

public slots:
	void start();
	void getReply(QNetworkReply* reply);
	bool isUpdateMode() const;
	void setUpdateMode(bool updateMode);

private:
	void crawl(const QString &url);
	QStringList parseForUrls(const QByteArray &data, const QString &baseUrl);

private:
	QString startUrl;
	bool updateMode;
};

#endif /* CRAWLER_H_ */
