//		Copyright © 1999–2000  Jens Kilian
//
//		This program is free software; you can redistribute it and/or modify
//		it under the terms of the GNU General Public License as published by
//		the Free Software Foundation; either version 1, or (at your option)
//		any later version.
//
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//		GNU General Public License for more details.
//
//		You should have received a copy of the GNU General Public License
//		along with this program; if not, write to the Free Software
//		Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

//		Screen saver configuration view.

#include <cstring>

#include <Font.h>
#include <Message.h>
#include <ListItem.h>
#include <ListView.h>
#include <Point.h>
#include <Rect.h>
#include <ScrollView.h>
#include <TextView.h>

#define saverVersionID workaroundMissignExternInHeader

#include "KanjiSaver.h"
#include "KanjiSaverConfigView.h"

// Message field names.
const char kFieldIndex[] = "index";

KanjiSaverConfigView::KanjiSaverConfigView(KanjiSaver &saver, BRect frame)
:	inherited(frame, "KanjiSaver", frame.OffsetToCopy(B_ORIGIN),
				 B_FOLLOW_ALL, B_WILL_DRAW),
	mSaver(saver),
	mpListView(0)
{
	// empty
}

KanjiSaverConfigView::~KanjiSaverConfigView(void)
{
	if (mpListView) {
		while (!mpListView->IsEmpty()) {
			delete mpListView->RemoveItem(mpListView->CountItems() - 1);
		}
	}
	mpListView = 0;
}

void
KanjiSaverConfigView::AttachedToWindow(void)
{
	inherited::AttachedToWindow();
	
	SetText("KanjiSaver\n"
			  "\n"
			  "\t© 1999  Jens Kilian <jjk@acm.org>\n"
			  "\n"
			  "KanjiSaver comes with ABSOLUTELY NO WARRANTY; "
			  "it is free software, and you are welcome "
			  "to redistribute it under certain conditions.  "
			  "See the GNU General Public License for details.");
	SetViewColor(Parent()->ViewColor());
	SetStylable(true);
	SetFontAndColor(be_plain_font);
	const char *pText = Text();
	SetFontAndColor(0, strchr(pText, '\n') - pText, be_bold_font);
	MakeEditable(FALSE);
	MakeSelectable(FALSE);

	BRect frame = Bounds().InsetBySelf(5.0, 5.0);
	frame.top += TextHeight(0, TextLength()) + 10.0;
	frame.right -= B_V_SCROLL_BAR_WIDTH;
	mpListView = new BListView(frame, "fonts");
	const int32 nFonts = mSaver.CountFontListItems();
	for (int i = 0; i < nFonts; ++i) {
		if (BStringItem *pItem = mSaver.CreateFontListItem(i)) {
			mpListView->AddItem(pItem);
		}
	}
	AddChild(new BScrollView("scroll_fonts", mpListView,
									 B_FOLLOW_ALL, 0, false, true));
	mpListView->SetTarget(this);
	mpListView->SetSelectionMessage(new BMessage(kSelectFont));
	mpListView->Select(mSaver.SelectedFont());
}

void
KanjiSaverConfigView::MessageReceived(BMessage *pMsg)
{
	switch (pMsg->what) {
	
	case kSelectFont:
		{	int32 selected;
			if (pMsg->FindInt32(kFieldIndex, &selected) >= B_OK) {
				mSaver.SelectFont(selected);
			}
		}
		break;
	
	default:
		inherited::MessageReceived(pMsg);
		break;
	}
}
