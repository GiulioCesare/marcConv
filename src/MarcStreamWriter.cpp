/*
 * MarcStreamWriter.cpp
 *
 *  Created on: 7-dic-2008
 *      Author: Arge
 */

#include <ControlField.h>
#include <DataField.h>
#include <library/tvvector.h>
#include <Leader.h>
#include <MarcConstants.h>
#include <MarcGlobals.h>
#include <MarcStreamWriter.h>
#include <Subfield.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif


MarcStreamWriter::MarcStreamWriter() {
	init();
}


    /**
     * Constructs an instance and creates a <code>Writer</code> object with
     * the specified output stream.
     */
MarcStreamWriter::MarcStreamWriter(CFile * out) {
	init();
    this->out = out;
    encoding = "ISO8859_1";
    }
void MarcStreamWriter::init()
{
	fieldData = new CBufferedData();

	recordData = new CBufferedData();
	directoryData = new CBufferedData();
}

    /**
     * Constructs an instance and creates a <code>Writer</code> object with
     * the specified output stream and character encoding.
     */
MarcStreamWriter::MarcStreamWriter(CFile *out, char* encoding) {
	MarcStreamWriter();
	this->encoding = encoding;
    this->out = out;
    }

MarcStreamWriter::~MarcStreamWriter() {
	if (recordData)
		delete recordData;
	if (directoryData)
		delete directoryData;
	if (fieldData)
		delete fieldData;
}

//	void setConverter(CharConverter converter);
//	CharConverter getConverter();
//void MarcStreamWriter::close()
//{
//}


/**
 * Returns the character converter.
 *
 * @return CharConverter the character converter
 */
/*
  CharConverter MarcStreamWriter::getConverter() {
        return converter;
    }
*/
/**
 * Sets the character converter.
 *
 * @param converter
 *            the character converter
 */
/*
void MarcStreamWriter::setConverter(CharConverter converter) {
        this->converter = converter;
    }
*/








/**
 * Writes a <code>Record</code> object to the writer.
 *
 * @param record -
 *            the <code>Record</code> object
 */
bool MarcStreamWriter::write(MarcRecord* marcRecord) {
	bool retb;


        retb = prepareRecordTowrite(marcRecord);
        if (!retb)
        	return retb;

        return writeToFile();
} // End write






long MarcStreamWriter::getWriteToFileRecordLength() {
	long length = ldrStr->Length();
	length += directoryData->GetUsedBytes();
	length += recordData->GetUsedBytes();
	length ++; // RECORD_TERMINATOR

	if (RECORDUNIMARCSUSINGOLARIGA == 1)
		length ++; // Linefeed

	return length;
}





//void MarcStreamWriter::getDataElement(char * data, CString & dataElement) { //  throws IOException
//	dataElement = data;
//} // End getDataElement


//
//void MarcStreamWriter::getEntry(char* tag, int length, int start, CString &entry) // throws IOException
//	{
//    char buf[20];
//	//return (tag + format4.format(length) + format5.format(start)).getBytes(encoding);
////    sprintf (buf, "%s%04d%05d", tag, length, start);
//
//    //entry= buf;
//    entry.assign (buf, 12);
//	} // End getEntry




bool MarcStreamWriter::prepareRecordTowrite(MarcRecord* marcRecord) {
    long previous = 0;
    const int leaderLength = 24;
    const int directoryEntryLength = 12;

    ControlField *cf;
    DataField *df; //, *df1
    Subfield *sf;
    recordData->Reset();
    directoryData->Reset();
    //CString dataElement; // entry,
    CString directoryEntry;
//    char *bid;
//    char chr;
    CString *sPtr;


    int len;
        // Prepare CONTROL FIELDS
        ATTValVector <ControlField*> *controlFields = marcRecord->getControlFieldsVector();
        for (int i=0;i< controlFields->Length(); i++ )
        {
			cf = controlFields->Entry(i);
//			if (!i)
//				bid = cf->getData()->Data();
			recordData->AddString(cf->getData());
			recordData->AddChar(FIELD_TERMINATOR);

			//getEntry(cf->getTag(), (recordData->GetUsedBytes())- previous, previous, directoryEntry);
			//directoryData->AddString(directoryEntry.Data());

			sprintf (buf, "%3s%04d%05d", cf->getTag(), recordData->GetUsedBytes() - previous, previous);
			//directoryEntry.assign (buf, 12);
			directoryData->AddBinaryData(buf, 12);

			previous = recordData->GetUsedBytes();
        }


        // Prepare DATA FIELDS

        ATTValVector <DataField*> *dataFields = marcRecord->getDataFieldsVector();

//printf ("\ndataFields->Length() = %d", dataFields->Length());

        for (int i=0;i< dataFields->Length(); i++ )
        {
        	fieldData->Reset();

			df = dataFields->Entry(i);
			if (!df)
				continue;
			fieldData->AddChar(df->getIndicator1());
			fieldData->AddChar(df->getIndicator2());

			// Get SUBFIELDS
            ATTValVector <Subfield*> *subfields =  df->getSubfields();
            for (int j=0;j< subfields->Length(); j++ )
            {
                sf = subfields->Entry(j);
                //getDataElement(sf->getData(), dataElement);
                sPtr = sf->getDataString();

				if (sPtr->Length() > 9998)
				{
					//printf ("\nCAMPO Troppo lungo (verra' escluso ESCLUSO) per aver superato max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTag(), controlFields->Entry(0)->getData(), dataElement.Length());
//					fprintf (stderr, "\nSUBFIELD Troppo lungo (viene troncato a max len di 9.999 bytes: Field %s, BID=%s, length=%ld", df->getTagString()->data(), controlFields->Entry(0)->getData()->data(), sPtr->Length());
//					sPtr->Resize(9999); // 29/01/2010 12.33


					int pos = sPtr->IndexCharFrom(' ', 9998, sPtr->backward);
					sPtr->CropRightFrom(pos);
					fprintf(stderr, "Bid %s, SOTTOCAMPO %0.3d troppo lungo. Viene TRONCATO a posizione %d\n", controlFields->Entry(0)->getData()->data(), sf->getId(), pos);


					// continue;
				}

   				if (fieldData->GetUsedBytes()+sPtr->Length() > 9998)
				{
					fprintf (stderr, "\nBID=%s - Field %s:  FIELD TRONCATO per aver superato max len di 9995 bytes,  length=%ld (sottocamp N.%d)\n",
							controlFields->Entry(0)->getData()->data(), df->getTagString()->data(), recordData->GetUsedBytes()+sPtr->Length(), j);
//					int pos = sPtr->IndexCharFrom(' ', 9995, sPtr->backward);
//					sPtr->CropRightFrom(pos);
//					fprintf(stderr, "Bid %s, CAMPO %0.3d troppo lungo. Viene TRONCATO a posizione %d\n", controlFields->Entry(0)->getData()->data(), sf->getId(), pos);
					break;
				}

                fieldData->AddChar(SUBFIELD_DELIMITER);
                fieldData->AddChar(sf->getCode());
//if (df->getId() == 330)
//	fprintf (stderr, "\n->Tag 330 BEFORE\nData: %s\n", sPtr->data());
// 14/09/2021
sPtr->ChangeTo("{dollar}", "$");

//if (df->getId() == 330)
//	fprintf (stderr, "\n->Tag 330 AFTER\nData: %s\n", sPtr->data());

				fieldData->AddBinaryData(sPtr->data(), sPtr->Length());

            } // End for subfields

            fieldData->AddChar(FIELD_TERMINATOR);

            // Stiamo sforando?
            // FIX per bug BVE PAL0040043 14/03/2011
            len = leaderLength + recordData->GetUsedBytes() + fieldData->GetUsedBytes() + directoryData->GetUsedBytes() + directoryEntryLength +1;
			if (len > 99900)
			{
				cf = controlFields->Entry(0);
				fprintf (stderr, "\nRECORD TROPPO LUNGO (Max 99999) per bid %s. VIENE TRONCATO!! Scaricati %d campi dati su %d. I %d campi rimanenti vanno persi.", cf->getData()->data(), i, dataFields->Length(), dataFields->Length()-i);
				break; // 14/03/2011
			}


            // Aggiungiamo il campo al record
            recordData->AddBinaryData(fieldData->Data(), fieldData->GetUsedBytes());

            // Ricalcoliamo la directory entry
//            getEntry(df->getTagString()->data(), recordData->GetUsedBytes() - previous, previous, directoryEntry);
//			directoryData->AddString(directoryEntry.Data());

			sprintf (buf, "%3s%04d%05d", df->getTagString()->data(), recordData->GetUsedBytes() - previous, previous);
//			directoryEntry.assign (buf, 12);
			directoryData->AddBinaryData(buf, 12);

			previous = recordData->GetUsedBytes();



//printf ("\nRecord data = %d", previous);

        } // End for datafields


        directoryData->AddChar(FIELD_TERMINATOR);

        // Prepare il LEADER
        Leader *ldr = marcRecord->getLeader();
        ldr->setBaseAddressOfData(leaderLength + directoryData->GetUsedBytes());
        ldr->setRecordLength(ldr->getBaseAddressOfData() + recordData->GetUsedBytes() + 1);
        ldrStr = ldr->getLeader();

        return true;
} // End prepareRecordTowrite



bool MarcStreamWriter::writeToFile() {
	bool retb;

	// 14/03/2011
	int recordLen = getWriteToFileRecordLength();
	if (recordLen > 99999)
	{
		fprintf (stderr, "\nRecord troppo lungo %d. Scartato!!", recordLen);
		return false;
	}

	retb = out->Write(ldrStr->data(), ldrStr->Length());
	if (!retb)
		return retb;
	retb = out->Write(directoryData->Data(), directoryData->GetUsedBytes());
	if (!retb)
		return retb;
	retb = out->Write(recordData->Data(), recordData->GetUsedBytes());
	if (!retb)
		return retb;
    char chr = RECORD_TERMINATOR;
    retb = out->Write(chr);


	if (RECORDUNIMARCSUSINGOLARIGA == 1)
	    retb = out->Write('\n');



    return retb;
}


/**
 * Writes a <code>Record</code> object to the writer.
 *
 * @param record -
 *            the <code>Record</code> object
 */
bool MarcStreamWriter::writeStructure(MarcRecord* marcRecord) {
	bool retb;

        retb = prepareRecordTowrite(marcRecord);
        if (!retb)
        	return retb;

        //return writeToFile();


        Leader *ldr = marcRecord->getLeader();
        if (ldr->getRecordLength() > 99999)
    	{
    		fprintf (stderr, "\nRecord troppo lungo %d. Scartato!!", ldr->getRecordLength());
    		return false;
    	}

        printf ("\n\n%s",ldr->toString());


        ATTValVector <ControlField*> *controlFields = marcRecord->getControlFieldsVector();
        for (int i=0;i< controlFields->Length(); i++ )
        {
			ControlField *cf = controlFields->Entry(i);
			if (strcmp ((const char *)cf->getTag(), (const char *)"001") == 0 )
			{
				printf ("\n%s %s", cf->getTag(), cf->getData()->Data());
				break;
			}

        }




//        int leaderLength = 24;
        int directoryLength = directoryData->GetUsedBytes()-1;
        CString *directory = new CString (directoryData->Data(), directoryLength);

//        Directory entries (12 bytes per entry), ......
//        [-][--][---]-
//        |  |   |    |
//        |  |   |    F/T = Field Terminator
//        |  |   Posizione del primo carattere del campo(iniziando da 0)
//        |  Length of field
//        Etichetta

//        printf ("\n%s",directory->Data());

        int pos=0;
    	CString tag, fieldLength, fieldPos;
    	printf("\n  TAG R.POS A.POS A.POS LENGTH");
        while (pos < directoryLength)
        {
        	tag = directory->SubstringData(pos, 3);
        	pos+=3;
        	fieldLength = directory->SubstringData(pos, 4);
        	pos+=4;
        	fieldPos = directory->SubstringData(pos, 5);
        	pos+=5;


        	long absolutePos = ldr->getBaseAddressOfData() + atol(fieldPos.data());

        	printf("\n  %s %s %0.5ld %0.5x %s", tag.data(), fieldPos.data(), absolutePos, absolutePos, fieldLength.Data());

        }

        delete directory;

        return true;
} // End writeStructure

