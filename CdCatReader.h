// CdCatReader.h - IReader implementation for parsing CD catalogues.
#pragma once
#include <QSharedPointer>
#include <memory>
#include <map>

#include "ireader.h"


// forward 
class QXmlStreamReader;
class QString;
class HtmlWriter;
// 

class CdCatReader :
	public IReader
{
public:
	
	CdCatReader();
	
	virtual void read(QIODevice *device);
	virtual void findCDs();

	// BEGIN xml element reader functions
	virtual void readCD();
	virtual void readField();
	//virtual void readArtist();
	//virtual void readCompany();
	//virtual void readPrice();
	//virtual void readYear();
	// END xml element reader functions

	//virtual QSharedPointer<QString> htmlText() const; // a chunk of generated html text
	virtual QTextStream& output();


	virtual ~CdCatReader(void);
protected:
	std::auto_ptr<QFile> _htmlFile; // keep at top
	//QSharedPointer<QString> _htmlText; //html is shared with it's user, no need to deref on return
	QXmlStreamReader *_xml;
	QSharedPointer<QTextStream> _output; //output and file is hold by CdCatReader but shared with HtmlWriter
	HtmlWriter *_writer;

	typedef void (CdCatReader::*CdCatFunction)();
	std::map<QStringRef, CdCatFunction> _nodeNameToFunc; // a map of node name -> processing function 

private:
	bool fitsBuffer();
	CdCatReader( CdCatReader& ); // for now restrict copying and other stuff
	CdCatReader& operator = ( CdCatReader&);
	void TODO_FUNC(); //debug purposes;
};


class CdReaderException : public std::logic_error
{
};
