//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************

/*
 * tuiBaseDrawerColor.h
 *
 *  Created on: Jan, 30th 2025 (Thu)
 *      Author: Marco Dau
 */
 
#ifndef TUI_GRPH_ABST_UNIT_4_IN_OUT_COLOR_H
#define TUI_GRPH_ABST_UNIT_4_IN_OUT_COLOR_H


#define NCURS_COLOR_PAIR_WINDOW_SELECT              COLOR_PAIR  (1)
#define NCURS_COLOR_PAIR_INIT_WINDOW_SELECT         init_pair   (1, COLOR_YELLOW,  COLOR_BLUE)

#define NCURS_COLOR_PAIR_WINDOW_DESELECT            COLOR_PAIR  (2)
#define NCURS_COLOR_PAIR_INIT_WINDOW_DESELECT       init_pair   (2, COLOR_RED,     COLOR_BLACK)

#define NCURS_COLOR_PAIR_WINDOW_EVENT_ON            COLOR_PAIR  (3)
#define NCURS_COLOR_PAIR_INIT_WINDOW_EVENT_ON       init_pair   (3, COLOR_RED,   COLOR_YELLOW)

// ----------------------------------------------------------------------

#define NCURS_COLOR_YELLOW                          kFormatColor_t::fmt_yellow
#define NCURS_COLOR_PAIR_WINDOW_YELLOW              COLOR_PAIR  (NCURS_COLOR_YELLOW)
#define NCURS_COLOR_PAIR_INIT_WINDOW_YELLOW         init_pair   (NCURS_COLOR_YELLOW, COLOR_YELLOW,   COLOR_BLACK)

#define NCURS_COLOR_MAGENTA                         kFormatColor_t::fmt_magenta
#define NCURS_COLOR_PAIR_WINDOW_MAGENTA             COLOR_PAIR  (NCURS_COLOR_MAGENTA)
#define NCURS_COLOR_PAIR_INIT_WINDOW_MAGENTA        init_pair   (NCURS_COLOR_MAGENTA, COLOR_MAGENTA,   COLOR_BLACK)

#define NCURS_COLOR_CYAN                            kFormatColor_t::fmt_cyan
#define NCURS_COLOR_PAIR_WINDOW_CYAN                COLOR_PAIR  (NCURS_COLOR_CYAN)
#define NCURS_COLOR_PAIR_INIT_WINDOW_CYAN           init_pair   (NCURS_COLOR_CYAN, COLOR_CYAN,   COLOR_BLACK)

#define NCURS_COLOR_WHITE                           kFormatColor_t::fmt_white
#define NCURS_COLOR_PAIR_WINDOW_WHITE               COLOR_PAIR  (NCURS_COLOR_WHITE)
#define NCURS_COLOR_PAIR_INIT_WINDOW_WHITE          init_pair   (NCURS_COLOR_WHITE, COLOR_WHITE,   COLOR_BLACK)

// ----------------------------------------------------------------------

#define NCURS_COLOR_PAIR_STRING_ENABLED             COLOR_PAIR  (8)
#define NCURS_COLOR_PAIR_INIT_STRING_ENABLED        init_pair   (8, COLOR_GREEN,   COLOR_BLACK)

#define NCURS_COLOR_PAIR_STRING_DISABLED            COLOR_PAIR  (9)
#define NCURS_COLOR_PAIR_INIT_STRING_DISABLED       init_pair   (9, COLOR_RED,    COLOR_BLACK)


#endif  // TUI_GRPH_ABST_UNIT_4_IN_OUT_COLOR_H
