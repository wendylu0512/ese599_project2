
// ese599_project2View.cpp : implementation of the Cese599_project2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ese599_project2.h"
#endif

#include "ese599_project2Doc.h"
#include "ese599_project2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cese599_project2View

IMPLEMENT_DYNCREATE(Cese599_project2View, CScrollView)

BEGIN_MESSAGE_MAP(Cese599_project2View, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Cese599_project2View construction/destruction

Cese599_project2View::Cese599_project2View()
{
	// TODO: add construction code here
	
	
}

Cese599_project2View::~Cese599_project2View()
{
}

BOOL Cese599_project2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}


// Cese599_project2View drawing

void Cese599_project2View::OnDraw(CDC* pDC)
{
	Cese599_project2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Screen scr = (*pDoc).get_main_scr();
	CPen pen_scr(PS_SOLID, 2, RGB(0, 0, 0));
	CPen pen_grid(PS_DASH, 0, RGB(128, 128, 128));

	pDC->SelectObject(pen_scr);
	pDC->Rectangle(scr.get_left(), scr.get_top(), scr.get_right(), scr.get_bottom());

	pDC->SelectObject(pen_grid);
	for (int i = (int)(scr.get_width() / 10.0); i < (int)scr.get_width(); i += (int)(scr.get_width() / 10.0))
	{
		pDC->MoveTo(scr.get_left(), scr.get_top() + i);
		pDC->LineTo(scr.get_right(), scr.get_top() + i);
		pDC->MoveTo(scr.get_left() + i, scr.get_top());
		pDC->LineTo(scr.get_left() + i, scr.get_bottom());
	}

	// draw sub-screens
	pDC->SelectObject(pen_scr);
	for (int i = 0; i < 4; i++)
	{
		string str_cam = "cam";
		CString cstr_cam(str_cam.c_str());
		cstr_cam.AppendChar('0' + i);
		scr = (*pDoc).get_sub_scr(i);
		pDC->Rectangle(scr.get_left(), scr.get_top(), scr.get_right(), scr.get_bottom());
		pDC->TextOutW(scr.get_right(), scr.get_top() + 5, cstr_cam);
	}

	this->draw_obj(pDC, (*pDoc).get_obj_coord(), (*pDoc).get_main_scr());

	this->draw_text(pDC, (*pDoc).get_cam(0), 0);
	this->draw_text(pDC, (*pDoc).get_cam(1), 1);
	this->draw_text(pDC, (*pDoc).get_cam(2), 2);
	this->draw_text(pDC, (*pDoc).get_cam(3), 3);


	//placement of counter/time ***********************************************************************


	CString temp;
	int compare = this->counter;
	temp.Format(_T("Time: %d"), this->counter, compare);
	pDC->TextOutW(770, 760, temp);
	

	this->draw_cam(pDC, (*pDoc).get_cam(0), 0);
	this->draw_cam(pDC, (*pDoc).get_cam(1), 1);
	this->draw_cam(pDC, (*pDoc).get_cam(2), 2);
	this->draw_cam(pDC, (*pDoc).get_cam(3), 3);

	this->draw_obj_on_sub(pDC, (*pDoc).get_cam(0).coord_on_screen((*pDoc).get_obj_coord()), (*pDoc).get_sub_scr(0), (*pDoc).get_cam(0), 0);
	this->draw_obj_on_sub(pDC, (*pDoc).get_cam(1).coord_on_screen((*pDoc).get_obj_coord()), (*pDoc).get_sub_scr(1), (*pDoc).get_cam(1), 1);
	this->draw_obj_on_sub(pDC, (*pDoc).get_cam(2).coord_on_screen((*pDoc).get_obj_coord()), (*pDoc).get_sub_scr(2), (*pDoc).get_cam(2), 2);
	this->draw_obj_on_sub(pDC, (*pDoc).get_cam(3).coord_on_screen((*pDoc).get_obj_coord()), (*pDoc).get_sub_scr(3), (*pDoc).get_cam(3), 3);

	this->draw_grid_on_sub(pDC, (*pDoc).get_cam(0), (*pDoc).get_sub_scr(0), (*pDoc).get_room());
	this->draw_grid_on_sub(pDC, (*pDoc).get_cam(1), (*pDoc).get_sub_scr(1), (*pDoc).get_room());
	this->draw_grid_on_sub(pDC, (*pDoc).get_cam(2), (*pDoc).get_sub_scr(2), (*pDoc).get_room());
	this->draw_grid_on_sub(pDC, (*pDoc).get_cam(3), (*pDoc).get_sub_scr(3), (*pDoc).get_room());
	
	//this->find_localzones(pDC, (*pDoc).get_cam(0), (*pDoc).get_sub_scr(0), 0);
	//this->find_localzones(pDC, (*pDoc).get_cam(1), (*pDoc).get_sub_scr(0), 1);
	//this->find_localzones(pDC, (*pDoc).get_cam(2), (*pDoc).get_sub_scr(0), 2);
	//this->find_localzones(pDC, (*pDoc).get_cam(3), (*pDoc).get_sub_scr(0), 3);

	//this->localzones(0);
	//this->localzones(1);
	//this->localzones(2);
	//this->localzones(3);
}
	
//////////////////////////////



///////////////////////


void Cese599_project2View::draw_text(CDC* pDC, Camera cam, int i)
{
	int fixmargin = 40;
	CString str_place(("cam" + std::to_string(i) + ":  " + cam.to_string_placement()).c_str());
	pDC->TextOutW(770, 500 + fixmargin + (i * 55), str_place);
	CString str_zone0(cam.to_string_zone(0).c_str());
	pDC->TextOutW(770, 520 + fixmargin + (i * 55), str_zone0);
	//CString str_zone1(cam.to_string_zone(1).c_str());
	//pDC->TextOutW(770, 540 + fixmargin + (i * 55), str_zone1);
//	CString mapshow(localzones(0).c_str());
//	pDC->TextOutW(1200, 500 + (i * 55), str_zone1);
	
}

void Cese599_project2View::draw_cam(CDC* pDC, Camera cam, int i)
{
	Cese599_project2Doc* pDoc = GetDocument();
	Screen scr = (*pDoc).get_main_scr();
	CPen pen_cam(PS_SOLID, 5, RGB(0, 128, 0));
	CPen pen_cov(PS_DOT, 0, RGB(255, 0, 0));  //camera coverage in global view
	pDC->SelectObject(pen_cam);
	
	int x_offset = 0;
	int y_offset = 0;

	if (cam.get_x() == 0)
		x_offset = 4;
	else if (cam.get_x() == (*pDoc).get_room_dimension().get_x())
		x_offset = -4;
	if (cam.get_y() == 0)
		y_offset = -4;
	else if (cam.get_y() == (*pDoc).get_room_dimension().get_y())
		y_offset = 4;

	pDC->Rectangle(scr.get_left() + (int)(cam.get_x()*scr.get_s()) - 5 + x_offset   //camera point region 
		, scr.get_bottom() - (int)(cam.get_y()*scr.get_s() - 5) + y_offset
		, scr.get_left() + (int)(cam.get_x() * scr.get_s() + 5) + x_offset
		, scr.get_bottom() - (int)(cam.get_y()*scr.get_s() + 5) + y_offset);
	
	CString str("cam");
	str.AppendChar('0' + i);

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOutW(scr.get_left() + (int)(cam.get_x()*scr.get_s()) - 20
		, scr.get_bottom() - (int)(cam.get_y()*scr.get_s()) + 10
		, str);

	pDC->SelectObject(pen_cov);
	pDC->MoveTo((int)(cam.get_top_left_corner().get_x()*scr.get_s()) + scr.get_left()   // camera coverage region
		, scr.get_bottom() - (int)(cam.get_top_left_corner().get_y() *scr.get_s()));
	pDC->LineTo((int)(cam.get_top_right_corner().get_x()*scr.get_s()) + scr.get_left()
		, scr.get_bottom() - (int)(cam.get_top_right_corner().get_y() *scr.get_s()));
	pDC->LineTo((int)(cam.get_bottom_right_corner().get_x()*scr.get_s()) + scr.get_left()
		, scr.get_bottom() - (int)(cam.get_bottom_right_corner().get_y() *scr.get_s()));
	pDC->LineTo((int)(cam.get_bottom_left_corner().get_x()*scr.get_s()) + scr.get_left()
		, scr.get_bottom() - (int)(cam.get_bottom_left_corner().get_y() * scr.get_s()));
	pDC->LineTo((int)(cam.get_top_left_corner().get_x()*scr.get_s()) + scr.get_left()
		, scr.get_bottom() - (int)(cam.get_top_left_corner().get_y() *scr.get_s()));
}



void Cese599_project2View::draw_obj_on_sub(CDC* pDC, Coord2 obj, Screen scr,Camera cam, int k)
{
	int fixmargin = 40; // fix the position of the sub-screen
	int a = 10;  // change a and b to change number of local grids
	int b = 10;  // total local grids = a x b : b rows * a columns

	string localstr;
	int zone_in;   //local grid number

	int objx = (int)(obj.get_x()*scr.get_s());   //object x position in subscreen
	int objy = (int)(obj.get_y()*scr.get_s());	//object y position in subscreen
	int scrwidth = (int)(scr.get_width());	//subscreen width
	int scrheight = (int)(scr.get_height());	//subscreen height

	string strzones;

	int zone_left;
	int zone_right;
	int zone_top;
	int zone_bottom;

	Coord2 ztemp;	


	int zone_prev;
	int zone_cur;

	string map;


	bool found = false;
	zones_mapped.clear();
	zone_prev = -1;

	if (objx >= 0			//if object detected in subscreen
		&& objx <= scr.get_width()
		&& objy >= 0
		&& objy <= scr.get_height())
	{
		zone_in = ((objx / (scrwidth / a))*b) + ((scrheight - objy) / (scrheight / b));   // find local zone object is in
		localstr += (std::to_string(zone_in) + " ");

		zone_left = (int)(floor(objx / (scrwidth / a)) * (scrwidth / a));	//left border, calculated
		zone_right = (int)(zone_left + (scrwidth / a));
		zone_top = (int)(floor(objy / (scrheight / b)) * (scrheight / b));
		zone_bottom = (int)(zone_top + (scrheight / b));
		/////////////////

		//cout << endl << "Zone IN: " << zone_in << endl;
		//cout << "Left border = " << zone_left << " Right Border = " << zone_right << endl;
		//cout << "Top border = " << zone_top << " Bottom Border = " << zone_bottom << endl;
		
		//Cese599_project2Doc* pDoc = GetDocument();

		//cout << "Object's CUrrent Position: " << (int)(obj.get_x()*(pDoc->get_main_scr().get_s())) << "," << (int)(obj.get_y()*(pDoc->get_main_scr().get_s())) << endl;
		//cout << "Object's CUrrent Position2: " << obj.get_x()<< "," << obj.get_y()<< endl;

		Coord2 mytemp = cam.cam_to_world(Coord2(zone_left, zone_bottom));
		Coord2 top_right = cam.cam_to_world(Coord2(zone_right, zone_top));
		cout << "Transformed Border (Bottom Left): " << mytemp.to_string() << "TOP RIGHT: " << top_right.to_string() << endl;

		////////////////
		for (int w = zone_left*2; w < zone_right*2; w+=2)
		{
			for (int h = zone_top*2; h < zone_bottom*2; h+=2)
			{
				ztemp = cam.cam_to_world(Coord2(w, h));
				// cout << "ZTemp: " << ztemp.to_string() << endl;
				//zone_cur = (int)((ztemp.get_x() / (scrwidth / b))*a) + (int)(ztemp.get_y() / (scrheight / b));
				zone_cur = ((((int)ztemp.get_x() / 100) * 10) + ((int)ztemp.get_y() / 100));
				
				if ((zone_cur != zone_prev) && (zone_cur != -1))
				{
					found = false;
					for (int g = 0; g < zones_mapped.size(); g++)  //find if zone already exists in vector/list to avoid duplicate
					{
						if (zones_mapped[g] == zone_cur)
						{
							found = true;	//found duplicate zone_mapped already, no need to add again
							break;
						}
					}
					if (!found)		//if found, just add onto vector(zones_mapped)
					{
						zones_mapped.push_back(zone_cur);
						cout << "**** Adding NEW Zone Map: " << zone_cur << endl;
					}
				}
				zone_prev = zone_cur;
			}
		}

		sort(zones_mapped.begin(), zones_mapped.end());

	}
		//for (int m = 0; m < zones_mapped.size(); m++)
	
	for (int p = 0; p < zones_mapped.size(); p++)
	{

		map += (std::to_string(zones_mapped[p]) + " ");
	}
	CString mapto("Mapped to: ");
	CString mapstr(map.c_str());
	pDC->TextOutW(1120, 500 + fixmargin + (k * 55), mapto);
	pDC->TextOutW(1200, 500 + fixmargin + (k * 55), mapstr);

			CString locc("Local: ");
			CString locals(localstr.c_str());
			pDC->TextOutW(1030, 500 + fixmargin + (k * 55), locc);
			pDC->TextOutW(1080, 500 + fixmargin + (k * 55), locals);

		
	
		//Draw the local grids///
		CPen pen_grid(PS_DASH, 0, RGB(255, 0, 0));  
		pDC->SelectObject(pen_grid);
		pDC->Rectangle(scr.get_left(), scr.get_top(), scr.get_right(), scr.get_bottom());

		//vertical lines
		for (int j = (int)(scr.get_width() / a); j < (int)scr.get_width(); j += (int)(scr.get_width() / a))
		{

			pDC->MoveTo(scr.get_left() + j, scr.get_top());
			pDC->LineTo(scr.get_left() + j, scr.get_bottom());

		//horizontal lines
		for (int k = (int)(scr.get_height() / b); k < (int)scr.get_height(); k += (int)(scr.get_height() / b))
			{
				pDC->MoveTo(scr.get_left(), scr.get_top() + k);
				pDC->LineTo(scr.get_right(), scr.get_top() + k);
			}
		}

	///Draw the object in subscreens

		if ((int)(obj.get_x()*scr.get_s()) >= 0
			&& (int)(obj.get_x()*scr.get_s()) <= scr.get_width()
			&& (int)(obj.get_y()*scr.get_s()) >= 0
			&& (int)(obj.get_y()*scr.get_s()) <= scr.get_height())
		{
			CPen pen(PS_SOLID, 5, RGB(0, 0, 128));
			pDC->SelectObject(pen);
			pDC->Ellipse(scr.get_left() + (int)(obj.get_x()*scr.get_s()) - 5
				, scr.get_top() + (int)(obj.get_y()*scr.get_s() - 5)
				, scr.get_left() + (int)(obj.get_x() * scr.get_s() + 5)
				, scr.get_top() + (int)(obj.get_y()*scr.get_s() + 5));

		}

	}

/*
string Cese599_project2View::localzones(int k)
{
	int a = 3;  // change a and b to change number of local grids
	int b = 3;  // total local grids = a x b

	Screen scr;
	string localstr;
	int zone_in;   //local grid number

	int scrwidth = (int)(scr.get_width());	//subscreen width
	int scrheight = (int)(scr.get_height());	//subscreen height

	string strzones;

	for (int i = 0; i < scrwidth; i+=a)
	{
		for (int j = 0; j < scrheight; j += b)
		{
			zone_in = ((i / (scrwidth / b))*a) + (j / (scrheight / b));   // find local zone object is in
			strzones[zone_in] = zone_in;
		}
	}



	return "map: " + strzones;


}



void Cese599_project2View::map_zones(CDC* pDC, Camera cam, Screen scr, int h)

{
	int a = 3;  // change a and b to change number of local grids
	int b = 3;  // total local grids = a x b

	string localstr;
	int zone_in;   //local grid number

	map <string,int> mapping;

	int scrwidth = (int)(scr.get_width());	//subscreen width
	int scrheight = (int)(scr.get_height());	//subscreen height







}

*/


void Cese599_project2View::draw_obj(CDC* pDC, Coord2 obj, Screen scr)
{
	if ((int)(obj.get_x()*scr.get_s()) >= 0
		&& (int)(obj.get_x()*scr.get_s()) <= scr.get_width()
		&& (int)(obj.get_y()*scr.get_s()) >= 0
		&& (int)(obj.get_y()*scr.get_s()) <= scr.get_height())
	{
		CPen pen(PS_SOLID, 5, RGB(0, 0, 128));
		pDC->SelectObject(pen);
		pDC->Ellipse(scr.get_left() + (int)(obj.get_x()*scr.get_s()) - 5, scr.get_bottom() - (int)(obj.get_y()*scr.get_s() - 5)
			, scr.get_left() + (int)(obj.get_x() * scr.get_s() + 5), scr.get_bottom() - (int)(obj.get_y()*scr.get_s() + 5));
	}

	cout << "Object position in Main: " << (int)(obj.get_x()) << "," << (int)(obj.get_y()) << endl;
}

void Cese599_project2View::draw_grid_on_sub(CDC* pDC, Camera cam, Screen scr, World room)
{

	int x_pix = 0;
	int y_pix = 0;

	Coord2 temp;

	for (int i = 0; i <= room.get_width(); i++)
	{
		temp = Coord2(i, y_pix);
		if (cam.is_on_screen(temp))
		{
			temp = cam.coord_on_screen(temp);
			pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(0, 0, 0));
		}

		temp = Coord2(i, room.get_length());
		if (cam.is_on_screen(temp))
		{
			temp = cam.coord_on_screen(temp);
			pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(0, 0, 0));
		}
	}
	
	for (int i = 0; i <= room.get_length(); i++)
	{
		temp = Coord2(x_pix, i);
		if (cam.is_on_screen(temp))
		{
			temp = cam.coord_on_screen(temp);
			pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(0, 0, 0));
		}

		temp = Coord2(room.get_width(), i);
		if (cam.is_on_screen(temp))
		{
			temp = cam.coord_on_screen(temp);
			pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(0, 0, 0));
		}
	}

	y_pix = 0;

	for (int j = 0; j < 10; j++)
	{
		y_pix += 100;
		for (int i = 0; i <= room.get_width(); i += 2)
		{
			temp = Coord2(i, y_pix);
			if (cam.is_on_screen(temp))
			{
				temp = cam.coord_on_screen(temp);
				pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(128, 128, 128));
			}
		}
	}

	x_pix = 0;
	for (int j = 0; j < 10; j++)
	{
		x_pix += 100;
		for (int i = 0; i <= room.get_length(); i += 2)
		{
			temp = Coord2(x_pix, i);
			if (cam.is_on_screen(temp))
			{
				temp = cam.coord_on_screen(temp);
				pDC->SetPixel((int)(scr.get_left() + temp.get_x() * scr.get_s()), (int)(scr.get_top() + temp.get_y() * scr.get_s()), RGB(128, 128, 128));
			}
		}
	}

}

void Cese599_project2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1410;
	sizeTotal.cy = 800;
	
	SetScrollSizes(MM_TEXT, sizeTotal);


}


// Cese599_project2View printing

BOOL Cese599_project2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cese599_project2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cese599_project2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Cese599_project2View diagnostics

#ifdef _DEBUG
void Cese599_project2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void Cese599_project2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

Cese599_project2Doc* Cese599_project2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cese599_project2Doc)));
	return (Cese599_project2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cese599_project2View message handlers


int angles[4][3] = 
{
	{ 40, 0, -40 },
	{ 60, 35, 10 },
	{ 100, 125, 150 },
	{ 130, 180, 230 } 
};


void Cese599_project2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	// TODO: Add your message handler code here and/or call default
	if (nChar == ' ')
	{
		this->counter += 1;	//increment counter***************************************************************
		(*GetDocument()).SpaceKey();
		
		
		//move cam0 periodically
		int mod_result0 = this->counter % 4;
		switch (mod_result0)
		{
		case 0: 
			(*GetDocument()).get_camm(0)->moveTo(300, 0, 200, angles[0][0], -55);
			break;
		case 1:	
			(*GetDocument()).get_camm(0)->moveTo(300, 0, 200, angles[0][1], -55);
			break;
		case 2: 
			(*GetDocument()).get_camm(0)->moveTo(300, 0, 200, angles[0][2], -55);
			break;
		case 3: 
			(*GetDocument()).get_camm(0)->moveTo(300, 0, 200, angles[0][1], -55);
			break;
		}

		//move cam1 periodically
		int mod_result1 = this->counter % 4;
		switch (mod_result1)
		{
		case 0:
			(*GetDocument()).get_camm(1)->moveTo(900, 0, 200, angles[1][0], -50);
			break;
		case 1:
			(*GetDocument()).get_camm(1)->moveTo(900, 0, 200, angles[1][1], -50);
			break;
		case 2:
			(*GetDocument()).get_camm(1)->moveTo(900, 0, 200, angles[1][2], -50);
			break;
		case 3:
			(*GetDocument()).get_camm(1)->moveTo(900, 0, 200, angles[1][1], -50);
			break;
		}
		
		//move cam2 periodically
		int mod_result2 = this->counter % 4;
		switch (mod_result2)
		{
		case 0:
			(*GetDocument()).get_camm(2)->moveTo(1000, 900, 200, angles[2][0], -55);
			break;
		case 1:
			(*GetDocument()).get_camm(2)->moveTo(1000, 900, 200, angles[2][1], -55);
			break;
		case 2:
			(*GetDocument()).get_camm(2)->moveTo(1000, 900, 200, angles[2][2], -55);
			break;
		case 3:
			(*GetDocument()).get_camm(2)->moveTo(1000, 900, 200, angles[2][1], -55);
			break;
		}

		//move cam3 periodically
		int mod_result3 = this->counter % 4;
		switch (mod_result3)
		{
		case 0:
			(*GetDocument()).get_camm(3)->moveTo(300, 1000, 200, angles[3][0], -60);
			break;
		case 1:
			(*GetDocument()).get_camm(3)->moveTo(300, 1000, 200, angles[3][1], -60);
			break;
		case 2:
			(*GetDocument()).get_camm(3)->moveTo(300, 1000, 200, angles[3][2], -60);
			break;
		case 3:
			(*GetDocument()).get_camm(3)->moveTo(300, 1000, 200, angles[3][1], -60);
			break;
		}

	}
	/*  4 direction keys
	if (nChar == 'I')
		(*GetDocument()).up();
	if (nChar == 'M')
		(*GetDocument()).down();
	if (nChar == 'J')
		(*GetDocument()).left();
	if (nChar == 'K')
		(*GetDocument()).right();
	
	*/

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
