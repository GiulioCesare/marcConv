/*
 * MarcStreamWriter.h
 *
 *  Created on: 7-dic-2008
 *      Author: Arge
 */

#ifndef MARCSTREAMWRITER_H_
#define MARCSTREAMWRITER_H_

#include "library/CFile.h"
#include "MarcRecord.h"
#include "library/CBufferedData.h"

class MarcStreamWriter {

private:
    CString encoding;
    char buf[20];


//    void write(Leader *ldr);
	//void getEntry(char* tag, int length, int start, CString &entry);
	//void getDataElement(char * data, CString & dataElement);

protected:
	CFile *out;
    CString *ldrStr;
    CBufferedData *fieldData;
	CBufferedData *recordData;
	CBufferedData *directoryData;

public:

	MarcStreamWriter();
	MarcStreamWriter(CFile * out);
	MarcStreamWriter(CFile *out, char* encoding);

	virtual ~MarcStreamWriter();
	virtual bool write(MarcRecord* marcRecord);
	virtual bool writeStructure(MarcRecord* marcRecord);

	bool writeToFile();
	bool prepareRecordTowrite(MarcRecord* marcRecord);
	long getWriteToFileRecordLength();

	void init();
//	void setConverter(CharConverter converter);
//	CharConverter getConverter();
//	void close();




};

#endif /* MARCSTREAMWRITER_H_ */
