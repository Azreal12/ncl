/*
 *	$Id: devices.c,v 1.2 1991-01-09 11:09:36 clyne Exp $
 */
/***********************************************************************
*                                                                      *
*                          Copyright (C)  1990                         *
*            University Corporation for Atmospheric Research           *
*                          All Rights Reserved                         *
*                                                                      *
*                      NCAR View V3.01 - UNIX Release                  *
*                                                                      *
***********************************************************************/
/*
 *	devices.c:
 *
 *	Author		John Clyne	(clyne@redcloud.ucar.edu)
 *			
 *	Date		Mon Nov 28 14:45:24 MST 1988
 *
 *		This file contains the devices ctrans supports. To
 *	add a new device begin here by adding the device and its functions
 *	to the jump table
 */

#include	<stdio.h>
#include	<cterror.h>
#include	<cgm_tools.h>
#include	"cgmc.h"
#define		DEVICES
#include	"devices.h"

int	devicenum = (sizeof(devices)/sizeof(struct device));

/*
 *	Declarations for all the function in the Jump Table
 */

/*
 *	The functions for the GraphCap and FontCap processing
 *	also the funtions for setting the default-table values.
 */

/*	Class 0	*/

Ct_err BegMF(), EndMF(), BegPic(), BegPicBody(), EndPic();

/*	Class 1	*/

Ct_err MFVersion(), MFDesc(), VDCType(), IntergerPrec(), RealPrec(), 
	IndexPrec(),
    ColrPrec(), ColrIndexPrec(), MaxColrIndex(), ColrValueExt(), MFElemList(),
    MFDefaults(), FontList(), CharSetList(), CharCoding();

/*	Class 2	*/

Ct_err ScaleMode(), ColrMode(), LineWidthMode(), MarkerSizeMode(), EdgeWidthMode(),
    VDCExt(), BackColr();


/*	Class 3	*/

Ct_err VDCIntergerPrec(), VDCRealPrec(), AuxColr(), Transparency(), ClipRect(),
    Clip();

/*	Class 4	*/

Ct_err PolyLine(), DisjtLine(), PolyMarker(), Text(), RestrText(), ApndText(),
    Polygon(), PolygonSet(), CellArray(), GDP(), Rect(), Circle(), Arc3Pt(),
    Arc3PtClose(), ArcCtr(), ArcCtrClose(), Ellipse(), EllipArc(),
    EllipArcClose();

/*	Class 5	*/

Ct_err LineIndex(), LineType(), LineWidth(), LineColr(), MarkerIndex(),
    MarkerType(), MarkerSize(), MarkerColr(), TextIndex(), TextFontIndex(),
    TextPrec(), CharExpan(), CharSpace(), TextColr(), CharHeight(), CharOri(),
    TextPath(), TextAlign(), CharSetIndex(), AltCharSetIndex(), FillIndex(),
    IntStyle(), FillColr(), HatchIndex(), PatIndex(), EdgeIndex(), EdgeType(),
    EdgeWidth(), EdgeColr(), EdgeVis(), FillRefPt(), PatTable(), PatSize(),
    ColrTable(), ASF();

/*	Class 6	*/

Ct_err Escape();

/*	Class 7	*/

Ct_err Message(), ApplData();

#ifdef CGI

/*
 *				CGI
 *
 *	The function that inturn call the CGI library
 */

/*	Class 0	*/

Ct_err	 CGIBegMF(), CGIEndMF(), CGIBegPic(), CGIBegPicBody(), CGIEndPic();

/*	Class 1	*/

Ct_err	CGIMFVersion(), CGIMFDesc(), 
	CGIMFElemList(), 
	CGIMFDefaults(), CGICharSetList(), CGICharCoding();

/*	Class 2	*/

Ct_err	CGIBackColr();

/*	Class 3	*/

Ct_err	CGIAuxColr(), CGITransparency(); 

/*	Class 4	*/

Ct_err	CGIPolyLine(), CGIDisjtLine(), CGIPolyMarker(), Text(), 
	CGIRestrText(), CGIApndText(), CGIPolygon(), CGIPolygonSet(), 
	CGICellArray(), CGIGDP(), CGIRect(), CGICircle(), CGIArc3Pt(), 
	CGIArc3PtClose(), CGIArcCtr(), CGIArcCtrClose(), CGIEllipse(), 
	CGIEllipArc(), CGIEllipArcClose();

/*	Class 5	*/

Ct_err	CGILineIndex(), CGIMarkerIndex(), 
	CGITextIndex(), CGITextPrec(), 
	CGICharSetIndex(),
	CGIAltCharSetIndex(), CGIFillIndex(),
	CGIPatIndex(),
	CGIEdgeIndex(), CGIPatTable(), 
	CGIColrTable(), CGIASF();

/*	Class 6	*/

Ct_err	CGIEscape();

/*	Class 7	*/

Ct_err	CGIMessage(), CGIApplData();

#endif CGI


#ifdef X11

/*
 *				X11
 *
 *	The functions that inturn call the X11 library
 *	note: some functions do not exist because the interface
 *	uses the gcap version. This is true most often when  a CGM
 *	command sets defaults	
 */

/* 	Class 0	*/	

Ct_err X11_BegMF(), X11_EndMF(), X11_BegPic(), X11_BegPicBody(), X11_EndPic();

/*	Class 1	*/

Ct_err X11_MFVersion(), X11_MFDesc(), X11_MFElemList(), X11_MFDefaults(), 
    X11_CharSetList(); 

/*	Class 2	*/


/*	Class 3	*/

Ct_err X11_AuxColr();

/*	Class 4	*/	

Ct_err X11_PolyLine(), X11_DisjtLine(), X11_PolyMarker(), X11_RestrText(), 
    X11_ApndText(), X11_Polygon(), X11_PolygonSet(), X11_CellArray(), X11_GDP(),
    X11_Rect(), X11_Circle(), X11_Arc3Pt(), X11_Arc3PtClose(), X11_ArcCtr(), 
    X11_ArcCtrClose(), X11_Ellipse(), X11_EllipArc(), X11_EllipArcClose();

/*	Class 5	*/

Ct_err X11_PatTable(), X11_ColrTable(), X11_ASF();

/*	Class 6	*/

Ct_err X11_Escape();

/*	Class 7	*/

Ct_err X11_Message(), X11_ApplData();


/*
 *	When the X11 driver is define the XBFR driver gets defined
 *	as well.
 */
Ct_err	xbfr_BegMF(), xbfr_BegPic(), xbfr_BegPicBody(), xbfr_EndPic();

#endif X11





#ifdef	CTXT
/*
 *	The functions for the Clear Text driver
 */

/*	Class 0	*/

Ct_err	CTXT_NoOp(), CTXT_BegMF(), CTXT_EndMF(), CTXT_BegPic(), 
	CTXT_BegPicBody(), CTXT_EndPic();

/*	Class 1	*/

Ct_err	CTXT_MFVersion(), CTXT_MFDesc(), CTXT_VDCType(),CTXT_IntergerPrec(),
	CTXT_RealPrec(), CTXT_IndexPrec(), CTXT_ColrPrec(), 
	CTXT_ColrIndexPrec(), CTXT_MaxColrIndex(), CTXT_ColrValueExt(), 
	CTXT_MFElemList(), CTXT_MFDefaults(), CTXT_FontList(), 
	CTXT_CharSetList(), CTXT_CharCoding();

/*	Class 2	*/

Ct_err	CTXT_ScaleMode(), CTXT_ColrMode(), CTXT_LineWidthMode(), 
	CTXT_MarkerSizeMode(), CTXT_EdgeWidthMode(), CTXT_VDCExt(), 
	CTXT_BackColr();


/*	Class 3	*/

Ct_err	CTXT_VDCIntergerPrec(), CTXT_VDCRealPrec(), CTXT_AuxColr(), 
	CTXT_Transparency(), CTXT_ClipRect(), CTXT_Clip();

/*	Class 4	*/

Ct_err	CTXT_PolyLine(), CTXT_DisjtLine(), CTXT_PolyMarker(), CTXT_Text(), 
	CTXT_RestrText(), CTXT_ApndText(), CTXT_Polygon(), 
	CTXT_PolygonSet(), CTXT_CellArray(), CTXT_GDP(), CTXT_Rect(), 
	CTXT_Circle(), CTXT_Arc3Pt(), CTXT_Arc3PtClose(), CTXT_ArcCtr(), 
	CTXT_ArcCtrClose(), CTXT_Ellipse(), CTXT_EllipArc(),
	CTXT_EllipArcClose();

/*	Class 5	*/

Ct_err	CTXT_LineIndex(), CTXT_LineType(), CTXT_LineWidth(),CTXT_LineColr(),
	CTXT_MarkerIndex(), CTXT_MarkerType(), CTXT_MarkerSize(), 
	CTXT_MarkerColr(), CTXT_TextIndex(), CTXT_TextFontIndex(),
	CTXT_TextPrec(), CTXT_CharExpan(), CTXT_CharSpace(),CTXT_TextColr(),
	CTXT_CharHeight(), CTXT_CharOri(), CTXT_TextPath(),CTXT_TextAlign(),
	CTXT_CharSetIndex(), CTXT_AltCharSetIndex(), CTXT_FillIndex(),
	CTXT_IntStyle(), CTXT_FillColr(), CTXT_HatchIndex(),CTXT_PatIndex(),
	CTXT_EdgeIndex(), CTXT_EdgeType(), CTXT_EdgeWidth(),CTXT_EdgeColr(),
	CTXT_EdgeVis(), CTXT_FillRefPt(), CTXT_PatTable(), CTXT_PatSize(),
	CTXT_ColrTable(), CTXT_ASF();

/*	Class 6	*/

Ct_err	CTXT_Escape();

/*	Class 7	*/

Ct_err	CTXT_Message(), CTXT_ApplData();

#endif	CTXT

#ifdef	SunV
/*
 *
 *		The Sun SunView driver
 * 
 */
/*	class 1	*/
Ct_err	SunV_BegMF(), SunV_EndMF(), SunV_BegPic(), SunV_BegPicBody(), 
	SunV_EndPic();

/*	Class 4	*/


Ct_err	SunV_PolyLine(), SunV_PolyMarker(), SunV_Polygon(), SunV_CellArray();
    
   

/*	Class 5	*/

Ct_err	SunV_ColrTable(); 

#endif
#ifdef	SunR
/*
 *
 *		The Sun raster filter
 * 
 */
/*	class 1	*/
Ct_err	SunR_BegMF(), SunR_EndMF(), SunR_BegPic(), SunR_BegPicBody(), 
	SunR_EndPic();

/*	Class 4	*/


Ct_err	SunR_PolyLine(), SunR_PolyMarker(), SunR_Polygon(), SunR_CellArray();
    
   

/*	Class 5	*/

Ct_err	SunR_ColrTable(); 

#endif
/*ARGSUSED*/
Ct_err	noop(c)
CGMC *c;
{
}



/*
 * The Jumptable 
 */
Ct_err  (*cmdtab[][MAXCLASS+1][MAXFUNCPERCLASS+1])() = {
	{
	/* Class 0 */
	{
	noop, BegMF, EndMF, BegPic, BegPicBody, 
	EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL,
	},
	/* Class 1 */
	{
	NULL, MFVersion, MFDesc, VDCType, IntergerPrec, 
	RealPrec, IndexPrec, ColrPrec, ColrIndexPrec, MaxColrIndex, 
	ColrValueExt, MFElemList, MFDefaults, FontList, CharSetList, 
	CharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode, 
	EdgeWidthMode, VDCExt, BackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, AuxColr, Transparency, 
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, PolyLine, DisjtLine, PolyMarker, Text, 
	RestrText, ApndText, Polygon, PolygonSet, CellArray, 
	GDP, Rect, Circle, Arc3Pt, Arc3PtClose, 
	ArcCtr, ArcCtrClose, Ellipse, EllipArc, EllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, LineIndex, LineType, LineWidth, LineColr, 
	MarkerIndex, MarkerType, MarkerSize, MarkerColr, TextIndex, 
	TextFontIndex, TextPrec, CharExpan, CharSpace, TextColr, 
	CharHeight, CharOri, TextPath, TextAlign, CharSetIndex, 
	AltCharSetIndex, FillIndex, IntStyle, FillColr, HatchIndex,
	PatIndex, EdgeIndex, EdgeType, EdgeWidth, EdgeColr, 
	EdgeVis, FillRefPt, PatTable, PatSize, ColrTable, 
	ASF,
	},
	/* Class 6 */
	{
	NULL, Escape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, Message, ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},

#ifdef CGI 

	/* The CGI functions */

	{
	/* Class 0 */
	{
	noop, CGIBegMF, CGIEndMF, CGIBegPic, CGIBegPicBody,
	CGIEndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, CGIMFVersion, CGIMFDesc, VDCType, IntergerPrec,
	RealPrec, IndexPrec,ColrPrec,ColrIndexPrec,MaxColrIndex,
	ColrValueExt,CGIMFElemList,CGIMFDefaults,FontList,
	CGICharSetList, CGICharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode,
	EdgeWidthMode, VDCExt, CGIBackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, CGIAuxColr, CGITransparency,
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, CGIPolyLine, CGIDisjtLine, CGIPolyMarker, Text,
	CGIRestrText, CGIApndText, CGIPolygon, CGIPolygonSet, CGICellArray,
	CGIGDP, CGIRect, CGICircle, CGIArc3Pt, CGIArc3PtClose,
	CGIArcCtr, CGIArcCtrClose, CGIEllipse, CGIEllipArc, CGIEllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, CGILineIndex, LineType, LineWidth, LineColr,
	CGIMarkerIndex,MarkerType,MarkerSize,MarkerColr,
	CGITextIndex, TextFontIndex, TextPrec, CharExpan, 
	CharSpace, TextColr, CharHeight, CharOri, 
	TextPath, TextAlign, CGICharSetIndex, CGIAltCharSetIndex,
	CGIFillIndex,IntStyle,FillColr,HatchIndex,
	CGIPatIndex, CGIEdgeIndex, EdgeType, EdgeWidth, EdgeColr,
	EdgeVis, FillRefPt, CGIPatTable, PatSize, CGIColrTable,
	CGIASF,
	},
	/* Class 6 */
	{
	NULL, CGIEscape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, CGIMessage, CGIApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},

#endif CGI

#ifdef X11 

	/* The X11_ functions 
	 *
	 *	note the following functions do not exist because they 
	 * are handled by the coresponding graph cap version of the 
	 * function:
	 *
	 *	X11_VDCType(), X11_IntegerPrec(), X11_RealPrec(),
	 *	X11_IndexPrec(), X11_ColrPrec(), X11_ColrIndexPrec(),
	 *	X11_MaxColrIndex(), X11_ColrValueExt(), X11_CharCoding()
	 *
	 *		Class 2
	 *	X11_ScaleMode(), X11_ColrMode(), X11_LineWidthMode(),
	 *	X11_MarkerSizeMode(), X11_EdgeWidthMode(), X11_VDCExt()
	 *	X11_BackColr()
	 *
	 *		Class 3
	 *	X11_VDCIntegerPrec(), X11_VDCRealPrec(), X11_Transpanrecy()
	 *	X11_ClipRect(), X11_Clip()
	 *
	 *		Class 4
	 *	X11_text()
	 *
	 *		Class 5
	 *	X11_LineIndex(), X11_LineType()	X11_LineWidth(), X11_LineColr()
	 *	X11_MarkerIndex(), X11_MarkerType() X11_MarkerSize()
	 *	X11_MarkerColour(), X11_TextIndex(), X11_TextFontIndex()
	 *	X11_TextPrec() X11_CharExpan(),	X11_CharSpace(), X11_TextColr() 
	 *	X11_CharHeight(), X11_CharOri() X11_TextPath() X11_TextAlign() 
	 *	X11_CharSetIndex(), X11_AltCharSetIndex(), X11_FillIndex()
	 *	X11_IntStyle() X11_Fill_colr() X11_HatchIndex() X11_PatIndex()
	 *	X11_EdgeIndex(), X11_EdgeType(), X11_EdgeWidth() X11_EdgeColr()
	 *	X11_EdgeVis() X11_FillRefPt(), X11_PatSize()
	 */

	{
	/* Class 0 */
	{
	noop, X11_BegMF, X11_EndMF, X11_BegPic, X11_BegPicBody,
	X11_EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, X11_MFVersion, X11_MFDesc, VDCType, IntergerPrec,
	RealPrec, IndexPrec, ColrPrec, ColrIndexPrec, MaxColrIndex,
	ColrValueExt, X11_MFElemList, X11_MFDefaults, FontList,
	X11_CharSetList, CharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode,
	EdgeWidthMode, VDCExt, BackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, X11_AuxColr, Transparency,
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, X11_PolyLine, X11_DisjtLine, X11_PolyMarker, Text,
	X11_RestrText, X11_ApndText, X11_Polygon, X11_PolygonSet, X11_CellArray,
	X11_GDP, X11_Rect, X11_Circle, X11_Arc3Pt, X11_Arc3PtClose,
	X11_ArcCtr, X11_ArcCtrClose, X11_Ellipse, X11_EllipArc, X11_EllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, LineIndex, LineType, LineWidth, LineColr,
	MarkerIndex,MarkerType,MarkerSize,MarkerColr,
	TextIndex, TextFontIndex, TextPrec, CharExpan, 
	CharSpace, TextColr, CharHeight, CharOri, 
	TextPath, TextAlign, CharSetIndex, AltCharSetIndex,
	FillIndex,IntStyle,FillColr,HatchIndex,
	PatIndex, EdgeIndex, EdgeType, EdgeWidth, EdgeColr,
	EdgeVis, FillRefPt, X11_PatTable, PatSize, X11_ColrTable,
	X11_ASF,
	},
	/* Class 6 */
	{
	NULL, X11_Escape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, X11_Message, X11_ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},

	/*
	 *	Whenever the X11 driver gets defined the xbfr driver gets
	 * 	defined as well. xbfr uses all of the same X11 driver routines
	 *	except X11_BegMF, X11_BegPic, X11_BegPicBody and X11_EndPic
	 */
	{
	/* Class 0 */
	{
	noop, xbfr_BegMF, X11_EndMF, xbfr_BegPic, xbfr_BegPicBody,
	xbfr_EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, X11_MFVersion, X11_MFDesc, VDCType, IntergerPrec,
	RealPrec, IndexPrec, ColrPrec, ColrIndexPrec, MaxColrIndex,
	ColrValueExt, X11_MFElemList, X11_MFDefaults, FontList,
	X11_CharSetList, CharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode,
	EdgeWidthMode, VDCExt, BackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, X11_AuxColr, Transparency,
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, X11_PolyLine, X11_DisjtLine, X11_PolyMarker, Text,
	X11_RestrText, X11_ApndText, X11_Polygon, X11_PolygonSet, X11_CellArray,
	X11_GDP, X11_Rect, X11_Circle, X11_Arc3Pt, X11_Arc3PtClose,
	X11_ArcCtr, X11_ArcCtrClose, X11_Ellipse, X11_EllipArc, X11_EllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, LineIndex, LineType, LineWidth, LineColr,
	MarkerIndex,MarkerType,MarkerSize,MarkerColr,
	TextIndex, TextFontIndex, TextPrec, CharExpan, 
	CharSpace, TextColr, CharHeight, CharOri, 
	TextPath, TextAlign, CharSetIndex, AltCharSetIndex,
	FillIndex,IntStyle,FillColr,HatchIndex,
	PatIndex, EdgeIndex, EdgeType, EdgeWidth, EdgeColr,
	EdgeVis, FillRefPt, X11_PatTable, PatSize, X11_ColrTable,
	X11_ASF,
	},
	/* Class 6 */
	{
	NULL, X11_Escape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, X11_Message, X11_ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},

#endif X11


#ifdef CTXT 

	/*
	 *	The Clear Text portion of the jump table
	 */


	{
	/* Class 0 */
	{
	CTXT_NoOp, CTXT_BegMF, CTXT_EndMF, CTXT_BegPic, CTXT_BegPicBody,
	CTXT_EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, CTXT_MFVersion, CTXT_MFDesc, CTXT_VDCType, CTXT_IntergerPrec,
	CTXT_RealPrec, CTXT_IndexPrec, CTXT_ColrPrec, CTXT_ColrIndexPrec, 
	CTXT_MaxColrIndex, CTXT_ColrValueExt, CTXT_MFElemList, 
	CTXT_MFDefaults, CTXT_FontList, CTXT_CharSetList, CTXT_CharCoding, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	},
	/* Class 2 */
	{
	NULL, CTXT_ScaleMode, CTXT_ColrMode, CTXT_LineWidthMode, 
	CTXT_MarkerSizeMode, CTXT_EdgeWidthMode, CTXT_VDCExt, 
	CTXT_BackColr, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	},
	/* Class 3 */
	{
	NULL, CTXT_VDCIntergerPrec, CTXT_VDCRealPrec, CTXT_AuxColr, 
	CTXT_Transparency, CTXT_ClipRect, CTXT_Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL,
	},
	/* Class 4 */
	{
	NULL, CTXT_PolyLine, CTXT_DisjtLine, CTXT_PolyMarker, CTXT_Text,
	CTXT_RestrText, CTXT_ApndText, CTXT_Polygon, CTXT_PolygonSet, 
	CTXT_CellArray, CTXT_GDP, CTXT_Rect, CTXT_Circle, CTXT_Arc3Pt, 
	CTXT_Arc3PtClose, CTXT_ArcCtr, CTXT_ArcCtrClose, CTXT_Ellipse, 
	CTXT_EllipArc, CTXT_EllipArcClose, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	},
	/* Class 5 */
	{
	NULL, CTXT_LineIndex, CTXT_LineType, CTXT_LineWidth, CTXT_LineColr,
	CTXT_MarkerIndex,CTXT_MarkerType,CTXT_MarkerSize,CTXT_MarkerColr,
	CTXT_TextIndex, CTXT_TextFontIndex, CTXT_TextPrec, CTXT_CharExpan, 
	CTXT_CharSpace, CTXT_TextColr, CTXT_CharHeight, CTXT_CharOri, 
	CTXT_TextPath, CTXT_TextAlign, CTXT_CharSetIndex, 
	CTXT_AltCharSetIndex, CTXT_FillIndex,CTXT_IntStyle,CTXT_FillColr,
	CTXT_HatchIndex, CTXT_PatIndex, CTXT_EdgeIndex, CTXT_EdgeType, 
	CTXT_EdgeWidth, CTXT_EdgeColr, CTXT_EdgeVis, CTXT_FillRefPt, 
	CTXT_PatTable, CTXT_PatSize, CTXT_ColrTable, CTXT_ASF,
	},
	/* Class 6 */
	{
	NULL, CTXT_Escape, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL,
	},
	/* Class 7 */
	{
	NULL, CTXT_Message, CTXT_ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},
#endif CTXT

#ifdef	SunV

	{
	/* Class 0 */
	{
	noop, SunV_BegMF, SunV_EndMF, SunV_BegPic, SunV_BegPicBody,
	SunV_EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, MFVersion, MFDesc, VDCType, IntergerPrec,
	RealPrec, IndexPrec, ColrPrec, ColrIndexPrec, MaxColrIndex,
	ColrValueExt, MFElemList, MFDefaults, FontList,
	CharSetList, CharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode,
	EdgeWidthMode, VDCExt, BackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, AuxColr, Transparency,
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, SunV_PolyLine, DisjtLine, SunV_PolyMarker, Text,
	RestrText, ApndText, SunV_Polygon, PolygonSet, SunV_CellArray,
	GDP, Rect, Circle, Arc3Pt, Arc3PtClose,
	ArcCtr, ArcCtrClose, Ellipse, EllipArc, EllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, LineIndex, LineType, LineWidth, LineColr,
	MarkerIndex,MarkerType,MarkerSize,MarkerColr,
	TextIndex, TextFontIndex, TextPrec, CharExpan, 
	CharSpace, TextColr, CharHeight, CharOri, 
	TextPath, TextAlign, CharSetIndex, AltCharSetIndex,
	FillIndex,IntStyle,FillColr,HatchIndex,
	PatIndex, EdgeIndex, EdgeType, EdgeWidth, EdgeColr,
	EdgeVis, FillRefPt, PatTable, PatSize, SunV_ColrTable,
	ASF,
	},
	/* Class 6 */
	{
	NULL, Escape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, Message, ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},
#endif
#ifdef	SunR

	{
	/* Class 0 */
	{
	noop, SunR_BegMF, SunR_EndMF, SunR_BegPic, SunR_BegPicBody,
	SunR_EndPic, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 1 */
	{
	NULL, MFVersion, MFDesc, VDCType, IntergerPrec,
	RealPrec, IndexPrec, ColrPrec, ColrIndexPrec, MaxColrIndex,
	ColrValueExt, MFElemList, MFDefaults, FontList,
	CharSetList, CharCoding, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 2 */
	{
	NULL, ScaleMode, ColrMode, LineWidthMode, MarkerSizeMode,
	EdgeWidthMode, VDCExt, BackColr, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 3 */
	{
	NULL, VDCIntergerPrec, VDCRealPrec, AuxColr, Transparency,
	ClipRect, Clip, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 4 */
	{
	NULL, SunR_PolyLine, DisjtLine, SunR_PolyMarker, Text,
	RestrText, ApndText, SunR_Polygon, PolygonSet, SunR_CellArray,
	GDP, Rect, Circle, Arc3Pt, Arc3PtClose,
	ArcCtr, ArcCtrClose, Ellipse, EllipArc, EllipArcClose,
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 5 */
	{
	NULL, LineIndex, LineType, LineWidth, LineColr,
	MarkerIndex,MarkerType,MarkerSize,MarkerColr,
	TextIndex, TextFontIndex, TextPrec, CharExpan, 
	CharSpace, TextColr, CharHeight, CharOri, 
	TextPath, TextAlign, CharSetIndex, AltCharSetIndex,
	FillIndex,IntStyle,FillColr,HatchIndex,
	PatIndex, EdgeIndex, EdgeType, EdgeWidth, EdgeColr,
	EdgeVis, FillRefPt, PatTable, PatSize, SunR_ColrTable,
	ASF,
	},
	/* Class 6 */
	{
	NULL, Escape, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	},
	/* Class 7 */
	{
	NULL, Message, ApplData, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, 
	NULL,
	}

	},
#endif

};
