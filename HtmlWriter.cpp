#include "HtmlWriter.h"


HtmlWriter::HtmlWriter(QSharedPointer<QTextStream> stream) : _stream(stream)
{
}


HtmlWriter::~HtmlWriter(void)
{
}
void HtmlWriter::BeginDoc()
{
	// would be correct XHMTML 1.0 document
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
            <td> nbsp; CD " <<
                _cdNumber++ <<
            "</td>\
            <td>\
                <table border=\"1\" style=\"width: 100%;\">";
}
void HtmlWriter::CdTail()
{
	(*_stream.data()) <<
		"</table>\
            </td>\
        </tr>";
}
void HtmlWriter::Field(const QString& tagName, const QString& value)
{
	(*_stream.data()) <<
	"<tr>\
	<td>" <<
		tagName <<
		"</td>\
		<td>" <<
		value <<
		"</td>\
		</tr>";
}