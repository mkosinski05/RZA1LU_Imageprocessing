/*
* Copyright (C) TES Electronic Solutions GmbH,
* All Rights Reserved.
* Contact: info@guiliani.de
*
* This file is part of the Guiliani HMI framework
* for the development of graphical user interfaces on embedded systems.
*/

#ifndef GUI_COMMAND_RESOURCE__H_
#define GUI_COMMAND_RESOURCE__H_
#include "eC_Types.h"
#include <limits.h>

/// @file GUICommandResource.h @ref page_helpermacros
// 
// DO NOT EDIT THIS FILE!!! Add your own IDS within UserXXXResource.h files!
// DO NOT EDIT THIS FILE!!! Add your own IDS within UserXXXResource.h files!
// DO NOT EDIT THIS FILE!!! Add your own IDS within UserXXXResource.h files!
//

// -----------------------------------------------------------------------------------------
///  CommandClassIDs

    //Add Guiliani-CommandClassID_t here (with negative IDs, DUMMY_COMMAND has to stay 0, see COMMAND_START_TAG below)
#define COMMAND_TABLE            \
ENTRY(CMD_START_ANIMATIONS, CGUIStartAnimationsCmd) \
ENTRY(CMD_LOAD_ANIMATIONS, CGUILoadAnimationsCmd) \
ENTRY(CMD_SETOBJECTSTATE, CGUISetObjectStateCmd) \
ENTRY(CMD_DIALOG_TRANSITION, CGUITransitionCmd) \
ENTRY(CMD_PLAYBACK_SOUND, CGUIPlaybackSoundCmd) \
ENTRY(CMD_LOAD_DIALOG, CGUILoadDialogCmd) \
ENTRY(CMD_QUIT, CGUIQuitCmd) 

#ifndef GUILIANI_GUILIANILIB
    #include "UserCommandResource.h"
#endif

/// List of command class ids.
enum CommandClassID_t
{
    COMMAND_START_TAG=-8,
 #define ENTRY_ENUM(a) a, ///< \ref page_helpermacros
 #define ENTRY(cmd_id, cmd_classname) cmd_id, ///< \ref page_helpermacros
    COMMAND_TABLE

    DUMMY_COMMAND=0,
#ifndef GUILIANI_GUILIANILIB
    USER_COMMAND_TABLE
#endif
#undef ENTRY
#undef ENTRY_ENUM
    NOF_COMMANDCLASSES,
    GUILIANI_INTERNAL_CMD = INT_MAX // Do not touch this. Required for ensuring consistent enum type size across libraries.
};

extern const eC_UInt cuiNOFCommandClasses; ///< Used to contain the highest index cuiNOFXXXClasses = MAP_PROPID_TO_ARRAY(NOF_XXXCLASSES);
#endif
