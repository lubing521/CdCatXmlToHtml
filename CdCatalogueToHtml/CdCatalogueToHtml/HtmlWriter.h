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
	void  MakeBeginTable()
	{
		(*_stream.data()) << "<table>";
	}
	void MakeEndTable()
	{
		(*_stream.data()) << "</table>";
	}
	~HtmlWriter(void);
private:
	QSharedPointer<QTextStream> _stream;
};

