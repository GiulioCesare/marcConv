/*
 * DocOfflineExport.h
 *
 *  Created on: Feb 2, 2011
 *      Author: export
 */

#ifndef DOCOFFLINEEXPORT_H_
#define DOCOFFLINEEXPORT_H_

#include "library/CFile.h"
#include "library/CString.h"
#include "library/GenericError.h"
#include "library/CKeyValueVector.h"


class DocOfflineExport {
	CFile *cFileIn;
	CFile *cFileOut;
	CKeyValueVector *tagsKV, *tocKV;

	void elaboraFile();
	void scriviDocumentazione();
	void scriviTag(int i);
public:
	DocOfflineExport();
	virtual ~DocOfflineExport();
	void makeDocumentation();

};

#endif /* DOCOFFLINEEXPORT_H_ */
