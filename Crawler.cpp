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
		QThread(parent) {
	crawlman = 0;
}

Crawler::Crawler(const QString &startUrl) :
		startUrl(startUrl) {
	Crawler();
}

Crawler::~Crawler() {
}

void Crawler::crawl() {
	if (!startUrl.isEmpty()) {
		crawl(startUrl);
		emit finished(true);
	}
	emit finished(false);
}

void Crawler::run() {
	crawlman = new QNetworkAccessManager;
	connect(crawlman, SIGNAL(finished(QNetworkReply*)),
			SLOT(getReply(QNetworkReply*)));
	crawl();
	delete crawlman;
	crawlman = 0;
}

void Crawler::setStartUrl(const QString &url) {
	startUrl = url;
}

void Crawler::getReply(QNetworkReply* reply) {
	QByteArray data = reply->readAll();
	Utility::getInstance()->savePage(reply->url().toString(), data);
	reply->deleteLater();
	foreach(QString url, parseForUrls(data)) {
		crawl(url);
	}
}

void Crawler::crawl(const QString& url) {
	crawlman->get(QNetworkRequest(url));
}

QStringList Crawler::parseForUrls(const QByteArray &data) {
	QWebPage page;
	page.mainFrame()->setHtml(data);
	QStringList results;
	foreach (QWebElement e, page.mainFrame()->findAllElements("a")) {
		QString url = e.attribute("href");
		if (!url.isEmpty()) {
			results.append(url);
		}
	}
	return results;
}

