/*
 * ReadMarcExample.cpp
 *
 *  Created on: 10-dic-2008
 *      Author: Arge
 */

#include "ReadMarcExample.h"
#include "MarcStreamReader.h"


ReadMarcExample::ReadMarcExample() {

}

ReadMarcExample::~ReadMarcExample() {
}

void ReadMarcExample::read(char *filename)
{
CFile *in = new CFile(filename, AL_READ_FILE);

MarcStreamReader *marcStreamReader = new MarcStreamReader(in);
MarcRecord *marcRecord;
int ctr = 1;

while (marcStreamReader->hasNext()) {
	marcRecord = marcStreamReader->next();
	if (marcRecord)
		{
		printf("\n\n%s", marcRecord->toCString()->data());
		//printf ("\nRecord %d, bid=%s", ctr, marcRecord->getControlFieldsVector()->Entry(0)->getData()->data());
		}
	else
	{
//		printf ("\nRecord ERRATO %d", ctr);
//		marcRecord->clear();
		break;
	}

//	if (ctr == 1)
//		break;

	ctr++;

}

delete in;
delete marcStreamReader;
}

