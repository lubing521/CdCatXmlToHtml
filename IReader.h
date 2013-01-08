#pragma once

#include <QSharedPointer>

class QIODevice;
class QString;
class QTextStream;

class IReader
{
public:
	/*IReader(void);*/
	virtual void read(QIODevice *device) = 0; 
	virtual QSharedPointer<QString> htmlText() const = 0; // a chunk of generated html text
	virtual QTextStream& output();
	virtual bool isFull() const = 0; // buffer is full
	virtual ~IReader(void);
};

