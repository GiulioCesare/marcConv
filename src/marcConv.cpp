//============================================================================
// Name        : marcConv.cpp
// Author      : Argentino Trombin
// Version     :
// Copyright   : ArgeCopyRight
// Description : Convert from .mrc to .mrk and viceversa
//============================================================================

#include <iostream>
#include <stdlib.h>     /* atoi */
using namespace std;

#include <vector>

#include "library/CFileInMemory.h"
#include "library/CString.h"
#include "library/Cini.h"
#include "library/GenericError.h"
#include "DocOfflineExport.h"
#include "ReadMarcExample.h"
#include "MarcRecord.h"
#include "MarcStreamReader.h"
#include "MarcStreamWriter.h"

int 	RECORDUNIMARCSUSINGOLARIGA = 0;
#define  MRC 1
#define  MRK 2

void addExportTags(char *csvTags);
bool addexportTagsfromFile(const char *tagsFilename, cIni *ini);

void testMakeDocumentation();
void convertMarcRead(char *filename);
int getFileFormat(char *filename);
void convertMrk2Mrc(char *filename);
bool getMrkRecord(CFile *cFile, CKeyValueVector *mrkRecordVector);
void  dumpMrkRecord(CKeyValueVector *mrkRecordVector);
void buildMarcRecord(CKeyValueVector *mrkRecordVector, MarcRecord *marcRecord);
void dumpMrkSubfields(char *tag, ATTValVector <CString *> *subfields);
void getMrkRecord(CKeyValueVector *mrkRecordVector, CString *sPtr);


ATTValVector <CString *> exportTags;
cIni *ini;
char *tagsToExtractBufferPtr;
#define IS_TAG_TO_EXTRACT(tag) *(tagsToExtractBufferPtr + tag)
CString *mrcRecordToMrk(MarcRecord *marcRecord);
void convertMrc2Mrk(char *filename);
CString mrkString;

long convert_from;
long convert_to; // 0 = all
bool noConvert;
bool dumpStructure = false;


CString readFowardString;


// Print lines for CFile and DERIVED classes
void printLines(CFile* cFile)
{
	long ctr = 0;
	CString s;
//	char buf[200];


	while(!cFile->Eof())
	{
//		if (!s.ReadLine(cFile))
//			break;
		try{
			s.ReadLine(cFile);

		//cFile->ReadLine(buf, sizeof(buf));

		} catch (GenericError e) {
			std::cout << e.errorMessage;
		}

		ctr++;
//		printf ("\nLette %ld righe: ultima %s", ctr, s.data());
		printf ("\nLette %ld righe: ultima %s", ctr, s.data());

		if (!(ctr & 0xf))
		{
			break;
		}
	}

}

void testCFile()
{
	printf ("\ntestCFile\n");

	CFile *cFile = new CFile("/media/hd3/SbnWeb/migrazione/bve/input/tr_aut_aut.out.srt.rel");

	printLines(cFile);

	delete cFile;
	printf ("\nFine testCFile");
}






void testMakeDocumentation()
{
//	cout << "!!!Hello testMakeDocumentation!!!" << endl;
	DocOfflineExport docOfflineExport;
	docOfflineExport.makeDocumentation();
}






int getFileFormat(char *filename)
{
	//printf ("\ntestCFile\n");

	CFile *cFile = new CFile(filename);

//	printLines(cFile);
	char dest[5+1];
	dest[5] = 0;
	cFile->Read(dest, 5);

	for (int i=0; i < 5; i++) // Controlliamo se abbiamo 5 digiti per la lunghezza del record
	{
		if (dest[i] < '0' || dest[i] > '9')
		{
			delete cFile;
			return MRK;
		}
	}
	delete cFile;
	return MRC;
	//printf ("\nFine testCFile");
}

void convertMarcRead(char *filename)
{
//	cout << "!!!Hello testMarcRead!!!" << endl;
	//readMarcExample.read("/home/export/offlineExport/bve/tmp/IE001_BVE_CR_00006446.mrc"); // OK da export offline
//	readMarcExample.read("/home/export/offlineExport/bve/tmp/IEbase_BVE.mrc"); // Unimarc prodotto dal dataprep
//	readMarcExample.read("/home/export/offlineExport/bve/tmp/IEbase_BVE.Out.mrc"); // Unimarc prodotto dal dataprep


	// What are we converting?
	int fileFormat = getFileFormat(filename);

	if (fileFormat == MRC)
		{
		// Convert from .mrc to .mrk
//		ReadMarcExample readMarcExample;
//		readMarcExample.read(filename); // Unimarc prodotto dal dataprep
		convertMrc2Mrk(filename);
		}
	else
	{
		convertMrk2Mrc(filename);
	}

}

CString *mrcRecordToMrk(MarcRecord *marcRecord)
{
	ControlField *cf;
	DataField *df;
	CString *sPtr;

	// Prepare the leader
	mrkString.assign(marcRecord->getLeader()->toCString());

	cf = marcRecord->getControlFieldsVector()->Entry(0);
	char *id = cf->getData()->Data();



	// Cycle through the control fields
	int tag;
	for (int i=0; i < marcRecord->getControlFieldsVector()->Length(); i++)
	{
		cf = marcRecord->getControlFieldsVector()->Entry(i);
		tag = atoi (cf->getTag());
		if (!IS_TAG_TO_EXTRACT(tag))
			continue;
		mrkString.AppendString(cf->toCString());
	}

	// Cycle through the data fields
	for (int i=0; i < marcRecord->getDataFieldsVector()->Length(); i++)
	{
		df = marcRecord->getDataFieldsVector()->Entry(i);
		if (df)
		{
			tag = df->getId();
			if (!IS_TAG_TO_EXTRACT(tag))
				continue;

			sPtr = df->toCString(id);
			mrkString.AppendString(sPtr);
		}
		else
			//SignalAnError(__FILE__, __LINE__, "ERRORE: Datafield %d (partendo da 0) non instanziato (datafields=%d)", i, marcRecord->getDataFieldsVector()->Length());
			printf ("ERRORE: Datafield %d (partendo da 0) non instanziato (datafields=%d)", i, marcRecord->getDataFieldsVector()->Length());
	}



	return &mrkString;
}





//bool getMrkRecord(CFile *cFile, CKeyValueVector *mrkRecordVector)
//{
//	CString s;
//	CString key;
//	CString value;
//	bool hasRecord=false;
//
//	// Clear the vector;
//	mrkRecordVector->Clear();
//
//	int ctr=0;
//	while(!cFile->Eof())
//	{
//		s.Clear();
//		if (!s.ReadLine(cFile))
//			break;
//		if (s.IsEmpty())
//		{
//			if (hasRecord)
//				return true;
//			else
//				//return false;
//				continue;
//		}
//
//
//		key = s.SubstringData(1,3);
//		value = s.SubstringData(6);
//
//
//		mrkRecordVector->Add(key.data(), value.data());
//		ctr++;
//		hasRecord = true;
//
//	}
//	if (hasRecord)
//		return true;
//	else
//		return false;
//}



// 22/10/2019 GESTIONE TAG MULTILINE
bool getMrkRecord(CFile *cFile, CKeyValueVector *mrkRecordVector)
{
	CString s,sForward;
	CString key, value, bid;
	bool hasRecord=false;

	// Clear the vector;
	mrkRecordVector->Clear();

	int ctr=0;

	if (!readFowardString.IsEmpty())
	{
		s.assign(readFowardString.data());
		readFowardString.Clear();
	}
	else
	{
		s.Clear();
		if (!s.ReadLine(cFile))
			return hasRecord;
	}

	while(!cFile->Eof())
	{
		if (s.IsEmpty())
		{
			if (hasRecord)
				return true;
			else
				//return false;
				s.ReadLine(cFile);
				continue;
		}

		key = s.SubstringData(1,3);
		value = s.SubstringData(6);

		if (key.isEqual("001"))
			bid.assign(&value);

		while (true)
		{
			s.Clear();
			if (!s.ReadLine(cFile) || cFile->Eof())
			{
				if (value.Length() > 9995)
				{
					int pos = value.IndexCharFrom(' ', 9995, value.backward);
					value.CropRightFrom(pos);
					fprintf(stderr, "Bid %s, campo %s troppo lungo. Viene TRONCATO a posizione %d\n", bid.data(), key.data(), pos);
				}
				mrkRecordVector->Add(key.data(), value.data());
				return hasRecord;
			}

			if (s.IsEmpty())	// Riga vuota
			{
				value.AppendChar('\n');
				continue;
			}

			if (s.Length() && s.GetFirstChar() == '=')
			{
				if (s.Length() < 4)
				{
					value.AppendChar('\n');
					value.AppendString(s.data());
					continue;
				}

				CString tag = s.SubstringData(1,3);

				if (hasRecord && tag.isEqual("LDR"))
				{
					value.ExtractLastChar(); // get rid of /n

					if (value.Length() > 9995)
					{
						int pos = value.IndexCharFrom(' ', 9995, value.backward);
						fprintf(stderr, "Bid %s, campo %s troppo lungo. Viene TRONCATO a posizione %d\n", bid.data(), key.data(), pos);
						value.CropRightFrom(pos);
					}
					mrkRecordVector->Add(key.data(), value.data());
					readFowardString.assign(&s);
					return hasRecord;
				}


				char *ptr = tag.Data();
				if (tag.isEqual("FMT") || (
							isdigit(*(ptr)) &&
							isdigit(*(ptr+1)) &&
							isdigit(*(ptr+2))  ))
				{
					// NEW tag
					break;
				}

				else
				{
					value.AppendChar('\n');
					value.AppendString(s.data());
					continue;
				}
			}
			else
			{
				value.AppendChar('\n');
				value.AppendString(s.data());
			}

		} // End while

		if (value.Length() > 9995)
		{
			int pos = value.IndexCharFrom(' ', 9995, value.backward);
			fprintf(stderr, "Bid %s, campo %s troppo lungo. Viene TRONCATO a posizione %d\n", bid.data(), key.data(), pos);
			value.CropRightFrom(pos);
			value.AppendString("...");
//fprintf(stderr, "value len=%d", value.Length());
		}
		mrkRecordVector->Add(key.data(), value.data());
		ctr++;
		hasRecord = true;

	} // end while reading
	return hasRecord;

} // end getMrkRecord







void buildMarcRecord(CKeyValueVector *mrkRecordVector, MarcRecord *marcRecord)
{
	int mrkTag;
	CString mrkKey;
	CString mrkValue;
	char indicator1 = ' ';
	char indicator2 = ' ';

	ATTValVector <CString *> subfields;
	Leader *leader = new Leader();
	ControlField *cf;
	DataField *df;
	Subfield *sf;

	marcRecord->clear();

	for (int i=0; i < mrkRecordVector->Length(); i++)
	{
		CKeyValue *kvPtr;
		kvPtr = mrkRecordVector->Get(i);
		mrkKey = kvPtr->Key.p;
		mrkValue = kvPtr->Val.p;
		char buf[10];

		if (!mrkKey.Compare("LDR"))
		{
			// Handle leader
			leader->setRecordLength(0); // To be done once the record has been filled up
			leader->setRecordStatus(mrkValue.GetChar(5));
			leader->setTypeOfRecord(mrkValue.GetChar(6));
			leader->setLivelloBibliografico(mrkValue.GetChar(7));
			leader->setLivelloGerarchico(mrkValue.GetChar(8));
			leader->setPos9Undefined(mrkValue.GetChar(9));

			buf[0] = mrkValue.GetChar(10);
			buf[1] = 0;
			leader->setIndicatorCount(atoi (buf));

			buf[0] = mrkValue.GetChar(11);
			leader->setSubfieldCodeLength(atoi (buf));

			leader->setBaseAddressOfData(0);// To be done once the record has been filled up
			leader->setLivelloDiCodifica(mrkValue.GetChar(17));
			leader->setTipoDiCatalogazioneDescrittiva(mrkValue.GetChar(18));
			char entryMap[5+1];
			entryMap[0]=mrkValue.GetChar(19);
			entryMap[1]=mrkValue.GetChar(20);
			entryMap[2]=mrkValue.GetChar(21);
			entryMap[3]=mrkValue.GetChar(22);
			entryMap[4]=mrkValue.GetChar(23);
			entryMap[5]=0;
			leader->setEntryMap(entryMap);

			continue;
		}

		mrkTag = atoi(mrkKey.data());


		if (mrkTag > 0 && mrkTag < 10)
		{ // Control field
	        cf = new ControlField();

	        cf->setTag(mrkKey.data());
	        cf->setData(&mrkValue);
	        marcRecord->addControlField(cf);
		}
		else
		{
			indicator1 = mrkValue.GetChar(0);
			indicator2 = mrkValue.GetChar(1);

			// Split subfields
			mrkValue.CropLeftBy(2); // rimuoviamo gli indicatori

			mrkValue.Split(subfields, '$');	// Suddividiamo i sottocampi
//			dumpMrkSubfields(mrkKey.data(), &subfields);
//			mrkValue.Split(subfields, 01);	// Suddividiamo i sottocampi


			// Create the datafield
			df = new DataField(mrkKey.data(), indicator1, indicator2);
			// Add the subfields
			for (int i=1; i < subfields.Length(); i++)
			{
				char code = subfields.Entry(i)->GetFirstChar();
				if (subfields.Entry(i)->Length()) // 22/12/15
					subfields.Entry(i)->CropLeftBy(1);
				sf = new Subfield(code, subfields.Entry(i));
				df->addSubfield(sf);
				//printf ("$%c%s", subfields->Entry(i)->GetFirstChar(),  subfields->Entry(i)->data()+1);
			}
	        marcRecord->addDataField(df);


	        // Remove temporary data
	        subfields.DeleteAndClear();
		}
		// printf ("\n%s: '%s'", kvPtr->Key.p, mrkValue.data());

	} // End for

	// Finish off leader
	// -----------------
//	int recordLength = 0;
//	leader->setRecordLength(recordLength); // To be done once the record has been filled up
//	int baseDataAddress = 0;
//	leader->setBaseAddressOfData(baseDataAddress);// To be done once the record has been filled up
	marcRecord->setLeader(leader);


} // End buildMarcRecord

void dumpMrkSubfields(char *tag, ATTValVector <CString *> *subfields)
{
//	printf ("\nDUMP RECORD SUBFIELDS");
//	printf ("\n=====================");
	printf ("\n%s ", tag);
	for (int i=1; i < subfields->Length(); i++)
	{
		printf ("$%c%s", subfields->Entry(i)->GetFirstChar(),  subfields->Entry(i)->data()+1);
	}

}






void testCFileInMemory()
{
	CString s;
	int ctr=0;
	printf ("\ntestCFileInMemory\n");

	CFileInMemory *cFile = new CFileInMemory("/media/export70/indice/dp/input/tr_tit_mar.out.srt.rel");

	CString * sPtr = new CString(8);
	sPtr->SetResizeValueBy(8);

	// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
	cFile->SeekTo(0);
	if (!sPtr->ReadLineWithPrefixedMaxSize(cFile))
        printf ("read failed");

	printf ("\n%s", sPtr->data());


//	printLines(cFile);

//	while(!cFile->Eof())
//	{
//		if (!s.ReadLine(cFile))
//			break;
//		ctr++;
//		printf ("\nLette %ld righe: ultima %s", ctr, s.data());
//		if (!(ctr & 0xf))
//		{
//			break;
//		}
//	}


	delete cFile;
	printf ("\nFine testCFileInMemory");
}





bool addexportTagsfromFile(const char *tagsFilename, cIni *ini)
{
	CString tagsLine;

	// Reset eventuali export
	exportTags.DeleteAndClear();


	// Apri il file
	CFile *tagsFileIn=0; //= new CFile(tagsFilename);
	try{
		tagsFileIn = new CFile(tagsFilename, AL_READ_FILE);
	} catch (GenericError e) {
		if (tagsFileIn)
			delete tagsFileIn;
		std::cout << e.errorMessage;
		return false;
	}

	while(!tagsFileIn->Eof())
	{
		if (!tagsLine.ReadLine(tagsFileIn))
			break;
		if (tagsLine.GetFirstChar() == '#' || tagsLine.IsEmpty())
			continue;

		ini->SplitIniFields(tagsLine.data());

		if (!ini->fieldsVector->Entry(0)->Compare("extractTags"))
			addExportTags(ini->fieldsVector->Entry(1)->data());

	}

	delete tagsFileIn;
	return true;
}


void addExportTags(char *csvTags)
{
	ATTValVector <CString *> localExportTags;
	CString s = csvTags;
	CString *sPtr;
	s.Split(localExportTags, ',');

	for (int i=0; i < localExportTags.length(); i++)
	{
		sPtr = localExportTags.Entry(i);
		sPtr->CropRightFrom(3);
		if (sPtr->Length())
			exportTags.Add(sPtr);
//printf ("\n Export Tag %s", localExportTags.Entry(i)->data());
	}

//printf ("\n --------------", exportTags.length());
//printf ("\n Export %d tags", exportTags.length());
}






void dumpMrkRecord(CKeyValueVector *mrkRecordVector)
{
	fprintf (stderr, "\nDUMP RECORD MRK");
	fprintf (stderr, "\n===============");
	for (int i=0; i < mrkRecordVector->Length(); i++)
	{
		CKeyValue *kvPtr;
		kvPtr = mrkRecordVector->Get(i);
		fprintf (stderr, "\n%s: '%s'", kvPtr->Key.p, kvPtr->Val.p);
	}
}


void getMrkRecord(CKeyValueVector *mrkRecordVector, CString *sPtr)
{
	sPtr->Clear();
	for (int i=0; i < mrkRecordVector->Length(); i++)
	{
		CKeyValue *kvPtr;
		kvPtr = mrkRecordVector->Get(i);
		//printf ("\n%s: '%s'", kvPtr->Key.p, kvPtr->Val.p);
		sPtr->AppendChar('\n');
		sPtr->AppendString(kvPtr->Key.p);
		sPtr->AppendString("  ");
		sPtr->AppendString(kvPtr->Val.p);
	}

}


void convertMrc2Mrk(char *filename)
{
CFile *in = new CFile(filename, AL_READ_FILE);
FILE * out = stdout;
CFile *cFileOut;

MarcStreamReader *marcStreamReader = new MarcStreamReader(in);
MarcStreamWriter *marcStreamWriter = NULL;

if (noConvert || dumpStructure)
{
	cFileOut = new CFile("stdout", out);
	marcStreamWriter = new MarcStreamWriter(cFileOut);
}

MarcRecord *marcRecord;
long read_ctr = 0;
CString *sPtr;

while (marcStreamReader->hasNext()) {
	marcRecord = marcStreamReader->next(); // Legge il record
	read_ctr++;

	if (!marcRecord)
		break;

	if (read_ctr < convert_from)
		continue;

	if (marcRecord && read_ctr >= convert_from)
		{

		// Convertiamo o scriviamo come lo abbiamo letto


		if (noConvert)
		{ // keep as is
			marcStreamWriter->write(marcRecord);
		}
		else
		{

			if (dumpStructure)
			{

				marcStreamWriter->writeStructure(marcRecord);

			}
			else
			{
				sPtr = mrcRecordToMrk(marcRecord);
				printf("%s\n\n", sPtr->Data());
			}
		}
		//printf ("\nRecord %d, bid=%s", ctr, marcRecord->getControlFieldsVector()->Entry(0)->getData()->data());
		}


	if (convert_to && read_ctr >= convert_to) // convert_to a 0 = tutti
	{
//		printf ("Exit after record %ld", convert_to);
		break;
	}
} // End while

//printf ("\nConvertiti %d record", ctr);

delete in;
delete marcStreamReader;
if (noConvert || dumpStructure)
{
	delete cFileOut;
	delete marcStreamWriter;
}

} // End convertMrc2Mrk



void convertMrk2Mrc(char *filename)
{
	CFile *cFileIn = new CFile(filename);
	FILE * out = stdout;
	CFile *cFileOut = new CFile("stdout", out);
	CString *mrkPtr = new CString();

	//vector <CString*> mrkRecordVector;
	CKeyValueVector *mrkRecordVector;
	mrkRecordVector = new CKeyValueVector(tKVSTRING, tKVSTRING);

	MarcRecord *marcRecord = new MarcRecord();
	MarcStreamWriter *marcStreamWriter = new MarcStreamWriter(cFileOut);

	long read_ctr = 0;
	CString *sPtr;

	while (getMrkRecord(cFileIn, mrkRecordVector))
	{
//dumpMrkRecord(mrkRecordVector);

		read_ctr++;

		if (read_ctr < convert_from)
			continue;

		// Convertiamo o scriviamo come lo abbiamo letto
		if (noConvert)
		{ // keep as is
			getMrkRecord(mrkRecordVector, mrkPtr);
			printf("%s\n\n", mrkPtr->Data());
		}
		else
		{
			// Do conversion to MRC
			buildMarcRecord(mrkRecordVector, marcRecord);

			if (dumpStructure)
				marcStreamWriter->writeStructure(marcRecord);
			else
				marcStreamWriter->write(marcRecord);
		}

		if (convert_to && read_ctr >= convert_to) // convert_to a 0 = tutti
		{
			break;
		}

	} // end while

	delete marcRecord;
	delete mrkRecordVector;
	delete mrkPtr;
	delete cFileIn;
	delete cFileOut;
	delete marcStreamWriter;
} // End convertMrk2Mrc

void test_changeTo()
{
	CString s = "h{{dollar}k{dollar}-critical cells}";

	fprintf (stderr, "\n->Tag 330 BEFORE\nData: %s\n", s.data());
	s.ChangeTo("{dollar}", "$");
	fprintf (stderr, "\n->Tag 330 AFTER\nData: %s\n", s.data());

}



int main(int argc, const char* argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);

//test_changeTo();
//exit(1);

	if (argc < 2)
	{

		//		printf ("USO: marcConv filename (mrc o mrk) [tagsToextractFilename]\n");
		printf ("USO: marcConv filename (mrc o mrk) [tags=tagsToextractFilename] [from=nn] [to=nn] [noConvert=true] [dumpStructure=true]\n");
		//printf ("Ver: 2015_03_26 gestione mrc con lf o cr/lf\n");
		//printf ("Ver: 2015_11_04 gestione extract tags parametrizzato\n");
//		printf ("Ver: 2017_03_07 gestione extract di range di record form/to con conversione o no\n");
//		printf ("Ver: 2019_09_19 gestione extract di range di record form/to con conversione o no\n");
//		printf ("Ver: 2019_10_24 15:50\n"); // gestione gestione mrk con tag su piu' righe, anche vuote
										// Troncamento campi troppo lunghi a 9995 (primo spazio a sinistra)
										// Errori e Warning su stderr
//		printf ("Ver: 2021_09_13 16:18\n"); // Fix troncamento campo troppo lungo e migliorato report

		printf ("Ver: 2021_09_14 11:21\n"); // Gestione {dollar} nel testo dei sottocampi del .mrk per distinguerlo dal marcatore in chiaro del sottocampo: '$'
		exit (1);
	}

	int maxTags=10*100+1;
	CString arg;
	tagsToExtractBufferPtr = 0;
	convert_from = 1;
	convert_to = 0; // 0 = all
	noConvert = false; // defaulr

	if (argc > 1)
	{
		for (int i = 2; i <= argc; i++)
		{
			arg = argv[i];
			if (arg.StartsWith("to="))
				convert_to = atol(arg.data()+3);
			else if (arg.StartsWith("from="))
				convert_from = atol(arg.data()+5);
			else if (arg.StartsWith("noConvert=true"))
				noConvert = true;
			else if (arg.StartsWith("tags="))
			{
				ini = new cIni();
				addexportTagsfromFile(arg.data()+5, ini);
				if (exportTags.length())
				{
					// Nuova gestione per un accesso veloce senza ricerca dicotomica!!

				 	CString *tagPtr;
					int tag;
					for (int i=0; i < exportTags.length(); i++)
					{
						tagPtr = exportTags.Entry(i);
						tag = atoi (tagPtr->data());
						*(tagsToExtractBufferPtr+tag) = 1;	// set to true
					}
				}
				delete ini;
			}
			else if (arg.StartsWith("dumpStructure=true"))
				dumpStructure = true;

		}
	}

	// Se tags non caricati
	if (!tagsToExtractBufferPtr)
	{	// export alla tags
		tagsToExtractBufferPtr = (char *)malloc(maxTags * sizeof(char)); // 10 blocchi da 100 bytes settati a false +1 per start a 1 e non a 0
		for (int i=0; i < maxTags; i++)
			*(tagsToExtractBufferPtr+i) = 1;	// set to true

	}

//	printf ("Converting from record %ld to record %ld\n", convert_from, convert_to);

	convertMarcRead((char *)argv[1]);

	//testCFileInMemory();
	exportTags.DeleteAndClear();

	return 0;
}


