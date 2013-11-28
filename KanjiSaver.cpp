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

//		Screen saver class.

#include <cstdlib>

#include <Font.h>
#include <GraphicsDefs.h>
#include <image.h>
#include <List.h>
#include <ListItem.h>
#include <Message.h>
#include <OS.h>
#include <Point.h>
#include <Rect.h>
#include <Screen.h>
#include <ScreenSaver.h>
#include <String.h>
#include <TextView.h>
#include <UnicodeBlockObjects.h>
#include <View.h>

#include "KanjiSaver.h"
#include "KanjiSaverConfigView.h"
#include "RandomColor.h"
#include "RandomNumbers.h"

// Background color.
const rgb_color kBlack = { 0, 0, 0, 0 };

// Message field names.
const char kFieldFamily[] = "family";
const char kFieldStyle[] = "style";

// The set of glyphs which we can display.
const int kMinGlyph = 0x4e00;
const int kNumGlyphs = 0xa000 - kMinGlyph;
const unicode_block kUnicodeBlock = B_CJK_UNIFIED_IDEOGRAPHS_BLOCK;

// Screen saver interface.
BScreenSaver *
instantiate_screen_saver(BMessage *pMsg, image_id id)
{
	return new KanjiSaver(pMsg, id);
}

KanjiSaver::KanjiSaver(BMessage *pMsg, image_id id)
:	inherited(pMsg, id),
	mFontList(),
	mFontIndex(0)
{
	srand((long)system_time());

	// Extract previously selected font, if any.
	const char *pFamily;
	if (pMsg->FindString(kFieldFamily, &pFamily) < B_OK) {
		pFamily = "";
	}
	const char *pStyle;
	if (pMsg->FindString(kFieldStyle, &pStyle) < B_OK) {
		pStyle = "";
	}
	
	// Identify fonts which contain the necessary glyphs.
	BFont font;
	const int32 nFamilies = count_font_families();
	for (int32 i = 0; i < nFamilies; ++i) {
		font_family family;
		if (get_font_family(i, &family) >= B_OK) {
			const int32 nStyles = count_font_styles(family);
			for (int32 j = 0; j < nStyles; ++j) {
				font_style style;
				if (get_font_style(family, j, &style) >= B_OK) {
					if (font.SetFamilyAndStyle(family, style) >= B_OK) {
						if (font.Blocks().Includes(kUnicodeBlock)) {
							mFontList.AddItem(
								new FamilyAndStyle(family,
														 style,
														 font.FamilyAndStyle()));
							
							if (!strcmp(family, pFamily) && !strcmp(style, pStyle)) {
								// This is the previously selected font.
								mFontIndex = mFontList.CountItems() - 1;
							}
						}
					}
				}
			}
		}
	}
}

KanjiSaver::~KanjiSaver(void)
{
	while (!mFontList.IsEmpty()) {
		delete (FamilyAndStyle *)mFontList.RemoveItem(mFontList.CountItems()-1);
	}
}

void
KanjiSaver::Draw(BView *pView, int32 /*frame*/)
{
	const BRect bounds = pView->Bounds();
	pView->SetLowColor(kBlack);
	pView->FillRect(bounds, B_SOLID_LOW);
	
	if (InitCheck() == B_OK) {
		// Use the currently selected font.
		if (const FamilyAndStyle *pFamilyAndStyle = GetFamilyAndStyle(mFontIndex)) {
			BFont font;
			font.SetFamilyAndStyle(pFamilyAndStyle->mID);
			font.SetSize(bounds.Height() * 0.9);
			pView->SetFont(&font, B_FONT_FAMILY_AND_STYLE|B_FONT_SIZE);
		}
		
		// Choose a random color.
		pView->SetHighColor(RandomColor(0.2, 1.0, 0.2, 1.0));
		
		// Choose a random glyph.
		int glyph = kMinGlyph + randomInteger(kNumGlyphs);
		char utf8Chars[4];
		utf8Chars[0] = (char)(0xe0 | ((glyph & 0xf000) >> 12));
		utf8Chars[1] = (char)(0x80 | ((glyph & 0x0fc0) >> 6));
		utf8Chars[2] = (char)(0x80 |  (glyph & 0x003f));
		utf8Chars[3] = (char)0;

		font_height height;
		pView->GetFontHeight(&height);
		const float width = pView->StringWidth(utf8Chars);
		const BPoint origin((bounds.left + bounds.right - width) * 0.5,
								  bounds.bottom - height.descent);
		pView->DrawString(utf8Chars, origin);
	}
	pView->Sync();
}

status_t
KanjiSaver::InitCheck(void)
{
	// We need at least one font.
	if (mFontList.IsEmpty()) {
		return B_ERROR;
	}
	return B_OK;
}

status_t
KanjiSaver::SaveState(BMessage *pMsg) const
{
	// Save the currently selected font.
	if (const FamilyAndStyle *pFamilyAndStyle = GetFamilyAndStyle(mFontIndex)) {
		status_t status = pMsg->AddString(kFieldFamily, pFamilyAndStyle->mFamily);
		if (status < B_OK) {
			return status;
		}
		return pMsg->AddString(kFieldStyle, pFamilyAndStyle->mStyle);
	}
	return B_ERROR;
}

void
KanjiSaver::StartConfig(BView *pConfigView)
{
	BRect frame = pConfigView->Bounds();
	frame.InsetBy(10.0, 10.0);
	pConfigView->AddChild(new KanjiSaverConfigView(*this, frame));
}

status_t
KanjiSaver::StartSaver(BView * /*pView*/, bool /*preview*/)
{
	SetTickSize(5000000);	// 5 seconds
	return InitCheck();
}

BStringItem *
KanjiSaver::CreateFontListItem(int32 index) const
{
	const FamilyAndStyle *pFamilyAndStyle = GetFamilyAndStyle(index);
	if (!pFamilyAndStyle) {
		return 0;
	}

	BString text = pFamilyAndStyle->mFamily;
	text += ' ';
	text += pFamilyAndStyle->mStyle;
	return new BStringItem(text.String());
}
