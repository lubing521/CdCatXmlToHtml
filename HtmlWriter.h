#pragma once
#include <QString>
#include <QTextStream>
#include <QSharedPointer>

class HtmlWriter
{
public:
	HtmlWriter(QSharedPointer<QTextStream> stream); 

	void BeginDoc();
	void EndDoc();
	void CdHead();
	void CdTail();
	void Field(const QStringRef tagName, const QString& value);

	~HtmlWriter(void);
private:
	HtmlWriter(HtmlWriter &);
	HtmlWriter & operator = (const HtmlWriter & other);
	QSharedPointer<QTextStream> _stream;
	qint64 _cdNumber;
};

