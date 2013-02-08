#include "MyBrowser.h"
#include <QtWebKit>
#include "DatabaseViewer.h"
#include "Utility.h"
#include "Crawler.h"

MyBrowser::MyBrowser(QWidget *parent) :
		QWidget(parent), updateMode(false) {
	threadCount = 0;
	ui.setupUi(this);
	ui.webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	ui.webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,
			true);
	ui.homeButton->click();
	ui.webInspector->setPage(ui.webView->page());
	dbViewer = new DatabaseViewer(this);
	Utility::getInstance()->setLogBrowser(ui.logBrowser);
}

void MyBrowser::on_urlEdit_returnPressed() {
	if (!ui.urlEdit->text().contains("://")) {
		ui.urlEdit->setText("http://" + ui.urlEdit->text());
	}
	ui.webView->load(QUrl(ui.urlEdit->text()));
}

void MyBrowser::on_webView_urlChanged(const QUrl &url) {
	ui.urlEdit->setText(url.toString());
}

void MyBrowser::on_homeButton_clicked() {
	ui.webView->load(QUrl("https://www.google.com/ncr"));
}

void MyBrowser::on_webView_loadFinished(bool ok) {
	if (ok) {
		ui.linksView->clear();
		ui.imagesView->clear();
		QUrl baseUrl = ui.webView->url();
		QString noSlashEnding = baseUrl.toString();
		if (noSlashEnding.endsWith("/")) {
			ui.linksView->addItem(noSlashEnding.left(noSlashEnding.size() - 1));
		} else {
			ui.linksView->addItem(noSlashEnding);
		}
		QWebElementCollection ec =
				ui.webView->page()->mainFrame()->findAllElements("a");
		foreach (QWebElement e, ec) {
			QString href = e.attribute("href");
			QString absHref = baseUrl.resolved(QUrl(href)).toString();
			if (ui.linksView->findItems(noTrailingSlash(absHref),
					Qt::MatchExactly).size() == 0) {
				ui.linksView->addItem(absHref);
			}
		}
		ec = ui.webView->page()->mainFrame()->findAllElements("img");
		foreach (QWebElement e, ec) {
			QString href = e.attribute("src");
			QString absHref = baseUrl.resolved(QUrl(href)).toString();
			if (ui.imagesView->findItems(noTrailingSlash(absHref),
					Qt::MatchExactly).size() == 0) {
				ui.imagesView->addItem(absHref);
			}
		}
	}
}

void MyBrowser::on_webView_loadStarted() {
	ui.linksView->clear();
	ui.imagesView->clear();
}

void MyBrowser::on_linksView_itemActivated(QListWidgetItem *item) {
	ui.webView->load(QUrl(item->text()));
}

void MyBrowser::on_imagesView_itemActivated(QListWidgetItem *item) {
	ui.webView->load(QUrl(item->text()));
}

void MyBrowser::on_viewDBButton_clicked() {
	dbViewer->show();
	dbViewer->raise();
	dbViewer->setFocus();
}

void MyBrowser::on_savePageButton_clicked() {
	Utility::getInstance()->savePage(*ui.webView->page());
}

void MyBrowser::on_crawlButton_clicked() {
	if (!crawler) {
		crawler = new Crawler(ui.webView->url().toString());
	}
	crawler->start();
}

QString MyBrowser::noTrailingSlash(const QString &url) {
	if (url.endsWith("/")) {
		return url.left(url.size() - 1);
	} else {
		return url;
	}
}

void MyBrowser::on_testButton_clicked() {
	log(Utility::getInstance()->hasUrl(ui.urlEdit->text()));
}

void MyBrowser::on_updateModeCheck_toggled(bool updateMode) {
	setUpdateMode(updateMode);
}

bool MyBrowser::isUpdateMode() const {
	return updateMode;
}

void MyBrowser::setUpdateMode(bool updateMode) {
	this->updateMode = updateMode;
	if (crawler) {
		crawler->setUpdateMode(updateMode);
	}
}
