
// ese599_project2Doc.cpp : implementation of the Cese599_project2Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ese599_project2.h"
#endif

#include "ese599_project2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cese599_project2Doc

IMPLEMENT_DYNCREATE(Cese599_project2Doc, CDocument)

BEGIN_MESSAGE_MAP(Cese599_project2Doc, CDocument)
END_MESSAGE_MAP()


// Cese599_project2Doc construction/destruction




Cese599_project2Doc::Cese599_project2Doc()
{
	double gap = 5;
	double margin = 30;
	// TODO: add one-time construction code here
	this->main_scr = Screen(Coord2(gap, gap), 750, 750, .75);
	this->sub_scr[0] = Screen(Coord2(main_scr.get_right() + gap + margin, gap), 320, 240, .5);
	this->sub_scr[1] = Screen(Coord2(main_scr.get_right() + gap + margin, sub_scr[0].get_bottom() + gap + margin), 320, 240, .5);
	this->sub_scr[2] = Screen(Coord2(sub_scr[0].get_right() + gap + margin, gap), 320, 240, .5);
	this->sub_scr[3] = Screen(Coord2(sub_scr[1].get_right() + gap + margin, sub_scr[2].get_bottom() + gap + margin), 320, 240, .5);
	this->map_scr = Screen(Coord2(gap, gap), 1000, 1000, .75);

	this->room = World(615, 117, 0, 1000, 1000);


	cam[0] = Camera(322.515987, 259.055966, 521.179233, 493.033034, 0.05858325, 0.03856792, 0, 0, 0, 0, 0, 0, 0, 0, 640, 480);
	cam[0].moveTo(300, 0, 200, 40, -55);

	cam[1] = Camera(322.515987, 259.055966, 521.179233, 493.033034, 0.05858325, 0.03856792, 0, 0, 0, 0, 0, 0, 0, 0, 640, 480);
	cam[1].moveTo(900, 0, 200, 60, -50);

	cam[2] = Camera(322.515987, 259.055966, 521.179233, 493.033034, 0.05858325, 0.03856792, 0, 0, 0, 0, 0, 0, 0, 0, 640, 480);
	cam[2].moveTo(1000, 900, 200, 100, -55);

	cam[3] = Camera(322.515987, 259.055966, 521.179233, 493.033034, 0.05858325, 0.03856792, 0, 0, 0, 0, 0, 0, 0, 0, 640, 480);
	cam[3].moveTo(300, 1000, 200, 130, -60);

}



void Cese599_project2Doc::SpaceKey()
{
	this->room.object_decrement();
	UpdateAllViews(0, 0, 0);
} 





/*
void Cese599_project2Doc::up()
{
	this->room.object_up();
	UpdateAllViews(0, 0, 0);
}

void Cese599_project2Doc::down()
{
	this->room.object_down();
	UpdateAllViews(0, 0, 0);
}

void Cese599_project2Doc::left()
{
	this->room.object_left();
	UpdateAllViews(0, 0, 0);
}

void Cese599_project2Doc::right()
{
	this->room.object_right();
	UpdateAllViews(0, 0, 0);
}

*/

Cese599_project2Doc::~Cese599_project2Doc()
{
}

BOOL Cese599_project2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cese599_project2Doc serialization

void Cese599_project2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cese599_project2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cese599_project2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cese599_project2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cese599_project2Doc diagnostics

#ifdef _DEBUG
void Cese599_project2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cese599_project2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cese599_project2Doc commands
