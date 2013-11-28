#		Copyright © 1999–2000  Jens Kilian
#
#		This program is free software; you can redistribute it and/or modify
#		it under the terms of the GNU General Public License as published by
#		the Free Software Foundation; either version 1, or (at your option)
#		any later version.
#
#		This program is distributed in the hope that it will be useful,
#		but WITHOUT ANY WARRANTY; without even the implied warranty of
#		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
#		GNU General Public License for more details.
#
#		You should have received a copy of the GNU General Public License
#		along with this program; if not, write to the Free Software
#		Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#		Makefile for ScreenSaver module.
#------------------------------------------------------------------------------

NAME = KanjiSaver
INSTDIR = '/boot/home/config/add-ons/Screen Savers'

#------------------------------------------------------------------------------
#		Top-level targets.

all:	default

install:	all
	install -m 755 $(TARGET) $(INSTDIR)

#------------------------------------------------------------------------------
#		The works.

TYPE = SHARED
SRCS = KanjiSaver.cpp KanjiSaverConfigView.cpp RandomColor.cpp
RSRCS = 
LIBS = be screensaver
LIBPATHS = 
SYSTEM_INCLUDE_PATHS = /boot/develop/headers/be/add-ons/screen_saver
LOCAL_INCLUDE_PATHS = 
DEFINES = 
OPTIMIZE = FULL
WARNINGS = 
SYMBOLS = TRUE
DEBUGGER = 
COMPILER_FLAGS = 
LINKER_FLAGS = 

include /boot/develop/etc/makefile-engine

#------------------------------------------------------------------------------
