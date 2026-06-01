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
 
#ifndef TUI_GRPH_ABST_UNIT_4_IN_OUT_H
#define TUI_GRPH_ABST_UNIT_4_IN_OUT_H

#include "tuiGrphAbstUnit3Event.h"

#include <ncurses.h>
#include "tuiGrphAbstUnit4InOutColor.h"



class  tuiGrphAbstUnit4InOut_t : public tuiGrphAbstUnit3Event_t {

public:


// ****************************************************
// section start **** DEFINES *****
    #define TUI_KEY_CTRL_Q              0x0011
    #define TUI_KEY_CTRL_X              0x0018
    #define TUI_KEY_BACKSPACE           0x007f
    #define TUI_KEY_DEL                 0x014a
    #define TUI_KEY_TAB                 0x0009
    #define TUI_KEY_SHIFT_TAB           0x0161
    #define TUI_KEY_RETURN              0x000A
    #define TUI_KEY_ESC                 0x001b

    #define TUI_MOUSE_ROLL_UP           0x08000000
    #define TUI_MOUSE_ROLL_DOWN         0x00080000

    #define NCURS_MOUSE_TRACKING_ENABLE     // printf("\033[?1003h");            // Makes the terminal report mouse movement events
    #define NCURS_MOUSE_TRACKING_DISABLE    // printf("\033[?1003l");            // Disable mouse movement events, as l = low
    // section end   **** DEFINES *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** CONSTRUCTOR *****

    protected:
    tuiGrphAbstUnit4InOut_t (dtyIntfcAbstractUnitFunctional_t* p_pUnit);
    tuiGrphAbstUnit4InOut_t (dtyIntfcAbstractUnitFunctional_t* p_pUnit, box_t p_box    );
    tuiGrphAbstUnit4InOut_t (dtyIntfcAbstractUnitFunctional_t* p_pUnit,                 margins_t p_margin );
    tuiGrphAbstUnit4InOut_t (dtyIntfcAbstractUnitFunctional_t* p_pUnit, box_t p_box    ,margins_t p_margin );

    // section end   **** CONSTRUCTOR *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** INIT / DE-INIT *****
    public:
    //void    setNcursesWindow    (tuiGrphAbstUnit4InOut_t* p_pParent);
    void    setGraphEnvWindow    (dtyIntfcAbstractUnitGraphic_t* p_pParent) override;

    protected:
    void initWin                            (void)                                                                                          override;
    void initWin                            (uint16_t p_rootX0a, uint16_t p_rootY0a)                                                        override;
    void initWinRootDims                    (void);
    void initGraphEnv                       (void)                                                                                          override;
    void initGraphEnvColor                  (void)                                                                                          override;
    void deinitGraphEnv                     (void)                                                                                          override;
    void endGraphEnv                        (void)                                                                                          override;

    private:
    WINDOW* g_pNcursWin;

    // section end   **** INIT / DE-INIT *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DISPLAY STATUS *****
    public:
    bool isSelected                         (void) override;
    bool isSelectedOrEventOn                (void) override;

    private:
    typedef void (* attributeFunc_t)    (tuiGrphAbstUnit4InOut_t*, uint8_t);
    static attributeFunc_t  g_attributeMode_Frame[static_cast<uint8_t>(tuiState_t::num)];
    static void attributeMode_frameDeselect     (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);
    static void attributeMode_frameSelect       (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);
    static void attributeMode_frameEventOn      (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);
    static attributeFunc_t  g_attributeMode_Line[static_cast<uint8_t>(tuiState_t::num)];
    static void attributeMode_lineDeselect      (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);
    static void attributeMode_lineSelect        (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);
    static void attributeMode_lineEventOn       (tuiGrphAbstUnit4InOut_t* p_this, uint8_t p_status);

    // section end   **** DISPLAY STATUS *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** OUTPUT/DISPLAY functions *****

    public:

    void refreshWin                         (void)                                                                                          override;
    void frameClear                         (void)                                                                                          override;

    //void stringColoured                     (uint16_t p_x, tuiActivationStatus_t p_actSts)  override;
    void nameOnly                           (bool p_select, const char* p_strName)                                                          override;

    // .... string
    void nameOnly                           (const char* g_strName)                                                                         override;
    void nameOnly                           (uint16_t p_x, const char* p_strName)                                                           override;
    void nameOnly                           (uint16_t p_x, const char* p_strName, uint32_t p_info)                                          override;
    bool nameOnly                           (tuiState_t p_mode, const char* p_strName)                                                       override;
    bool nameOnly                           (tuiState_t p_mode, uint16_t p_x, const char* p_strName)                                         override;

    // .... formatted string
    void fmtStringOnly                      (fmt_str_t* p_fmtStr)                                                override;
    void fmtStringOnly                      (uint16_t p_x, fmt_str_t* p_fmtStr)                                  override;
    void fmtStringOnly                      (uint16_t p_x, fmt_str_t* p_fmtStr, uint32_t p_info)                 override;
    bool fmtStringOnly                      (tuiState_t p_mode, fmt_str_t* p_fmtStr)                              override;
    bool fmtStringOnly                      (tuiState_t p_mode, uint16_t p_x, fmt_str_t* p_fmtStr)                override;

    void frameNnameTest                     (const char* p_strName, const char* p_strValue)                                                 override;
    void frameNnameTest                     (const char* g_strName)                                                                         override;
    bool frameNnameTest                     (tuiState_t p_mode, const char* p_strName, const char* p_strValue)                               override;
    bool frameNnameTest                     (tuiState_t p_mode, const char* p_strName)                                                       override;

    void nameNstatus                        (const char* p_strName, uint8_t p_status)                                                       override;
    bool nameNstatus                        (tuiState_t p_mode, const char* p_strName, uint8_t p_status)                                     override;
    bool nameNstatus                        (tuiState_t p_mode, const char* p_strName, uint8_t p_status, bool p_repaint)                     override;

    void content                            (uint8_t p_begin)                                                                               override;
    void content                            (char* p_str, uint8_t p_size)                                                                   override;
    bool content                            (tuiState_t p_mode, char* p_str, uint8_t p_size)                                                 override;
    void content                            (char* p_str, uint8_t p_begin, uint8_t p_size)                                                  override;

    void positionCursor                     (bool p_status, uint8_t p_position)                                                             override;

    void stringPrint                        (uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize)                          override;
    bool stringPrint                        (tuiState_t p_mode, uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize)        override;
    void stringPrint2                       (uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize)                          override;
    bool stringPrint2                       (tuiState_t p_mode, uint8_t p_rowMarker, bool p_select, char* p_pStr, uint32_t p_strSize)        override;

    // utilities
    uint8_t colorCodeTranslator             (kColor_t p_color)                                                   override;

    // section end   **** OUTPUT/DISPLAY functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DEBUG OUTPUT/DISPLAY functions *****
    public:
    void debugPrint                         (uint32_t p_dbgParam1, uint32_t p_dbgParam2, char* p_pStr)                                      override;
    void dbgPrint                           (char* p_str) override;
    void dbgPrint                           (uint16_t p_x, uint16_t p_y, char* p_str) override;

    void dbgExit                            (const char* p_strExit)     override;
    void dbgStep                            (const char* p_strStep)     override;
    void dbgStep                            (const char* p_strStep, uint32_t p_param1, uint32_t p_param2)     override;
    void dbgStep                            (uint8_t p_y, const char* p_strStep, uint32_t p_param1, uint32_t p_param2)     override;
    // section end   **** DEBUG OUTPUT/DISPLAY functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** INPUT/(KEYBOARD-MOUSE) functions *****

    protected:

    bool    uiEventStatus                       (void) override;
    int     uiEventKeyCode                      (void) override;
    tuiEventCode_t  uiHandlerEventCode          (void) override;
    bool    uiMouseEventStatus                  (void) override;
    bool    uiMouseEventCode_ButtonPressed      (void) override;

    private:

    static int g_ncursEventCode;
    static MEVENT g_mouseEvent;

    // section end   **** INPUT/(KEYBOARD-MOUSE) functions *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DEBUG *****

    public:
    void    dbgSetChildrenNumber    (uint8_t p_childrenNumber);

    uint8_t g_childrenNumber;
    // section end   **** DEBUG *****
    // ****************************************************
    // --------------------------



};


#endif  // TUI_GRPH_ABST_UNIT_4_IN_OUT_H
