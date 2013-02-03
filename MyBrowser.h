#include "ui_MyBrowser.h"

class DatabaseViewer;

class MyBrowser: public QWidget {
Q_OBJECT
public:
	MyBrowser(QWidget *parent = 0);

public slots:
	void on_lineEdit_returnPressed();
	void on_webView_urlChanged(const QUrl &url);
	void on_homeButton_clicked();
	void on_webView_loadFinished(bool ok);
	void on_webView_loadStarted();
	void on_linksView_itemActivated(QListWidgetItem *item);
	void on_imagesView_itemActivated(QListWidgetItem *item);
	void on_viewDBButton_clicked();
	void on_savePageButton_clicked();

private:
	QString noTrailingSlash(const QString &url);

private:
	Ui::MyBrowser ui;
	DatabaseViewer *dbViewer;
};

