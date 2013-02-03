/*
 * Crawler.h
 *
 *  Created on: Feb 2, 2013
 *      Author: vincent
 */

#ifndef CRAWLER_H_
#define CRAWLER_H_

#include <QObject>

class Crawler: public QObject {
	Q_OBJECT
public:
	Crawler(QObject *parent = 0);
	virtual ~Crawler();
};

#endif /* CRAWLER_H_ */
