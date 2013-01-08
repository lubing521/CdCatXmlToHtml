// CdCatReader.h - IReader implementation for parsing CD catalogues.
#pragma once
#include <QSharedPointer>
#include <memory>
#include <map>

#include "ireader.h"


// forward classes declarations
class QXmlStreamReader;
class QString;
class HtmlWriter;
//class QTextOStream;
// 

class CdCatReader :
	public IReader
{
public:
	static const size_t BufferSize = 64; // the amount of memory we want to use in bytes
	
	CdCatReader();
	
	virtual void read(QIODevice *device);
	virtual void readCdCat();

	// BEGIN xml element reader functions
	virtual void readCD();
	virtual void readTitle();
	virtual void readArtist();
	virtual void readCompany();
	virtual void readPrice();
	virtual void readYear();
	// END xml element reader functions

	virtual QSharedPointer<QString> htmlText() const; // a chunk of generated html text
	virtual bool isFull() const; // buffer is full
	virtual QTextStream& output();


	virtual ~CdCatReader(void);
protected:
	typedef void (CdCatReader::*CdCatFunction)(); // function pointer type

	QSharedPointer<QString> _htmlText; //html is shared with it's user, no need to deref on return
	QXmlStreamReader *_xml;
	QSharedPointer<QTextStream> _output; //output and file is hold by CdCatReader but shared with HtmlWriter
	std::auto_ptr<QFile> _htmlFile;
	HtmlWriter *_writer;
	std::map<QStringRef, CdCatFunction> _nodeNameToFunc; // a map of node name -> processing function 
	bool _isFull;
private:
	bool fitsBuffer();
	CdCatReader( CdCatReader& ); // for now restrict copying and other stuff
	CdCatReader& operator = ( CdCatReader&);
	void TODO_FUNC(); //debug purposes;
};


class CdReaderException : public std::logic_error
{
};
