#include "ui_MyBrowser.h"

class MyBrowser : public QWidget {
Q_OBJECT
public:
	MyBrowser(QWidget *parent = 0);

public slots:
	void on_lineEdit_returnPressed();
	void on_webView_urlChanged(const QUrl &url);
	void on_homeButton_clicked();
	void on_webView_loadFinished(bool ok);
	void on_webView_loadStarted();
	void on_linksView_itemActivated(QListWidgetItem* item);

private:
	Ui::MyBrowser ui;
};

