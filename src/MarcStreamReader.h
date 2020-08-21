/*
 * MarcStreamReader.h
 *
 *  Created on: 8-dic-2008
 *      Author: Arge
 */

#ifndef MARCSTREAMREADER_H_
#define MARCSTREAMREADER_H_

#include "MarcRecord.h"
#include "Leader.h"
#include "library/CFile.h"

#define MAX_FIELD_LENGTH 9999
#define MAX_SUBFIELD_LENGTH 9999

class MarcStreamReader {
private:
	class DirectoryEntry
	{
	public:
		DirectoryEntry(){};
		CString tag;
		int 	length;
		int 	start;
	};

	CFile *in;
    CString encoding;
    MarcRecord *record;
//    Leader *ldr;
    unsigned char readBuffer[MAX_FIELD_LENGTH+2+2+1]; // +2 indicators +$ + subfieldId + EOS
    unsigned char subfieldBuffer[MAX_FIELD_LENGTH+1]; // + EOS


	ATTValVector <DirectoryEntry *> *directoryEntries;

    DataField *parseDataField(char* tag); // byte[] field
    void parseLeader(unsigned char* leaderData); // byte[] leaderData
    char *getDataAsString(unsigned char*); // byte[] bytes
    bool isControlField(char* tag);
    bool isControlNumberField(char* tag);
    int getSubfield(int pos);
    void init();

public:
	MarcStreamReader();
	MarcStreamReader(CFile *in);
	MarcStreamReader(CFile *in, char * encoding);
	bool hasNext();
	MarcRecord* next();
	~MarcStreamReader();

};


#endif /* MARCSTREAMREADER_H_ */
