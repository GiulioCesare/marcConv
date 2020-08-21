/*
 * DocOfflineExport.cpp
 *
 *  Created on: Feb 2, 2011
 *      Author: export
 */

#include "DocOfflineExport.h"

char *divMemdoc = "<div class=\"memdoc\">";
char *endDiv = "</div>";



DocOfflineExport::DocOfflineExport() {
	// TODO Auto-generated constructor stub

}

DocOfflineExport::~DocOfflineExport() {
	// TODO Auto-generated destructor stub
}

void DocOfflineExport::makeDocumentation()
{
	tagsKV = new CKeyValueVector(tKVSTRING, tKVVOID);
	tocKV = new CKeyValueVector(tKVSTRING, tKVSTRING);

	char *files[] = {
			"/home/export/workspace/cdt/doc/doxygen/html/class_leader.html",
			"/home/export/workspace/cdt/doc/doxygen/html/class_marc4cpp_collocazione.html",
			"/home/export/workspace/cdt/doc/doxygen/html/class_marc4cpp_documento.html",
			"/home/export/workspace/cdt/doc/doxygen/html/class_marc4cpp_legami.html",
			0
	};

	//	CFile *cFileIn = new CFile("/home/export/workspace/cdt/doc/doxygen/html/class_leader.html");
	cFileOut = new CFile("/home/export/workspace/cdt/doc/doxygen/docOfflineExport/docOfflineExport.html", AL_WRITE_FILE);

	for (int i=0; files[i]; i++)
	{
		cFileIn = new CFile(files[i]);
		printf ("\nElaborando %s", files[i]);
		elaboraFile();
		delete cFileIn;
	}


	scriviDocumentazione();

	delete tagsKV;
	delete tocKV;

	delete cFileOut;
	printf ("\nFine testMakeDocumentation");
} // End makeDocumentation






void DocOfflineExport::scriviDocumentazione()
{
	// Scriviamo la documentazione

	char *header =
	"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" \
	"<html xmlns=\"http://www.w3.org/1999/xhtml\">"\
	"<head>"\
	"<meta http-equiv=\"Content-Type\" content=\"text/xhtml;charset=UTF-8\"/>"\
	"<title>offlineExport Unimarc: Leader Class Reference</title>"\
	"<link href=\"tabs.css\" rel=\"stylesheet\" type=\"text/css\"/>"\
	"<link href=\"search/search.css\" rel=\"stylesheet\" type=\"text/css\"/>"\
	"<script type=\"text/javaScript\" src=\"search/search.js\"></script>"\
	"<link href=\"doxygen.css\" rel=\"stylesheet\" type=\"text/css\"/>"\
	"</head>";

	char *title =	"<div class=\"headertitle\">"\
				"<h1>Documentazione etichette export offline Unimarc</h1>"\
				"<h2>Versione 2.01.7a 28/01/2011</h2>"\
				"Elaborato di doxygen e rielaborato da DocOfflineExport.cpp"\
				"</div>";

	// Ordiniamo i Tag
	tagsKV->SortAscendingByKey();
	tocKV->SortAscendingByKey();

	cFileOut->Write(header);
	cFileOut->Write(title);

	// Scriviamo su file la TOC
	// ------------------------
	cFileOut->Write("<h2>Elenco etichette</h2>");

	// Leader first
	cFileOut->Write("<a href=#");
	cFileOut->Write((char *)tocKV->GetKey(tocKV->Length()-1));
	cFileOut->Write('>');
	cFileOut->Write((char *)tocKV->GetValue(tocKV->Length()-1));
	cFileOut->Write("</a>");


	for (int i=0; i < tocKV->Length()-1; i++)
	{
		cFileOut->Write("<a href=#");
		cFileOut->Write((char *)tocKV->GetKey(i));
		cFileOut->Write('>');
		cFileOut->Write((char *)tocKV->GetValue(i));
		cFileOut->Write("</a>");
	}



	// Scriviamo su file le etichette
	// ------------------------------
	cFileOut->Write("<h2>Sezione etichette</h2>");
	scriviTag(tagsKV->Length()-1);


	for (int i=0; i < tagsKV->Length()-1; i++)
		scriviTag(i);

} // End scriviDocumentazione

void DocOfflineExport::scriviTag(int i)
{
	CString *tag;
	tag = (CString *)tagsKV->GetValue(i);

	cFileOut->Write("<a name=");
	cFileOut->Write((char *)tocKV->GetKey(i));
	cFileOut->Write('>');

	cFileOut->Write("<div class=\"memitem\">");
	cFileOut->Write("<div class=\"memproto\">");
	cFileOut->Write("<table class=\"memname\"><tr><td class=\"memname\">");
	cFileOut->Write("Tag ");
	cFileOut->Write((char *)tagsKV->GetKey(i));

	cFileOut->Write(" <a href=\"javascript: history.go(-1)\">(Indietro)</a>");

	cFileOut->Write("</td></tr></table>");

	cFileOut->Write(divMemdoc);
	cFileOut->Write(tag->data());
	cFileOut->Write(endDiv);
	cFileOut->Write(endDiv);
	cFileOut->Write(endDiv);

//		printf ("\nTAG = %s", tag->data());
	delete tag;
}


void DocOfflineExport::elaboraFile()
{
//	printf ("\ntestMakeDocumentation\n");

	char key[3+1];
	key[3]=0;

	CString s, tocString;
	CString *tag =0;

	int memdocLen = strlen (divMemdoc) + strlen (endDiv);


	bool inTable= false;
	char *ptr;
	while(!cFileIn->Eof())
	{
		try{
			s.ReadLine(cFileIn);

			// Siamo alla fine del tag?
			if (tag)
			{
//				printf ("\nTAG = %s", s.data());
				if (!inTable)
				{
					if (s.FindSubstring("<table "))
					{
						inTable = true;
					}
					else if (ptr = s.FindSubstring("<p><b>Tag "))
					{
						// Rimuoviamo links
						long from, to;
						from = s.IndexSubString("<a");
						if (from != -1)
							{
							to = s.IndexSubString("html\">");
							s.ExtractFromTo(from, to+5);

							from = s.IndexSubString("</a>");
							s.ExtractFromTo(from, from+3);
							}

						strncpy (key, ptr+10, 3);
						tocString = s.data();
						tocString.AppendChar('\n');
						continue;
					}
				}
				if (s.FindSubstring(endDiv))
				{
					if (tag->Length())
					{
						tagsKV->Add(key, tag);
						tocKV->Add(key, tocString.data());

						inTable = false;

//						break;
					}
					else
						delete tag;
//					printf ("\nTAG = %s", tag->data());
					tag = 0;
				}
				else
				tag->AppendString(s.data());

				continue;
			}
			// Siamo all'inizio del tag?
			else if (s.FindSubstring(divMemdoc))
			{
				tag = new CString(); // s.data()
				continue;
			}

		// SKIP irrelevant data
		} catch (GenericError e) {
			std::cout << e.errorMessage;
		}

	} // End while
} // End elaboraFile


