/*
 * PageRecord.h
 *
 *  Created on: Feb 3, 2013
 *      Author: vincent
 */

#ifndef PAGERECORD_H_
#define PAGERECORD_H_

#include <QString>

class PageRecord {
public:
	PageRecord(QString url = QString(), QString html = QString());

	QString getHtml() const {
		return html;
	}

	void setHtml(QString html) {
		this->html = html;
	}

	QString getUrl() const {
		return url;
	}

	void setUrl(QString url) {
		this->url = url;
	}

private:
	QString url;
	QString html;
};

#endif /* PAGERECORD_H_ */
