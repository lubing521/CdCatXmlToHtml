#pragma once
#include <QString>
#include <QTextStream>
#include <QSharedPointer>

class HtmlWriter
{
public:
	HtmlWriter(QSharedPointer<QTextStream> stream); 

	void MakeHtmlCDElementRow(const QString& elementText)
	{
		QString row("<tr>");
		row.append(elementText);
		row.append("</tr>");
		(*_stream.data()) << row;
	}
	void BeginDoc();
	void EndDoc();
	void CdHead();
	void CdTail();
	void Field(const QString& tagName, const QString& value);

	~HtmlWriter(void);
private:
	QSharedPointer<QTextStream> _stream;
	qint64 _cdNumber;
};

