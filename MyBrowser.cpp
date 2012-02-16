#include "MyBrowser.h"
#include <QtWebKit>

MyBrowser::MyBrowser(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	ui.webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	ui.homeButton->click();
}

void MyBrowser::on_lineEdit_returnPressed() {
	if (!ui.lineEdit->text().contains("://")) {
		ui.lineEdit->setText("http://" + ui.lineEdit->text());
	}
	ui.webView->load(QUrl(ui.lineEdit->text()));
}

void MyBrowser::on_webView_urlChanged(const QUrl &url) {
	ui.lineEdit->setText(url.toString());
}

void MyBrowser::on_homeButton_clicked() {
	ui.webView->load(QUrl("https://www.google.com"));
}

void MyBrowser::on_webView_loadFinished(bool ok) {
	if (ok) {
		ui.linksView->clear();
		QUrl baseUrl = ui.webView->url();
		QString noSlashEnding = baseUrl.toString();
		if (noSlashEnding.endsWith("/")) {
			ui.linksView->addItem(noSlashEnding.left(noSlashEnding.size() - 1));
		} else {
			ui.linksView->addItem(noSlashEnding);
		}
		QWebElementCollection ec = ui.webView->page()->mainFrame()->findAllElements("a");
		foreach (QWebElement e, ec) {
			QString href = e.attribute("href");
			QString absHref = baseUrl.resolved(QUrl(href)).toString();
			if (absHref.endsWith("/")) {
				absHref = absHref.left(absHref.size() - 1);
			}
			if (ui.linksView->findItems(absHref, Qt::MatchExactly).size() == 0) {
				ui.linksView->addItem(absHref);
			}
		}
	}
}

void MyBrowser::on_webView_loadStarted() {
	ui.linksView->clear();
}

void MyBrowser::on_linksView_itemActivated(QListWidgetItem* item) {
	ui.webView->load(QUrl(item->text()));
}

