/*
 * MarcRecord.h
 *
 *  Created on: 3-dic-2008
 *      Author: Arge
 */

#ifndef MARCRECORD_H_
#define MARCRECORD_H_
#include "library/CString.h"
#include "library/tvvector.h"
#include "Leader.h"
#include "ControlField.h"
#include "DataField.h"


class MarcRecord {
private:
	long id;
	Leader *leader;
	ATTValVector<ControlField*> *controlFieldsVector;
	ATTValVector<DataField*> *dataFieldsVector;
	CString type;
	CString stringed;
	void init();
	void stop();

public:
	MarcRecord();
	virtual ~MarcRecord();

	long getId() const;
    void setId(long id);
    Leader *getLeader() const;
    void setLeader(Leader *leader);
    ATTValVector<ControlField*> *getControlFieldsVector() const;
    void setControlFieldsVector(ATTValVector<ControlField*> *controlFieldsVector);
    ATTValVector<DataField*> * getDataFieldsVector() const;
    void setDataFieldsVector(ATTValVector<DataField*> *dataFieldsVector);
    char* getType();
    void setType(char* type);
    void clear();
    void addControlField(ControlField* cf);
    void addDataField(DataField* df);
    char *toString();
    CString *toCString();
    long toStringLength();
    char *toXml();
    long toXmlLength();

    void sortDataFields();
    int existsDataField(int anId) const;
    int removeDataFields(int anId) const;
;

};

#endif /* MARCRECORD_H_ */
