/*
 * DataField.h
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#ifndef DATAFIELD_H_
#define DATAFIELD_H_
#include "library/tvvector.h"
#include "library/CString.h"

#include "Embedded.h"
#include "Subfield.h"

class DataField {

private:
	int tagId;
	CString tag;
	char indicator1;
	char indicator2;
	ATTValVector <Subfield *> *subfieldsVector;
	CString stringed;

	void stop();

public:
//	ATTValVector <Embedded *> *embeddedVector;
	Embedded *embedded;

	DataField();
	DataField(char* tag, int len);
	DataField(char* tag, char ind1, char ind2);
	DataField(CString* tag, char ind1, char ind2);
	virtual ~DataField();
	void setIndicator1(char ind1);
	char getIndicator1();
	void setIndicator2(char ind2);
	char getIndicator2();
	void addSubfield(Subfield *subfield);
	ATTValVector<Subfield*> * getSubfields();
	ATTValVector <Subfield *> * getSubfields(char code);
	Subfield *getSubfield(char code);

	int getId();
//    void setId(long  id);
    bool find(char* pattern);
    char* toString();
    CString * toCString(char *recId);
    char* toXml(int indent);
    CString* toCStringXml(int indent);

    CString* toSubTag();
    long getToXmlLength();

    //char* getTag();
    CString *getTagString();
    void setTag(char* tag);
//    ATTValVector<Subfield*> *getSubfieldsVector(); //  const
    void setSubfieldsVector(ATTValVector<Subfield*> *subfieldsVector);
    void removeSubfield(char code);
	bool setDataField(DataField* aDf);
	void dump();

};

#endif /* DATAFIELD_H_ */
