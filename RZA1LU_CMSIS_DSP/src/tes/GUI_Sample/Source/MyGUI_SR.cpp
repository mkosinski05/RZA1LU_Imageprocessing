/*
* Copyright (C) 2004 TES Electronic Solutions GmbH,
* All Rights Reserved.
* This source code and any compilation or derivative thereof is the
* proprietary information of TES Electronic Solutions GmbH
* and is confidential in nature.
* Under no circumstances is this software to be exposed to or placed
* under an Open Source License of any type without the expressed
* written permission of TES Electronic Solutions GmbH
*
*############################################################
*/

/******************************************************************************
*   PROJECT:        Guiliani
*******************************************************************************
*
*    MODULE:        MyGUI_SR.cpp
*
*    Archive:       $URL: https://10.25.129.51:3690/svn/GSE/branches/Releases/1.0_Guiliani_2.1/StreamRuntime/src/MyGUI_SR.cpp $
*
*    Date created:  2005
*
*
*
*    Author:        JRE
*
*******************************************************************************
*   MODIFICATIONS
*******************************************************************************
*    ID
*    --------------------------------------------------------------------------
*    $Id: MyGUI_SR.cpp 2159 2014-11-26 15:36:46Z christian.euler $
*
******************************************************************************/
#include "MyGUI_SR.h"

#include "UserConfig.h"

#ifdef GFX_USE_EGML
#include "GfxWrapeGML.h"
#endif



extern "C"
{
/* Dependencies */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


}

#if __ICCARM__ == 1
extern "C"
{
    int open(const char *filename, int amode);
    int close(int handle);
}
#endif


// LAST INCLUDE!!
#include "GUIMemLeakWatcher.h"



CMyGUI::CMyGUI(
    eC_Value x, eC_Value y,
    eC_Value width, eC_Value height,
    ObjectHandle_t eID) :
    CStreamRuntimeGUI(x, y, width, height, eID)

{

}

CMyGUI::~CMyGUI()
{
    // Add application specific de-initialisation here if necessary

}


void CMyGUI::OnNotification(const CGUIValue& kObservedValue, const CGUIObject* const pkUpdatedObject, const eC_UInt uiX, const eC_UInt uiY)
{
    if (NULL != pkUpdatedObject)
    {

    }
}


eC_Bool CMyGUI::CallApplicationAPI(const eC_String& kAPI, const eC_String& kParam)
{

    return true;
}




