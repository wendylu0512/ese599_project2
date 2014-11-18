
// ese599_project2View.h : interface of the Cese599_project2View class
//

#pragma once

#include "Screen.h"
#include "Coord2.h"
#include <string.h>
#include <string>
#include <thread>
#include <iostream>
#include <map>

class Cese599_project2View : public CScrollView
{
protected: // create from serialization only
	Cese599_project2View();
	DECLARE_DYNCREATE(Cese599_project2View)

// Attributes
public:
	Cese599_project2Doc* GetDocument() const;
	

private:
	clock_t time;

	int counter = 0;	//************************** -- USED FOR KEYDOWN

	//string localzones(int k);
	vector<int> zones_mapped;

// Operations
public:
	void draw_obj(CDC* pDC, Coord2 obj, Screen scr);
	void draw_cam(CDC* pDC, Camera cam, int i);
	void draw_obj_on_sub(CDC* pDC, Coord2 obj, Screen scr, Camera cam, int k);
	void draw_grid_on_sub(CDC* pDC, Camera cam, Screen scr, World room);
	void draw_text(CDC* pDC, Camera cam, int i);
	void refresh_scr(CDC* pDC, int i);

	//void map_zones(CDC* pDC, Camera cam, Screen scr, int h);

	

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);



protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cese599_project2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in ese599_project2View.cpp
inline Cese599_project2Doc* Cese599_project2View::GetDocument() const
   { return reinterpret_cast<Cese599_project2Doc*>(m_pDocument); }
#endif

