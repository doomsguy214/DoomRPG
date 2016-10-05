// ----------------------------------------------------------------------------
//
//  GUI.h
//
//  User interface structures.
//
// ---

#ifndef DOOMRPG_GUI_H
#define DOOMRPG_GUI_H

#include "Defs.h"
#include "List.h"

#define GUIAlloc(n, ...) (GUIAlloc##n((GUI_AllocArgs_##n){ __VA_ARGS__ }))
#define GUI_INHERITS(n) [[__anonymous]] n SuperClass

#define GUI_WIDTH  800
#define GUI_HEIGHT 600

// ----------------------------------------------------------------------------
// Type Definitions
//

typedef struct GUI_S                    GUI;
typedef struct GUI_ControlFunctions_S   GUI_ControlFunctions;
typedef struct GUI_Tooltip_S            GUI_Tooltip;
typedef struct GUI_ContextMenu_S        GUI_ContextMenu;
typedef struct GUI_Control_S            GUI_Control;
typedef struct GUI_Panel_S              GUI_Panel;
typedef struct GUI_Label_S              GUI_Label;

// ----------------------------------------------------------------------------
// Enumerations
//

//
// EPanelTypes
//

typedef enum
{
    PANEL_MAIN,
    PANEL_STATS,
    PANEL_AUGS,
    PANEL_SKILLS,
    PANEL_SHIELD,
    PANEL_STIMS,
    PANEL_TURRET,
    PANEL_SHOP,
    PANEL_PAYOUT,
    PANEL_MISSION,
    PANEL_TRANSPORT,
    PANEL_TEAM,
    PANEL_TIPS,
    PANEL_MAX
} EPanelTypes;

//
// ELabelAlignment
//

typedef enum
{
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTERTOP,
    ALIGN_LEFTTOP,
    ALIGN_RIGHTTOP,
    ALIGN_MAX
} ELabelAlignment;

//
// EBarType
//

typedef enum
{
    BARTYPE_NORMAL,
    BARTYPE_PRETTY,
    BARTYPE_SEGMENT,
    BARTYPE_MAX
} EBarType;

//
// ETooltipType
//

typedef enum
{
    TOOLTIP_BASIC,
    TOOLTIP_TITLE,
    TOOLTIP_COMPLEX,
    TOOLTIP_MAX
} ETooltipType;

//
// EControlTypes
//

typedef enum
{
    CONTROL_ANY,
    CONTROL_LABEL,
    CONTROL_ICON,
    CONTROL_BUTTON,
    CONTROL_BAR,
    CONTROL_LIST,
    CONTROL_GRID,
    CONTROL_BORDER,
    CONTROL_MAX
} EControlTypes;

//
// EGUIDrawFunctions
//

typedef enum
{
    DRAWFN_PREDRAW,
    DRAWFN_DRAW,
    DRAWFN_POSTDRAW,
    DRAWFN_MAX
} EGUIDrawFunctions;

//
// EGUIProcFunctions
//

typedef enum
{
    PROCFN_UPDATE,
    PROCFN_CLICK,
    PROCFN_MAX
} EGUIProcFunctions;

// ----------------------------------------------------------------------------
// Structure Types
//

//
// GUI_S
//

struct GUI_S
{
    bool Created;
    bool Open;

    struct
    {
        int Pos;
        int Delay;
    } GlowLine;

    struct GUI_Control_S *Head;
};

//
// GUI_ControlFunctions_S
//

typedef int  (*GUI_DrawFunc)(struct GUI_Control_S *, int);
typedef void (*GUI_ProcFunc)(struct GUI_Control_S *);

struct GUI_ControlFunctions_S
{
    GUI_DrawFunc DrawFn[DRAWFN_MAX];
    GUI_ProcFunc ProcFn[PROCFN_MAX];
};

//
// GUI_Tooltip_S
//

struct GUI_Tooltip_S
{
    ETooltipType Type;

    str Title;
    str Text;
    int Width, Height;
    str Color;
    bool NoBack;
};

//
// GUI_ContextMenu_S
//

struct GUI_ContextMenu_S
{
    void *placeholder;
};

// ----------------------------------------------------------------------------
// Controls
//

//
// GUI_Control_S
//

struct GUI_Control_S
{
    struct LinkList_S DescLink;
    struct LinkList_S *Descendants;

    struct GUI_Control_S *Parent;

    EControlTypes Type;

    str Name;
    int ID;
    int X, Y;
    int Width, Height;

    bool NoProc;
    bool NoDraw;

    struct GUI_Tooltip_S     Tooltip;
    struct GUI_ContextMenu_S ContextMenu;

    struct GUI_ControlFunctions_S BaseFunctions;
    struct GUI_ControlFunctions_S UserFunctions;
};

//
// GUI_Panel_S
//

struct GUI_Panel_S
{
    GUI_INHERITS(struct GUI_Control_S);
};

//
// GUI_Label_S
//

struct GUI_Label_S
{
    GUI_INHERITS(struct GUI_Control_S);

    str Text;
    str Font;
    str Color;
    bool Big;
    bool RAINBOWS;
    ELabelAlignment Alignment;
};

// ----------------------------------------------------------------------------
// Argument List Structure Types
//

typedef struct GUI_AllocArgs_S          GUI_AllocArgs;
typedef struct GUI_AllocArgs_S          GUI_AllocArgs_Control;
typedef struct GUI_AllocArgs_S          GUI_AllocArgs_Panel;
typedef struct GUI_AllocArgs_Label_S    GUI_AllocArgs_Label;

struct GUI_AllocArgs_S
{
    str Name;
    int X, Y;
    int ID;
    struct GUI_Control_S          *Parent;
    struct GUI_ControlFunctions_S *UserFunctions;
};

struct GUI_AllocArgs_Label_S
{
    GUI_INHERITS(struct GUI_AllocArgs_S);

    str Text;
};

// ----------------------------------------------------------------------------
// Extern Functions
//

NamedScript void CreateAGooeyInVisualBasic();

void *GUIAllocBase(size_t size, struct GUI_AllocArgs_S *args);

int GUIDraw(GUI_Control *control, int hid);

#define GUI_ALLOC_DECL(n) GUI_##n *GUIAlloc##n(GUI_AllocArgs_##n args)

GUI_ALLOC_DECL(Control);
GUI_ALLOC_DECL(Panel);
GUI_ALLOC_DECL(Label);

#undef GUI_ALLOC_DECL

#endif // DOOMRPG_GUI_H
