#include "HtmlWriter.h"

HtmlWriter::HtmlWriter(QSharedPointer<QTextStream> stream) : _stream(stream), _cdNumber(1)
{
}

HtmlWriter::~HtmlWriter(void)
{
}

void HtmlWriter::BeginDoc()
{
	// would be a correct XHMTML 1.0 document
	(*_stream.data()) <<
		"<html>\
		<head>\
		<title>My Lovely Catalogue</title>\
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\
		<meta http-equiv=\"Content-Style-Type\" content=\"text/css\" />\
		</head>\
		<body>\
		<table style=\"width: 100%;\" border=\"1\">";
}

void HtmlWriter::EndDoc()
{
	(*_stream.data()) <<
		"</table>\
		</body>\
		</html>";
}

void HtmlWriter::CdHead()
{
	(*_stream.data()) <<
		"<tr>\
		<td> CD " <<
		_cdNumber++ <<
		"</td>\
		<td>\
		<table border=\"1\" >";
}

void HtmlWriter::CdTail()
{
	(*_stream.data()) <<
		"</table>\
		</td>\
		</tr>";
}

void HtmlWriter::Field(const QStringRef tagName, const QString& value)
{
	(*_stream.data()) <<
		"<tr>\
		<td>" <<
		tagName.toString() <<
		"</td>\
		<td style=\"width: 100%;\">" <<
		value <<
		"</td>\
		</tr>";
}