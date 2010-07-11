/*
 *      $Id: varmenus.h,v 1.6 2000-03-21 02:35:53 dbrown Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1996			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		varmenus.h
 *
 *	Author:		David I. Brown
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Mon Mar 17 20:52:04 MST 1997
 *
 *	Description:	
 */
#ifndef	_NG_VARMENUS_H
#define	_NG_VARMENUS_H

#include <ncarg/ngo/go.h>
#include <ncarg/ngo/ncl.h>

/*
 * Public api
 */

typedef struct _NgVarMenusRec 
{
        NhlPointer	vmenu_data;
	Widget		hluvars_mbutton;
        Widget		regvars_mbutton;
        Widget		filerefs_mbutton;
        Widget		filevars_mbutton;
	Widget		functions_mbutton;
        NrmQuark	qfile;    /* only used for retrieving file vars */
} NgVarMenusRec, *NgVarMenus;

NgVarMenus
NgCreateVarMenus(
        Widget		parent,
        XtCallbackProc	hluvar_cb,
        XtCallbackProc	regvar_cb,
        XtCallbackProc	fileref_cb,
        XtCallbackProc	filevar_cb,
        XtCallbackProc	function_cb,
        XtPointer	udata
        );


NhlErrorTypes NgUpdateVarMenus
(
        NgVarMenus		var_menus
        );

void NgDestroyVarMenus
(
        NgVarMenus		var_menus
        );
        

#endif	/* _NG_VARMENUS_H */