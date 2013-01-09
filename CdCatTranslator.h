// CdCatReader.h - IReader implementation for parsing CD catalogues.
#pragma once
#include <QSharedPointer>
#include <memory>
#include <map>

#include "ITranslator.h"


// forward 
class QXmlStreamReader;
class QString;
class HtmlWriter;
// 
namespace Translator
{

class CdCatTranslator :
	public ITranslator
{
public:	
	CdCatTranslator();	
	virtual void translate(QIODevice *device, const QString& outputFileName);
	virtual void findCDs();
	virtual void readCD();
	virtual QTextStream& output();
	virtual ~CdCatTranslator(void);

protected:
	std::auto_ptr<QFile> _htmlFile; // keep at top
	std::auto_ptr<QXmlStreamReader> _xml;
	QSharedPointer<QTextStream> _output; //output and file is shared with HtmlWriter
	std::auto_ptr<HtmlWriter> _writer;

private:
	CdCatTranslator( CdCatTranslator& ); // for now restrict copying and assigning
	CdCatTranslator& operator = ( CdCatTranslator&);
	void TODO_FUNC(); //debug purposes;
	void InitStream(const QString& outputFileName);
};


class CdReaderException : public std::logic_error
{
};

} //namespace Translator