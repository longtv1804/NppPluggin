//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef GOTILINE_DLG_H
#define GOTILINE_DLG_H

#include "DockingDlgInterface.h"
#include "resource.h"
#include "../src/PluginInterface.h"

typedef size_t idx_t;
struct NppData;

class DockingDialog : public DockingDlgInterface
{
public :
	DockingDialog();
    DockingDialog(const DockingDialog& other) = delete;
    ~DockingDialog();

    void initDialog(HINSTANCE hInst, NppData& nppData);

    void doDialog();
    void hide();

	void writeCmdText(size_t length, const char* text);
	void writeText(size_t length, const char* text);
	void clearText();

	NppData m_nppData;


    virtual void display(bool toShow = true) const {
        DockingDlgInterface::display(toShow);
        //if (toShow)
        //    ::SetFocus(::GetDlgItem(_hSelf, ID_GOLINE_EDIT));
    };

	void setParent(HWND parent2set){
		_hParent = parent2set;
	};

protected :
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private :
	void createOutputWindow(HWND hParentWindow);

    //int getLine() const {
    //    BOOL isSuccessful;
    //    int line = ::GetDlgItemInt(_hSelf, ID_GOLINE_EDIT, &isSuccessful, FALSE);
    //    return (isSuccessful?line:-1);
    //};

	LRESULT callScintilla(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return ::SendMessage(m_scintilla, message, wParam, lParam);
	}
	DockingDialog& operator = (const DockingDialog&); // assignment operator disabled

	//HWND m_hNpp;
	tTbData* m_data;
	HWND m_scintilla;
};

#endif //GOTILINE_DLG_H
