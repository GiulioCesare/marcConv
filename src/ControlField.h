/*
 * ControlField.h
 *
 * Control fields go from 001 to 009
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#ifndef CONTROLFIELD_H_
#define CONTROLFIELD_H_
#include "library/CString.h"

class ControlField {

private:
	long id;
	CString data;
	CString tag;
	CString stringed;

public:
	ControlField();
	ControlField(char *tag);
	ControlField(char* tag, char* data);
	virtual ~ControlField();
	char *toString();
	CString* toCString();

	char *toXml(int indent);
	CString* toCStringXml(int indent);

	void setId(long id);
	long getId();
	void setTag(char * tag);
	void setTag(CString * tag);
	char *getTag();
	void setData(char* data, int len);
	void setData(CString * data);
	//char * getData();
	CString * getData();

	long getToXmlLength();
	bool find(char* pattern);

};

#endif /* CONTROLFIELD_H_ */
