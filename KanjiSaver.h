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

#ifndef KANJISAVER_H
#define KANJISAVER_H

#include <cstring>

#include <Font.h>
#include <image.h>
#include <List.h>
#include <ListItem.h>
#include <Message.h>
#include <ScreenSaver.h>
#include <View.h>

class KanjiSaver : public BScreenSaver
{
	typedef BScreenSaver inherited;
public:
	KanjiSaver(BMessage *pMsg, image_id id);
	virtual ~KanjiSaver(void);
	
	// Hook functions.
	virtual void Draw(BView *pView, int32 frame);
	virtual status_t InitCheck(void);
	virtual status_t SaveState(BMessage *pMsg) const;
	virtual void StartConfig(BView *pConfigView);
	virtual status_t StartSaver(BView *pView, bool preview);

	// Font list management.
	int32 CountFontListItems(void) const;
	BStringItem *CreateFontListItem(int32 index) const;
	int32 SelectedFont(void) const;
	void SelectFont(int32 index);
	
private:
	KanjiSaver(const KanjiSaver &orig);
	KanjiSaver &operator =(const KanjiSaver &orig);

	// Internal font management.
	struct FamilyAndStyle {
		FamilyAndStyle(const font_family &family,
							const font_style &style,
							const uint32 id)
		:	mID(id)
		{
			strncpy(mFamily, family, sizeof(mFamily));
			strncpy(mStyle, style, sizeof(mStyle));
		}
		font_family mFamily;
		font_style mStyle;
		const uint32 mID;
	};
	const FamilyAndStyle *GetFamilyAndStyle(int32 index) const;
	
	// Data members.
	BList mFontList;
	int32 mFontIndex;
};

inline int32
KanjiSaver::CountFontListItems(void) const
{
	return mFontList.CountItems();
}

inline int32
KanjiSaver::SelectedFont(void) const
{
	return mFontIndex;
}

inline void
KanjiSaver::SelectFont(int32 index)
{
	mFontIndex = index;
}

inline const KanjiSaver::FamilyAndStyle *
KanjiSaver::GetFamilyAndStyle(int32 index) const
{
	return (const KanjiSaver::FamilyAndStyle *)(mFontList.ItemAt(index));
}

#endif // KANJISAVER_H
