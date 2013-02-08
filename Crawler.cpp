/*
 * Crawler.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#include "Crawler.h"
#include <QWebFrame>
#include <QWebPage>
#include <QWebElementCollection>
#include <QWebElement>

Crawler::Crawler(QObject *parent) :
		QObject(parent), updateMode(false) {
}

Crawler::Crawler(const QString &startUrl) :
		startUrl(startUrl) {
	Crawler();
}

Crawler::~Crawler() {
}

void Crawler::start() {
	if (!startUrl.isEmpty()) {
		crawl(startUrl);
	}
}

//void Crawler::run() {
//	crawlman = new QNetworkAccessManager;
//	connect(crawlman, SIGNAL(finished(QNetworkReply*)),
//			SLOT(getReply(QNetworkReply*)));
//	crawl();
//	delete crawlman;
//	crawlman = 0;
//}

void Crawler::setStartUrl(const QString &url) {
	startUrl = url;
}

void Crawler::getReply(QNetworkReply* reply) {
	QByteArray data = reply->readAll();
	Utility::getInstance()->savePage(reply->url().toString(), data);
	reply->deleteLater();
	foreach(QString url, parseForUrls(data, reply->url().toString())) {
		crawl(url);
	}
}

void Crawler::crawl(const QString& url) {
	if (!updateMode && Utility::getInstance()->hasUrl(url)) {
		return;
	}
	Utility::getInstance()->getCrawlman()->get(QNetworkRequest(url));
	connect(Utility::getInstance()->getCrawlman(),
			SIGNAL(finished(QNetworkReply *)),
			SLOT(getReply(QNetworkReply *)));
}

QStringList Crawler::parseForUrls(const QByteArray &data,
		const QString &baseUrl) {
	QWebPage page;
	page.mainFrame()->setHtml(data);
	QStringList results;
	foreach (QWebElement e, page.mainFrame()->findAllElements("a")) {
		QString url = e.attribute("href");
		if (!url.isEmpty()) {
			results.append(QUrl(baseUrl).resolved(url).toString());
		}
	}
	return results;
}

bool Crawler::isUpdateMode() const {
	return updateMode;
}

void Crawler::setUpdateMode(bool updateMode) {
	this->updateMode = updateMode;
}

