// ----------------------------------------------------------------------------
//
//  GUI.c
//
//  User interface scripts.
//
// ---

#include "Defs.h"

#include "Structs.h"
#include "RPG.h"
#include "GUI.h"

//
// CreateAGooeyInVisualBasic
//

NamedScript /*Type_ENTER*/ void CreateAGooeyInVisualBasic()
{
    Player.PGUI = calloc(1, sizeof(Player.PGUI));
    Player.PGUI->Head = GUIAlloc(Control, 0);

    GUIAlloc(Label, .X = 40, 50, .Parent = Player.PGUI->Head, .Text = "fuck me");

    Player.PGUI->Created = true;
    Player.PGUI->Open = false;
}

//
// ExposeTheIlluminati
//

NamedScript Console void ExposeTheIlluminati()
{
    Player.PGUI->Open = !Player.PGUI->Open;
}

//
// TrackTheHackersIPAddress
//

NamedScript /*Type_ENTER*/ void TrackTheHackersIPAddress()
{
    while(Player.PGUI == NULL || !Player.PGUI->Created) Delay(1);

    for(;;)
    {
        if(Player.PGUI->Open)
        {
            Log("right, the illuminati");
            GUIDraw(Player.PGUI->Head, 9999);
        }

        Delay(1);
    }
}

//
// GUIDrawControl
//

static int GUIDrawControl(GUI_Control *control, int hid)
{
    for(EGUIDrawFunctions fn = DRAWFN_PREDRAW; fn <= DRAWFN_POSTDRAW; fn++)
    {
        if(control->BaseFunctions.DrawFn[fn])
            hid = control->BaseFunctions.DrawFn[fn](control, hid);

        if(control->UserFunctions.DrawFn[fn])
            hid = control->UserFunctions.DrawFn[fn](control, hid);
    }

    return hid;
}

//
// GUIDraw
//

int GUIDraw(GUI_Control *head, int hid)
{
    if(head == NULL)
        return hid;

    for(LinkList *it = head->Descendants; it; it = it->Next)
    {
        GUI_Control *control = (GUI_Control *)it;

        if(control->Descendants)
            hid = GUIDraw(control, hid);
        
        hid = GUIDrawControl(control, hid);
    }

    hid = GUIDrawControl(head, hid);

    return hid;
}

//
// GUIAllocBase
//

void *GUIAllocBase(size_t size, GUI_AllocArgs *args)
{
    GUI_Control *control = calloc(1, size);

    if(control == NULL || args == NULL)
        return NULL;

    control->Name   = args->Name ? args->Name : "";
    control->X      = args->X;
    control->Y      = args->Y;
    control->ID     = args->ID ? args->ID : MAKE_ID_STR(control->Name);
    control->Parent = args->Parent;

    if(args->UserFunctions)
        control->UserFunctions = *args->UserFunctions;

    if(control->Parent)
        Link_Insert(&control->DescLink, control, &control->Parent->Descendants);

    return control;
}

//
// GUIAllocControl
//

GUI_Control *GUIAllocControl(GUI_AllocArgs args)
{
    return GUIAllocBase(sizeof(GUI_Control), &args);
}

//
// LabelDraw
//

int LabelDraw(GUI_Control *control, int hid)
{
    GUI_Label *this = (GUI_Label *)control;
    Log("lol %S", this->Text);
    return hid;
}

//
// GUIAllocLabel
//

GUI_Label *GUIAllocLabel(GUI_AllocArgs_Label args)
{
    GUI_Label *control = GUIAllocBase(sizeof(GUI_Label), &args.SuperClass);
    control->Text = args.Text ? args.Text : "";
    control->BaseFunctions.DrawFn[DRAWFN_DRAW] = LabelDraw;
    return control;
}

// EOF
