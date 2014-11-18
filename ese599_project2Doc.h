
// ese599_project2Doc.h : interface of the Cese599_project2Doc class
//


#pragma once
#include "Screen.h"
#include "Camera.h"
#include "Camera_dist_coeff.h"
#include "Camera_int_param.h"
#include "Coord2.h"
#include "Coord3.h"
#include "World.h"


class Cese599_project2Doc : public CDocument
{
protected: // create from serialization only
	Cese599_project2Doc();
	DECLARE_DYNCREATE(Cese599_project2Doc)


// Attributes
public:

private:
	Screen main_scr;
	Screen sub_scr[4];
	Screen map_scr; ////////// map test
	World room;
	Camera cam[4];
	int counter = 0;


// Operations
public:
	Screen get_main_scr() { return main_scr; }
	Screen get_sub_scr(int index) { return sub_scr[index]; }
	Screen get_map_scr() { return map_scr; }   ///////////////// map test
	Coord2 get_obj_coord() { return Coord2(room.get_obj().get_x(), room.get_obj().get_y()); }
	Camera get_cam(int index) { return cam[index]; }
	Coord2 get_room_dimension() { return Coord2(room.get_width(), room.get_length()); }
	World get_room() { return room; }
	Camera * get_camm(int index) { return & this->cam[index]; }

	void SpaceKey();


	//void up();
	//void down();
	//void left();
	//void right();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cese599_project2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
