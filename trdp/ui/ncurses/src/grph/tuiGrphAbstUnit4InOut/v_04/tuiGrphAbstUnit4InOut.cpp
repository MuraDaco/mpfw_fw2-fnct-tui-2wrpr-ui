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
 * tuiGrphAbstUnit4InOut.h
 *
 *  Created on: Jan, 30th 2025 (Thu)
 *      Author: Marco Dau
 */
 

#include "tuiGrphAbstUnit4InOut.h"

#include <iostream>
#include <stdexcept>
#include <string>


// ****************************************************
// section start **** CONSTRUCTOR *****

    tuiGrphAbstUnit4InOut_t::tuiGrphAbstUnit4InOut_t    (dtyIntfcAbstractUnitFunctional_t* p_pUnit)      :
        tuiGrphAbstUnit3Event_t        (p_pUnit)
    {}

    tuiGrphAbstUnit4InOut_t::tuiGrphAbstUnit4InOut_t    (dtyIntfcAbstractUnitFunctional_t* p_pUnit, box_t p_box    )      :
        tuiGrphAbstUnit3Event_t        (p_pUnit, p_box)
    {}

    tuiGrphAbstUnit4InOut_t::tuiGrphAbstUnit4InOut_t    (dtyIntfcAbstractUnitFunctional_t* p_pUnit, margins_t p_margin )      :
        tuiGrphAbstUnit3Event_t        (p_pUnit, p_margin)
    {}

    tuiGrphAbstUnit4InOut_t::tuiGrphAbstUnit4InOut_t    (dtyIntfcAbstractUnitFunctional_t* p_pUnit, box_t p_box    ,margins_t p_margin )      :
        tuiGrphAbstUnit3Event_t        (p_pUnit, p_box  ,p_margin   )
    {}

    // section end   **** CONSTRUCTOR *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** INIT *****

    // public:
    void tuiGrphAbstUnit4InOut_t::setGraphEnvWindow    (dtyIntfcAbstractUnitGraphic_t* p_pParent)     {
        g_pNcursWin     = static_cast<tuiGrphAbstUnit4InOut_t*>(p_pParent)->g_pNcursWin;
    }

    // protected:
    void tuiGrphAbstUnit4InOut_t::initWin           (void) {

        g_pNcursWin = newwin(g_h, g_w, g_mouseY0a, g_mouseX0a);
    }

    void tuiGrphAbstUnit4InOut_t::initWin           (uint16_t p_rootX0a, uint16_t p_rootY0a) {

        g_pNcursWin = newwin(g_h, g_w, p_rootY0a, p_rootX0a);

    }

    void tuiGrphAbstUnit4InOut_t::initWinRootDims   (void) {
        getmaxyx(stdscr,g_h,g_w);
    }

    void tuiGrphAbstUnit4InOut_t::initGraphEnv        (void)     {
        initscr();                          /* Start curses mode            */

        // the current instance is the main window, therefore ...

        // 2. set the pointer of ncurses window to main window [stdsrc]
        g_pNcursWin = stdscr;
        // 3. complete ncurses initialization
        raw();                              /* Line buffering disabled        */
        nodelay(g_pNcursWin, true);
        keypad(g_pNcursWin, TRUE);           /* We get F1, F2 etc..            */
        noecho();                           /* Don't echo() while we do getch */
        curs_set(0);                        /* make cursor invisible */
        mousemask(  ALL_MOUSE_EVENTS |      \
                    REPORT_MOUSE_POSITION,  \
                    NULL);
        // 3.1. enable the continuously monitoring of mouse movement
        NCURS_MOUSE_TRACKING_ENABLE


    }

    void tuiGrphAbstUnit4InOut_t::initGraphEnvColor (void)    {
        start_color();    // BE CAREFUL!! - this instruction must be execute before init_pair function              /* Start color                  */

        // a) init color windows management
        NCURS_COLOR_PAIR_INIT_WINDOW_DESELECT;
        NCURS_COLOR_PAIR_INIT_WINDOW_SELECT;
        NCURS_COLOR_PAIR_INIT_WINDOW_EVENT_ON;
        // -----------
        NCURS_COLOR_PAIR_INIT_WINDOW_YELLOW;
        NCURS_COLOR_PAIR_INIT_WINDOW_MAGENTA;
        NCURS_COLOR_PAIR_INIT_WINDOW_CYAN;
        NCURS_COLOR_PAIR_INIT_WINDOW_WHITE;
        // -----------
        NCURS_COLOR_PAIR_INIT_STRING_ENABLED;
        NCURS_COLOR_PAIR_INIT_STRING_DISABLED;
    }
    
    void tuiGrphAbstUnit4InOut_t::deinitGraphEnv    (void)    {
        NCURS_MOUSE_TRACKING_DISABLE
        mvwprintw(g_pNcursWin, 3, 5, "Exiting ... ");
    }

    void tuiGrphAbstUnit4InOut_t::endGraphEnv       (void)  {
        nodelay(stdscr, false);
        getch();                            /* Print it on to the real screen */
        clrtoeol();
    	refresh();
        endwin();                           /* Wait for user input */
    }

    // section end   **** INIT *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DISPLAY STATUS *****

    #define OFF     0
    #define ON      1

    // public:
    bool tuiGrphAbstUnit4InOut_t::isSelectedOrEventOn             (void)  {
        return (
                (tuiState_t::select == g_status) ||
                (tuiState_t::eventOn == g_status)
        );
    }

    bool tuiGrphAbstUnit4InOut_t::isSelected             (void)  {
        return (tuiState_t::select == g_status);
    }

    // private:
    void tuiGrphAbstUnit4InOut_t::attributeMode_frameDeselect (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status)   {
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_DESELECT);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_DESELECT);
    }

    void tuiGrphAbstUnit4InOut_t::attributeMode_frameSelect (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status)     {
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_SELECT);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_SELECT);
    }

    void tuiGrphAbstUnit4InOut_t::attributeMode_frameEventOn (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status)    {
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_EVENT_ON);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_EVENT_ON);
    }

    void tuiGrphAbstUnit4InOut_t::attributeMode_lineDeselect ([[maybe_unused]]tuiGrphAbstUnit4InOut_t* p_this, [[maybe_unused]] uint8_t p_status)    {
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,A_DIM);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,A_DIM);
    }

    void tuiGrphAbstUnit4InOut_t::attributeMode_lineSelect (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status)      {
        // if(OFF == p_status) wattroff(p_this->g_pNcursWin,A_UNDERLINE);
        // if(ON  == p_status) wattron (p_this->g_pNcursWin,A_UNDERLINE);
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,A_BOLD);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,A_BOLD);
    }

    void tuiGrphAbstUnit4InOut_t::attributeMode_lineEventOn (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status)     {
        if(OFF == p_status) wattroff(p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_EVENT_ON);
        if(ON  == p_status) wattron (p_this->g_pNcursWin,NCURS_COLOR_PAIR_WINDOW_EVENT_ON);
    }

    tuiGrphAbstUnit4InOut_t::attributeFunc_t  tuiGrphAbstUnit4InOut_t::g_attributeMode_Frame[] = {
         attributeMode_frameDeselect
        ,attributeMode_frameDeselect
        ,attributeMode_frameSelect
        ,attributeMode_frameEventOn
    };

    tuiGrphAbstUnit4InOut_t::attributeFunc_t  tuiGrphAbstUnit4InOut_t::g_attributeMode_Line[] = {
         attributeMode_lineDeselect
        ,attributeMode_lineDeselect
        ,attributeMode_lineSelect
        ,attributeMode_lineEventOn
    };

    // section end   **** DISPLAY STATUS *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** OUTPUT/DISPLAY functions *****

    // public:

    void tuiGrphAbstUnit4InOut_t::refreshWin     (void)  {
        wrefresh(g_pNcursWin);
        refreshWinChildren();
    }

    void tuiGrphAbstUnit4InOut_t::frameClear (void)   {

        for(uint16_t l_row = g_boundYupper+1; l_row < g_boundYlower; l_row++)  {
            wattron  (g_pNcursWin,A_NORMAL);
            mvwhline    (g_pNcursWin, l_row          ,g_boundXleft + 1           ,' '    ,g_boundXright - g_boundXleft - 1);
        }
        refreshWin();
    }

    //    void tuiGrphAbstUnit4InOut_t::stringValue (const char* p_str, uint8_t p_size)   {
        //        if(g_boundYupper <= g_boundYlower)  {
        //
        //            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, ON);
        //
        //            mvwprintw   (g_pNcursWin, g_boundYupper     ,g_boundXleft, "~ %s ~", p_str);
        //
        //            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, OFF);
        //
        //            refreshWin();
        //        }
    //    }

    void tuiGrphAbstUnit4InOut_t::nameOnly (bool p_select, const char* p_strName)   {
        if(g_boundYupper <= g_boundYlower)  {
            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, ON);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);

            if(g_pNcursWin) mvwprintw(g_pNcursWin, g_y0a, g_x0a, "++ %s ++", p_strName);

            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, OFF);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            wrefresh(g_pNcursWin);
        }
    }

    // .... string

    void tuiGrphAbstUnit4InOut_t::nameOnly (const char* p_strName)   {
        if(g_boundYupper <= g_boundYlower)  {
    
            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);

            if(g_pNcursWin) mvwprintw(g_pNcursWin, g_y0a, g_x0a, "++ %s ++", p_strName);

            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            wrefresh(g_pNcursWin);
        }
    }

    bool tuiGrphAbstUnit4InOut_t::nameOnly (tuiState_t p_mode, const char* p_strName)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        nameOnly(p_strName);

        return false;
    }

    void tuiGrphAbstUnit4InOut_t::nameOnly (uint16_t p_x, const char* p_strName)   {
        if(g_boundYupper <= g_boundYlower)  {
    
            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);

            if(g_pNcursWin) mvwprintw(g_pNcursWin, g_y0a, g_x0a + p_x, "++ %s ++", p_strName);

            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            wrefresh(g_pNcursWin);
        }
    }

    void tuiGrphAbstUnit4InOut_t::nameOnly (uint16_t p_x, const char* p_strName, uint32_t p_info)   {
        if(g_boundYupper <= g_boundYlower)  {
    
            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);

            if(g_pNcursWin) mvwprintw(g_pNcursWin, g_y0a, g_x0a + p_x, "++ %s - %04x ++", p_strName, p_info);

            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            wrefresh(g_pNcursWin);
        }
    }

    bool tuiGrphAbstUnit4InOut_t::nameOnly (tuiState_t p_mode, uint16_t p_x, const char* p_strName)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        nameOnly(p_x, p_strName);

        return false;
    }

    // .... formatted string

    void tuiGrphAbstUnit4InOut_t::fmtStringOnly  (fmt_str_t* p_fmtStr)  {
        wattron (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));

        nameOnly(p_fmtStr->str);

        wattroff (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));
    }

    bool tuiGrphAbstUnit4InOut_t::fmtStringOnly (tuiState_t p_mode, fmt_str_t* p_fmtStr)   {
        g_status = p_mode;
        fmtStringOnly(p_fmtStr);

        return false;
    }

    void tuiGrphAbstUnit4InOut_t::fmtStringOnly  (uint16_t p_x, fmt_str_t* p_fmtStr)  {
        wattron (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));

        nameOnly(p_x, p_fmtStr->str);

        wattroff (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));
    }

    void tuiGrphAbstUnit4InOut_t::fmtStringOnly  (uint16_t p_x, fmt_str_t* p_fmtStr, uint32_t p_info)  {
        wattron (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));

        nameOnly(p_x, p_fmtStr->str, p_info);

        wattroff (g_pNcursWin,COLOR_PAIR(colorCodeTranslator(p_fmtStr->color)));
    }

    bool tuiGrphAbstUnit4InOut_t::fmtStringOnly (tuiState_t p_mode, uint16_t p_x, fmt_str_t* p_fmtStr)   {
        g_status = p_mode;
        fmtStringOnly(p_x, p_fmtStr);

        return false;
    }

    void tuiGrphAbstUnit4InOut_t::frameNnameTest (const char* p_strName, const char* p_strValue)   {
        if(g_boundYupper <= g_boundYlower)  {

            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, ON);

            if(g_boundYupper < g_boundYlower)  {
                if((g_boundYlower+1) == (g_y0a + g_h))   {
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXleft      ,0    ,g_boundYlower - g_boundYupper      );
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXright     ,0    ,g_boundYlower - g_boundYupper      );
                } else {
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXleft      ,0    ,g_boundYlower - g_boundYupper + 1      );
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXright     ,0    ,g_boundYlower - g_boundYupper + 1      );
                }
            }

            if(g_boundYupper == g_y0a)   {
            	mvwaddch    (g_pNcursWin, g_boundYupper     ,g_boundXleft      ,ACS_ULCORNER       );
            	mvwaddch    (g_pNcursWin, g_boundYupper     ,g_boundXright     ,ACS_URCORNER       );
            	mvwhline    (g_pNcursWin, g_boundYupper     ,g_boundXleft + 1           ,0    ,g_boundXright - g_boundXleft - 1      );
                mvwprintw   (g_pNcursWin, g_boundYupper     ,g_x0a + 1, "~ %s ~", p_strName);
                if(((g_boundYupper+1) <= g_boundYlower))
                    mvwprintw   (g_pNcursWin, g_boundYupper+1 ,g_x0a + 1, "~ %04x - %04x - %s ~", g_boundYupper,  g_boundYlower, p_strValue);
            }

            if(
                (    
                        (g_boundYupper == (g_y0a+1))
                    &&  ((g_boundYupper+1) <= g_boundYlower)
                )
            )
                mvwprintw   (g_pNcursWin, g_boundYupper   ,g_x0a + 1, "~ %04x - %04x ~", g_boundYupper,  g_boundYlower);

            if((g_boundYlower+1) == (g_y0a + g_h))   {
            	mvwaddch    (g_pNcursWin, g_boundYlower     ,g_boundXleft       ,ACS_LLCORNER       );
            	mvwaddch    (g_pNcursWin, g_boundYlower     ,g_boundXright      ,ACS_LRCORNER       );
            	mvwhline    (g_pNcursWin, g_boundYlower     ,g_boundXleft + 1   ,0    ,g_boundXright - g_boundXleft - 1      );
                mvwprintw   (g_pNcursWin, g_boundYlower     ,g_boundXleft + 1, "~ %04x - %04x ~", g_boundXleft,   g_boundXright);
            }

            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, OFF);

            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::frameNnameTest (const char* p_strName)   {
        if(g_boundYupper <= g_boundYlower)  {

            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, ON);

            if(g_boundYupper < g_boundYlower)  {
                if((g_boundYlower+1) == (g_y0a + g_h))   {
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXleft      ,0    ,g_boundYlower - g_boundYupper      );
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXright     ,0    ,g_boundYlower - g_boundYupper      );
                } else {
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXleft      ,0    ,g_boundYlower - g_boundYupper + 1      );
                	mvwvline(g_pNcursWin, g_boundYupper          ,g_boundXright     ,0    ,g_boundYlower - g_boundYupper + 1      );
                }
            }

            if(g_boundYupper == g_y0a)   {
            	mvwaddch    (g_pNcursWin, g_boundYupper     ,g_boundXleft      ,ACS_ULCORNER       );
            	mvwaddch    (g_pNcursWin, g_boundYupper     ,g_boundXright     ,ACS_URCORNER       );
            	mvwhline    (g_pNcursWin, g_boundYupper     ,g_boundXleft + 1           ,0    ,g_boundXright - g_boundXleft - 1      );
                mvwprintw   (g_pNcursWin, g_boundYupper     ,g_x0a + 1, "~ %s ~", p_strName);
                if(((g_boundYupper+1) <= g_boundYlower))
                    mvwprintw   (g_pNcursWin, g_boundYupper+1 ,g_x0a + 1, "~ %04x - %04x ~", g_boundYupper,  g_boundYlower);
            }

            if(
                (    
                        (g_boundYupper == (g_y0a+1))
                    &&  ((g_boundYupper+1) <= g_boundYlower)
                )
            )
                mvwprintw   (g_pNcursWin, g_boundYupper   ,g_x0a + 1, "~ %04x - %04x ~", g_boundYupper,  g_boundYlower);

            if((g_boundYlower+1) == (g_y0a + g_h))   {
            	mvwaddch    (g_pNcursWin, g_boundYlower     ,g_boundXleft       ,ACS_LLCORNER       );
            	mvwaddch    (g_pNcursWin, g_boundYlower     ,g_boundXright      ,ACS_LRCORNER       );
            	mvwhline    (g_pNcursWin, g_boundYlower     ,g_boundXleft + 1   ,0    ,g_boundXright - g_boundXleft - 1      );
                mvwprintw   (g_pNcursWin, g_boundYlower     ,g_boundXleft + 1, "~ %04x - %04x ~", g_boundXleft,   g_boundXright);
            }

            g_attributeMode_Frame[static_cast<uint8_t>(g_status)](this, OFF);

            refreshWin();
        }
    }

    bool tuiGrphAbstUnit4InOut_t::frameNnameTest (tuiState_t p_mode, const char* p_strName, const char* p_strValue)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        frameNnameTest(p_strName, p_strValue);

        return false;
    }

    bool tuiGrphAbstUnit4InOut_t::frameNnameTest (tuiState_t p_mode, const char* p_strName)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        frameNnameTest(p_strName);

        return false;
    }

    void tuiGrphAbstUnit4InOut_t::nameNstatus (const char* p_strName, uint8_t p_status)   {

        if(g_boundYupper <= g_boundYlower)    {
            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);
            mvwprintw(g_pNcursWin, g_y0a, g_x0a, "-- %s -- %02d", p_strName, p_status);
            g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            refreshWin();
        }
    }

    bool tuiGrphAbstUnit4InOut_t::nameNstatus (tuiState_t p_mode, const char* p_strName, uint8_t p_status)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        if(g_boundYupper <= g_boundYlower)    {
            g_attributeMode_Line[static_cast<uint8_t>(p_mode)](this, ON);

            mvwprintw(g_pNcursWin, g_y0a, g_x0a, "-- %s -- %02d", p_strName, p_status);

            g_attributeMode_Line[static_cast<uint8_t>(p_mode)](this, OFF);

            refreshWin();
        }
        return true;
    }

    bool tuiGrphAbstUnit4InOut_t::nameNstatus (tuiState_t p_mode, const char* p_strName, uint8_t p_status, bool p_repaint)   {
        if(
                (g_status == p_mode)
            &&  (!p_repaint)
        )   return false; 
        g_status = p_mode;

        if(g_boundYupper <= g_boundYlower)    {
            g_attributeMode_Line[static_cast<uint8_t>(p_mode)](this, ON);

            mvwprintw(g_pNcursWin, g_y0a, g_x0a, "-- %s -- %02d", p_strName, p_status);

            g_attributeMode_Line[static_cast<uint8_t>(p_mode)](this, OFF);

            refreshWin();
        }
        return true;
    }

    void tuiGrphAbstUnit4InOut_t::content (uint8_t p_begin)   {
        int16_t l_row = getBoundYupper();
        if(
                (g_boundYupper <= l_row)  
            &&  (                 l_row <= g_boundYlower)  
        )    {
            uint16_t l_dspBoxW = getDspAreaDimXw();
            mvwhline    (g_pNcursWin, l_row          ,g_x0a + 1 + p_begin           ,' '    ,l_dspBoxW - p_begin      );

            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::content (char* p_str, uint8_t p_size)   {
        int16_t l_row = getBoundYupper();
        if(
                (g_boundYupper <= l_row)  
            &&  (                 l_row <= g_boundYlower)
        )    {

            uint16_t l_dspBoxW = getDspAreaDimXw();
            mvwaddnstr  (g_pNcursWin, l_row          ,g_x0a + 1        ,p_str  ,p_size);
            if(p_size < l_dspBoxW)
                mvwhline    (g_pNcursWin, l_row          ,g_x0a + 1 + p_size           ,' '    ,l_dspBoxW - p_size      );

            refreshWin();
        }
    }

    bool tuiGrphAbstUnit4InOut_t::content (tuiState_t p_mode, char* p_str, uint8_t p_size)   {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        content(p_str, p_size);

        return true;
    }

    void tuiGrphAbstUnit4InOut_t::content (char* p_str, uint8_t p_begin, uint8_t p_size)   {
        int16_t l_row = getBoundYupper();
        if(
                (g_boundYupper <= l_row)  
            &&  (                 l_row <= g_boundYlower)  
        )    {
            uint16_t l_dspBoxW = getDspAreaDimXw();
            mvwaddnstr  (g_pNcursWin, l_row          ,g_x0a + 1 + p_begin       ,p_str  ,p_size);
            if(p_size < l_dspBoxW)
                mvwhline    (g_pNcursWin, l_row          ,g_x0a + 1 + p_begin + p_size           ,' '    ,l_dspBoxW - (p_begin + p_size)      );

            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::positionCursor     (bool p_status, uint8_t p_position)    {
        int16_t l_row = getBoundYupper();
        if(
                (g_boundYupper <= l_row)  
            &&  (                l_row <= g_boundYlower)
        )    {
            if(p_status)    {
                if(g_position != p_position)    {
                    mvwchgat(g_pNcursWin, l_row          ,g_x0a + 1 + g_position,1, A_NORMAL, 0, NULL);
                    g_position = p_position;
                }
                mvwchgat(g_pNcursWin, l_row          ,g_x0a + 1 + g_position,1, A_BLINK | A_UNDERLINE, 0, NULL);
            } else {
                g_position = p_position;
                mvwchgat(g_pNcursWin, l_row          ,g_x0a + 1 + p_position,1, A_NORMAL, 0, NULL);    
            }
            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::stringPrint  (uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize) {
        if(g_boundYupper <= g_boundYlower)  {
            if(tuiState_t::select == g_status) p_select = true;

            wattron (g_pNcursWin,COLOR_PAIR(p_rowMarker));
            //if(p_select) wattron (g_pNcursWin,A_UNDERLINE);
            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, ON);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);


            uint16_t l_strSize = p_strSize;
            uint16_t l_lenghtStrMax = g_dspAreaW - 1; // the first column is reserved for info about string (if it is the first row or not)

            // synchronization between row and string id to display
            uint16_t l_row0     = (g_y0r < 0) ? (0 + (-g_y0r)) : 0;
            uint16_t l_strId    = (g_y0r < 0) ? (l_lenghtStrMax*(-g_y0r)) : 0;
            l_strSize          -= (g_y0r < 0) ?  l_strId         : 0;
            uint16_t l_strSizeRow  = (l_strSize < l_lenghtStrMax) ? l_strSize : l_lenghtStrMax;

            uint16_t l_rowAbs = g_y0a + l_row0;
            for(;;)    {
                if(g_boundYupper <= l_rowAbs)    {
                    // the row to display is inside the bounds, therefore ...

                    // display it
                    if(0 == l_strId) 
                        mvwaddch(g_pNcursWin,   l_rowAbs          ,g_x0a    ,'1'       );
                    else
                        mvwaddch(g_pNcursWin,   l_rowAbs          ,g_x0a    ,' '       );

                    // ---------------------

                    mvwaddnstr  (g_pNcursWin, l_rowAbs     ,g_x0a + 1     ,&p_pStr[l_strId]  ,l_strSizeRow);
                    if(l_strSizeRow < l_lenghtStrMax)    {
                        // if(p_select) wattroff (g_pNcursWin,A_UNDERLINE);
                        // wattron (g_pNcursWin,A_NORMAL);
                        if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, OFF);
                        else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

                  	    mvwhline    (g_pNcursWin, l_rowAbs          ,g_x0a + 1 + l_strSizeRow           ,' '    ,l_lenghtStrMax - l_strSizeRow);
                        // the last row is displayed, therefore ...
                    }
                }

                if(g_boundYlower == l_rowAbs) break;

                l_rowAbs++;
                l_strId         += l_lenghtStrMax;
                l_strSize       -= (l_strSize < l_lenghtStrMax) ? 0         : l_lenghtStrMax;
                l_strSizeRow     = (l_strSize < l_lenghtStrMax) ? l_strSize : l_lenghtStrMax;

            }

            //if(p_select) wattroff (g_pNcursWin,A_UNDERLINE);
            //wattron (g_pNcursWin,A_NORMAL);
            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, OFF);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

            wattroff(g_pNcursWin,COLOR_PAIR(p_rowMarker));

            refreshWin();
        }
    }

    bool tuiGrphAbstUnit4InOut_t::stringPrint  (tuiState_t p_mode, uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize) {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        stringPrint(p_rowMarker, p_select, p_pStr, p_strSize);


        return true;
    }

    void tuiGrphAbstUnit4InOut_t::stringPrint2  (uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize) {
        if(g_boundYupper <= g_boundYlower)  {
            if(tuiState_t::select == g_status) p_select = true;

            wattron (g_pNcursWin,COLOR_PAIR(p_rowMarker));
            //if(p_select) wattron (g_pNcursWin,A_UNDERLINE);
            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, ON);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, ON);


            uint16_t l_strSize = p_strSize;
            uint16_t l_lenghtStrMax = g_w - 1; // the first column is reserved for info about string (if it is the first row or not)

            // synchronization between row and string id to display
            uint16_t l_row0     = (g_y0r < 0) ? (0 + (-g_y0r)) : 0;
            uint16_t l_strId    = (g_y0r < 0) ? (l_lenghtStrMax*(-g_y0r)) : 0;
            l_strSize          -= (g_y0r < 0) ?  l_strId         : 0;
            uint16_t l_strSizeRow  = (l_strSize < l_lenghtStrMax) ? l_strSize : l_lenghtStrMax;

            uint16_t l_rowAbs = g_y0a + l_row0;
            for(;;)    {
                if(g_boundYupper <= l_rowAbs)    {
                    // the row to display is inside the bounds, therefore ...

                    // display it
                    if(0 == l_strId) 
                        mvwaddch(g_pNcursWin,   l_rowAbs          ,g_x0a    ,'1'       );
                    else
                        mvwaddch(g_pNcursWin,   l_rowAbs          ,g_x0a    ,' '       );

                    // ---------------------

                    mvwaddnstr  (g_pNcursWin, l_rowAbs     ,g_x0a + 1     ,&p_pStr[l_strId]  ,l_strSizeRow);
                    if(l_strSizeRow < l_lenghtStrMax)    {
                        //if(p_select) wattroff (g_pNcursWin,A_UNDERLINE);
                        //wattron (g_pNcursWin,A_NORMAL);
                        if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, OFF);
                        else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);

                  	    mvwhline    (g_pNcursWin, l_rowAbs          ,g_x0a + 1 + l_strSizeRow           ,' '    ,l_lenghtStrMax - l_strSizeRow);
                        // the last row is displayed, therefore ...
                    }
                }

                if(g_boundYlower == l_rowAbs) break;

                l_rowAbs++;
                l_strId         += l_lenghtStrMax;
                l_strSize       -= (l_strSize < l_lenghtStrMax) ? 0         : l_lenghtStrMax;
                l_strSizeRow     = (l_strSize < l_lenghtStrMax) ? l_strSize : l_lenghtStrMax;

            }

            // if(p_select) wattroff (g_pNcursWin,A_UNDERLINE);
            // wattron (g_pNcursWin,A_NORMAL);
            if(p_select) g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::select)](this, OFF);
            else g_attributeMode_Line[static_cast<uint8_t>(g_status)](this, OFF);
            wattroff(g_pNcursWin,COLOR_PAIR(p_rowMarker));

            refreshWin();
        }
    }

    bool tuiGrphAbstUnit4InOut_t::stringPrint2  (tuiState_t p_mode, uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize) {
        if(g_status == p_mode) return false; 
        g_status = p_mode;

        stringPrint2(p_rowMarker, p_select, p_pStr, p_strSize);


        return true;
    }

    uint8_t tuiGrphAbstUnit4InOut_t::colorCodeTranslator    (kColor_t p_color)   {
        uint8_t l_color;
        switch (p_color)    {
            case kColor_t::black:
            case kColor_t::black_low:
            case kColor_t::black_high:
                l_color = NCURS_COLOR_YELLOW;
                break;
            case kColor_t::red:
            case kColor_t::red_low:
            case kColor_t::red_high:
                l_color = NCURS_COLOR_CYAN;
                break;
            case kColor_t::green:
            case kColor_t::green_low:
            case kColor_t::green_high:
                l_color = NCURS_COLOR_MAGENTA;
                break;
            case kColor_t::yellow:
            case kColor_t::yellow_low:
            case kColor_t::yellow_high:
                l_color = NCURS_COLOR_YELLOW;
                break;
            case kColor_t::blue:
            case kColor_t::blue_low:
            case kColor_t::blue_high:
                l_color = NCURS_COLOR_YELLOW;
                break;
            case kColor_t::magenta:
            case kColor_t::magenta_low:
            case kColor_t::magenta_high:
                l_color = NCURS_COLOR_MAGENTA;
                break;
            case kColor_t::cyan:
            case kColor_t::cyan_low:
            case kColor_t::cyan_high:
                l_color = NCURS_COLOR_CYAN;
                break;
            case kColor_t::white:
            case kColor_t::white_low:
            case kColor_t::white_high:
                l_color = NCURS_COLOR_WHITE;
                break;
        }
        return l_color;
    }

    // section end   **** OUTPUT/DISPLAY functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DEBUG OUTPUT/DISPLAY functions *****

    // public:
    void tuiGrphAbstUnit4InOut_t::debugPrint     (uint32_t p_dbgParam1, uint32_t p_dbgParam2, char* p_pStr)       {
        uint16_t l_lenghtStrMax = g_dspAreaW - 1; // the first column is reserved for info about string (if it is the first row or not)
        uint16_t l_strId    = (g_y0r < 0) ? (l_lenghtStrMax*(-g_y0r)) : 0;
        uint16_t l_rowUp    = (g_y0r < 0) ? (0 + (-g_y0r)) : 0;

        mvwprintw   (g_pNcursWin, g_y0a + l_rowUp     ,g_x0a      ,"~ %08x - %08x - %04x ~", p_dbgParam1, p_dbgParam2, l_lenghtStrMax);
        mvwaddnstr  (g_pNcursWin, g_y0a + l_rowUp     ,g_x0a + 8 , &p_pStr[l_strId]  ,5);

    }

    void tuiGrphAbstUnit4InOut_t::dbgPrint             (char* p_str)       {
        [[maybe_unused]] uint16_t l_h;
        uint16_t l_w;
        getmaxyx(stdscr, l_h, l_w);
        if(80 < l_w)    {
            mvwhline    (stdscr, 2, 80, ' '         , (l_w-1) - 80);
            mvwprintw   (stdscr, 2, 80, "*** %s ***", p_str);
            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::dbgPrint             (uint16_t p_x, uint16_t p_y, char* p_str)       {
        [[maybe_unused]] uint16_t l_h;
        uint16_t l_w;
        getmaxyx(stdscr, l_h, l_w);
        if(p_x < l_w)    {
            mvwhline    (stdscr, p_y, p_x, ' '         , (l_w-1) - 80);
            mvwprintw   (stdscr, p_y, p_x, "*** %s ***", p_str);
            refreshWin();
        }
    }

    void tuiGrphAbstUnit4InOut_t::dbgExit                        (const char* p_strExit) {

        deinitGraphEnv();
        endGraphEnv();
        std::string l_strExit (p_strExit);
        std::cout << l_strExit << '\n';
        std::exit(0);


    }

    void tuiGrphAbstUnit4InOut_t::dbgStep                        (const char* p_strStep) {

            mvwhline    (stdscr, 3, 80, ' '         , 70);
            mvwprintw   (stdscr, 3, 80, "** dbg ** %s ****", p_strStep);
            refreshWin();

    }

    void tuiGrphAbstUnit4InOut_t::dbgStep                        (const char* p_strStep, uint32_t p_param1, uint32_t p_param2) {

            mvwhline    (stdscr, 3, 80, ' '         , 70);
            mvwprintw   (stdscr, 3, 80, "** dbg ** %s - %04d - %04d ****", p_strStep, p_param1, p_param2);
            refreshWin();

    }

    void tuiGrphAbstUnit4InOut_t::dbgStep                        (uint8_t p_y, const char* p_strStep, uint32_t p_param1, uint32_t p_param2) {

            mvwhline    (stdscr, p_y, 80, ' '         , 70);
            mvwprintw   (stdscr, p_y, 80, "** dbg ** %s - %04d - %04d ****", p_strStep, p_param1, p_param2);
            refreshWin();

    }

    // section end   **** DEBUG OUTPUT/DISPLAY functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** INPUT/(KEYBOARD-MOUSE) functions *****

    // protected:
    bool tuiGrphAbstUnit4InOut_t::uiEventStatus                                 (void)  {
        bool l_result;
        g_ncursEventCode = wgetch(g_pNcursWin);
        l_result = (ERR != g_ncursEventCode);
        return l_result;
    }

    int tuiGrphAbstUnit4InOut_t::uiEventKeyCode                                 (void)  {
        return g_ncursEventCode;
    }

    tuiEventCode_t  tuiGrphAbstUnit4InOut_t::uiHandlerEventCode                 (void)  {
        tuiEventCode_t l_eventCode = tuiEventCode_t::noEvent;
        switch(g_ncursEventCode)    {
            case KEY_MOUSE:
                mvwprintw(g_pNcursWin, 2, 50, "MOUSE_EVENT");
                l_eventCode = tuiEventCode_t::mouse;
                getmouse(&g_mouseEvent);
                char l_str[30];
                snprintf(l_str, sizeof l_str,"%03d / %03d", g_mouseEvent.x, g_mouseEvent.y);
                mvwprintw(g_pNcursWin, 3, 50, "MOUSE_coordinates: %s",l_str);
                snprintf(l_str, sizeof l_str,"%08lx", g_mouseEvent.bstate);
                mvwprintw(g_pNcursWin, 4, 50, "MOUSE_status: %s",l_str);
                if(TUI_MOUSE_ROLL_UP    == g_mouseEvent.bstate) l_eventCode = tuiEventCode_t::mouseRollUp;
                if(TUI_MOUSE_ROLL_DOWN  == g_mouseEvent.bstate) l_eventCode = tuiEventCode_t::mouseRollDown;            
                break;
            case KEY_DOWN:
            case TUI_KEY_TAB:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_DOWN                            ");
                l_eventCode = tuiEventCode_t::keyDown;
                break;
            case KEY_UP:
            case TUI_KEY_SHIFT_TAB:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_UP                              ");
                l_eventCode = tuiEventCode_t::keyUp;
                break;
            case KEY_LEFT:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_LEFT                            ");
                l_eventCode = tuiEventCode_t::keyLeft;
                break;
            case KEY_RIGHT:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_RIGHT                           ");
                l_eventCode = tuiEventCode_t::keyRight;
                break;
            case KEY_ENTER:
            case TUI_KEY_RETURN:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_ENTER                           ");
                l_eventCode = tuiEventCode_t::keyEnter;
                break;
            case KEY_HOME:
            case TUI_KEY_ESC:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_HOME                            ");
                l_eventCode = tuiEventCode_t::keyHome;
                break;
            case TUI_KEY_DEL:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_DEL                             ");
                l_eventCode = tuiEventCode_t::keyDel;
                break;
            case TUI_KEY_BACKSPACE:
                mvwprintw(g_pNcursWin, 2, 50, "KEY_BACKSPACE                       ");
                l_eventCode = tuiEventCode_t::keyBackspace;
                break;
            default:
                if((0x20 <= g_ncursEventCode) && (g_ncursEventCode < 0x7f)) {
                    mvwprintw(g_pNcursWin, 2, 50, "type character - keyCode: %04x", g_ncursEventCode);
                    l_eventCode = tuiEventCode_t::keyTypeChar;
                } else {
                    mvwprintw(g_pNcursWin, 2, 50, "UNKNOWN_EVENT - keyCode: %04x", g_ncursEventCode);
                }
                break;
        }

        return l_eventCode;
    }

    bool tuiGrphAbstUnit4InOut_t::uiMouseEventStatus                            (void)  {
        bool l_result;

        //l_result = (getmouse(&g_mouseEvent) == OK);
        l_result = true;
        g_xMouse = g_mouseEvent.x;
        g_yMouse = g_mouseEvent.y;

        return l_result;
    }

    bool tuiGrphAbstUnit4InOut_t::uiMouseEventCode_ButtonPressed             (void)  {
        bool l_result;
        l_result = (
                        (g_mouseEvent.bstate & BUTTON1_PRESSED  )
                    ||  (g_mouseEvent.bstate & BUTTON1_CLICKED  )     
                    //||  (g_mouseEvent.bstate & BUTTON1_RELEASED )     
                );
        return l_result;
    }

    // private:
    int      tuiGrphAbstUnit4InOut_t::g_ncursEventCode;
    MEVENT   tuiGrphAbstUnit4InOut_t::g_mouseEvent;

    // section end   **** INPUT/(KEYBOARD-MOUSE) functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DEBUG *****

    // public:
    void tuiGrphAbstUnit4InOut_t::dbgSetChildrenNumber    (uint8_t p_childrenNumber)     {
        g_childrenNumber     = p_childrenNumber;
    }

    // section end   **** DEBUG *****
    // ****************************************************
    // --------------------------

