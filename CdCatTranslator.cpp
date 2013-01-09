// CdCatReader.cpp - IReader implementation for parsing CD catalogues.
#include <vector>
#include <QString>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QFile>
#include "HtmlWriter.h"
#include "CdCatTranslator.h"
#include <iostream>
#include "Messenger.h" // should use pointer to interface etc, but won't add more files for now...

namespace Translator
{
	namespace // private constants
	{
		static const QString rootElementName = "CATALOG";
		const QString tags[] = {"TITLE","ARTIST","COMPANY", "COUNTRY", "PRICE", "YEAR"};
		std::vector<QString> vtags (tags, tags + (sizeof tags / sizeof tags[0]));
	}

CdCatTranslator::CdCatTranslator(void) 
{
	_xml = std::auto_ptr<QXmlStreamReader>(new QXmlStreamReader());	
	// Most desktop operating systems overcommit memory. This means that malloc() or operator new return a valid pointer,
	//	even though there is not enough memory available at allocation time. On such systems, no exception of type std::bad_alloc is thrown. - Qt4 doc
}

QTextStream& CdCatTranslator::output()
{
	return *_output;
}

void CdCatTranslator::InitStream( const QString& outputFileName)
{
	// Most desktop operating systems overcommit memory. This means that malloc() or operator new return a valid pointer,
	//	even though there is not enough memory available at allocation time. On such systems, no exception of type std::bad_alloc is thrown. - Qt4 doc
	_htmlFile = std::auto_ptr < QFile > (new QFile(outputFileName)); //TODO: init from argv[2]
	if (_htmlFile->open(QFile::WriteOnly | QFile::Truncate)) {
		_output = QSharedPointer<QTextStream>(new QTextStream(_htmlFile.get()));
		_writer = std::auto_ptr < HtmlWriter > (new HtmlWriter(_output));
	}
}

void CdCatTranslator::translate(QIODevice *device, const QString& outputFileName)
{
	Messenger messenger;

	InitStream(outputFileName);
	bool began = false;
	_xml->setDevice(device);

	 while (_xml->readNextStartElement())
	 {
        if (_xml->name() == rootElementName ) //check whether it's our file
		{
			_writer->BeginDoc();
			began = true;
            findCDs(); //start processing
		}
        else
			_xml->skipCurrentElement();
	 }
	 if (!began)
	 {
		 _xml->raiseError(QObject::tr("The file is not an CD Catalog file."));
		 messenger.WrongFormat(_xml->errorString().toLocal8Bit().constData());
	 }
	 else
	 {
		 _writer->EndDoc();
		 messenger.Finished(outputFileName.toLocal8Bit().constData());
	 }
}

void CdCatTranslator::findCDs()
{
	while (_xml->readNextStartElement()) // read every cd and skip all in between
        _xml->name() == "CD" ? readCD() : _xml->skipCurrentElement();
}
void CdCatTranslator::readCD()
{
	Q_ASSERT(_xml->name() == "CD"); 	
	_writer->CdHead();

	while (_xml->readNextStartElement()) // raead fields (artist, album...)
	{
		if(std::find(vtags.begin(), vtags.end(), _xml->name().toString()) != vtags.end()) 
			_writer->Field(_xml->name(), _xml->readElementText()); 
		else
			_xml->skipCurrentElement();
	}
	_writer->CdTail();
}

CdCatTranslator::~CdCatTranslator(void)
{
}

} // namespace Translator
