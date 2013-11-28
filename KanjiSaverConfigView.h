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

#ifndef KANJISAVERCONFIGVIEW_H
#define KANJISAVERCONFIGVIEW_H

#include <ListView.h>
#include <Message.h>
#include <Rect.h>
#include <TextView.h>

class KanjiSaver;

class KanjiSaverConfigView : public BTextView
{
	typedef BTextView inherited;
public:
	KanjiSaverConfigView(KanjiSaver &saver, BRect frame);
	virtual ~KanjiSaverConfigView(void);

	// Hook functions.
	virtual void AttachedToWindow(void);
	virtual void MessageReceived(BMessage *pMsg);
		
private:
	KanjiSaverConfigView(const KanjiSaverConfigView &orig);
	KanjiSaverConfigView &operator =(const KanjiSaverConfigView &orig);
	
	// Message codes.
	enum {
		kSelectFont = 'sfnt'
	};
	
	// Data members.
	KanjiSaver &mSaver;
	BListView *mpListView;
};
	
#endif // KANJISAVERCONFIGVIEW_H
