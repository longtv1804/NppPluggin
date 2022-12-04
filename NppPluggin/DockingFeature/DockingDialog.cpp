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

#include "DockingDialog.h"
#include "../src/PluginDefinition.h"
#include <WinUser.h>
DockingDialog::DockingDialog() :
	DockingDlgInterface(IDD_PLUGINGOLINE_DEMO),
	m_data(new tTbData),
	m_scintilla(NULL),
	m_nppData{ 0,0,0 }
{}

DockingDialog::~DockingDialog()
{
	if (m_scintilla)
	{
		::SendMessage(_hParent, NPPM_DESTROYSCINTILLAHANDLE, 0, reinterpret_cast<LPARAM>(m_scintilla));
		m_scintilla = NULL;
	}
	if (m_data)
	{
		delete m_data;
		m_data = NULL;
	}
}

void DockingDialog::initDialog(HINSTANCE hInst, NppData& nppData)
{
	DockingDlgInterface::init(hInst, nppData._nppHandle);
	createOutputWindow(nppData._nppHandle);

	m_nppData = nppData;
}
INT_PTR CALLBACK DockingDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_INITDIALOG:
		{
			SetParent(m_scintilla, _hSelf);
			ShowWindow(m_scintilla, SW_SHOW);
			return FALSE;
		}
		case WM_SIZE:
			MoveWindow(m_scintilla, 0, 0, LOWORD(lParam), HIWORD(lParam) - 30, TRUE);
			// ::SendMessage(m_scintilla, WM_SIZE, 0, MAKEWORD(LOWORD(lParam) - 10, HIWORD(lParam) - 30));
			return FALSE;

		default :
			return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
	}

}


void DockingDialog::createOutputWindow(HWND hParentWindow)
{
	m_scintilla = (HWND)::SendMessage(_hParent, NPPM_CREATESCINTILLAHANDLE, 0, reinterpret_cast<LPARAM>(hParentWindow));

	LONG_PTR currentStyle = GetWindowLongPtr(m_scintilla, GWL_STYLE);
	SetWindowLongPtr(m_scintilla, GWL_STYLE, currentStyle | WS_TABSTOP);

	LONG_PTR exstyles = GetWindowLongPtr(m_scintilla, GWL_EXSTYLE);
	if ((exstyles & WS_EX_LAYOUTRTL) == WS_EX_LAYOUTRTL)
	{
		SetWindowLongPtr(m_scintilla, GWL_EXSTYLE, exstyles & (~WS_EX_LAYOUTRTL));
	}

	callScintilla(SCI_SETREADONLY, 1, 0);

	/*  Style bits
	 *  LSB  0 - stderr = 1
	 *       1 - hotspot
	 *       2 - warning
	 *       ... to be continued
	 */

	 // Set the codepage to UTF-8
	callScintilla(SCI_SETCODEPAGE, 65001);

	// 0 is stdout, black text
	callScintilla(SCI_STYLESETSIZE, 0 /* = style number */, 8 /* = size in points */);

	// 1 is stderr, red text
	callScintilla(SCI_STYLESETSIZE, 1 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 1, RGB(250, 0, 0));

	// 2 is stdout, black text, underline hotspot
	callScintilla(SCI_STYLESETSIZE, 2 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETUNDERLINE, 2 /* = style number */, 1 /* = underline */);
	callScintilla(SCI_STYLESETHOTSPOT, 2, 1);

	// 3 is stderr, red text, underline hotspot
	callScintilla(SCI_STYLESETSIZE, 3 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 3, RGB(250, 0, 0));
	callScintilla(SCI_STYLESETUNDERLINE, 3 /* = style number */, 1 /* = underline */);
	callScintilla(SCI_STYLESETHOTSPOT, 3, 1);

	// 4 stdout warning without hotspot
	callScintilla(SCI_STYLESETSIZE, 4 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 4, RGB(199, 175, 7));  // mucky yellow

	// 5 stderr warning without hotspot
	callScintilla(SCI_STYLESETSIZE, 5 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 5, RGB(255, 128, 64));  // orange

	// 6 is hotspot, stdout, warning
	callScintilla(SCI_STYLESETSIZE, 6 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 6, RGB(199, 175, 7));  // mucky yellow
	callScintilla(SCI_STYLESETUNDERLINE, 6 /* = style number */, 1 /* = underline */);
	callScintilla(SCI_STYLESETHOTSPOT, 6, 1);

	// 7 is hotspot, stderr, warning
	callScintilla(SCI_STYLESETSIZE, 7 /* = style number */, 8 /* = size in points */);
	callScintilla(SCI_STYLESETFORE, 7, RGB(255, 128, 64));  // orange
	callScintilla(SCI_STYLESETUNDERLINE, 7 /* = style number */, 1 /* = underline */);
	callScintilla(SCI_STYLESETHOTSPOT, 7, 1);

	// 8 is colored stdout inidcator
	//intptr_t defaultColor = callScintilla(SCI_STYLEGETFORE, 0, 0);
	callScintilla(SCI_INDICSETSTYLE, 8 /* = indicator number */, INDIC_TEXTFORE);
	//callScintilla(SCI_INDICSETFORE, 8, m_colorOutput ? m_user_color : defaultColor); // green

	callScintilla(SCI_USEPOPUP, 0);
	callScintilla(SCI_SETLEXER, /*SCLEX_CONTAINER*/ 0);
}

void DockingDialog::writeCmdText(size_t length, const char* text)
{
	::SendMessage(m_scintilla, SCI_SETREADONLY, 0, 0);
	for (idx_t i = 0; i < length; ++i)
	{
		if (text[i] == '\r')
		{
			::SendMessage(m_scintilla, SCI_APPENDTEXT, i, reinterpret_cast<LPARAM>(text));
			text += i + 1;
			length -= i + 1;
			i = 0;
		}
	}

	if (length > 0)
	{
		::SendMessage(m_scintilla, SCI_APPENDTEXT, length, reinterpret_cast<LPARAM>(text));
	}

	::SendMessage(m_scintilla, SCI_SETREADONLY, 1, 0);

	::SendMessage(m_scintilla, SCI_GOTOPOS, ::SendMessage(m_scintilla, SCI_GETLENGTH, 0, 0), 0);
}

void DockingDialog::writeText(size_t length, const char* text)
{
	::SendMessage(m_scintilla, SCI_SETREADONLY, 0, 0);
	for (idx_t i = 0; i < length; ++i)
	{
		if (text[i] == '\r')
		{
			::SendMessage(m_scintilla, SCI_APPENDTEXT, i, reinterpret_cast<LPARAM>(text));
			text += i + 1;
			length -= i + 1;
			i = 0;
		}
	}

	if (length > 0)
	{
		::SendMessage(m_scintilla, SCI_APPENDTEXT, length, reinterpret_cast<LPARAM>(text));
	}

	::SendMessage(m_scintilla, SCI_SETREADONLY, 1, 0);

	::SendMessage(m_scintilla, SCI_GOTOPOS, ::SendMessage(m_scintilla, SCI_GETLENGTH, 0, 0), 0);
}

void DockingDialog::doDialog()
{
	if (!isCreated())
	{
		create(m_data);

		assert(m_data);
		if (m_data)
		{
			// define the default docking behaviour
			m_data->uMask = DWS_DF_CONT_BOTTOM | DWS_ICONTAB;
			m_data->pszName = _T("DD-Tool by Trinh Vu Long");

			RECT rc;
			rc.bottom = 0;
			rc.top = 0;
			rc.left = 0;
			rc.right = 0;
			m_data->hIconTab = (HICON)::LoadImage(_hInst, MAKEINTRESOURCE(IDB_PYTHON), IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS | LR_LOADTRANSPARENT);
			//m_data->hIconTab = /*m_hTabIcon*/ 0;
			m_data->pszModuleName = _T("RIL-Decoder");
			m_data->dlgID = -1; /* IDD_CONSOLE */
			m_data->pszAddInfo = _T("This plugin is developed by LONG.TV2");
			m_data->iPrevCont = -1;
			m_data->hClient = _hSelf;
			m_data->rcFloat = rc;


			::SendMessage(_hParent, NPPM_DMMREGASDCKDLG, 0, reinterpret_cast<LPARAM>(m_data));

			// Parse the whole doc, in case we've had errors that haven't been parsed yet
			callScintilla(SCI_COLOURISE, 0, -1);
		}
	}
	display(true);
}
void DockingDialog::hide()
{
	display(false);
	HWND current_HWND = ::GetFocus();
	if (/*m_hInput == current_HWND || */m_scintilla == current_HWND)
	{
		intptr_t currentView = MAIN_VIEW;
		::SendMessage(m_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentView);
		HWND sci = (currentView == MAIN_VIEW) ? m_nppData._scintillaMainHandle : m_nppData._scintillaSecondHandle;

		DWORD currentThreadId = GetCurrentThreadId();
		DWORD otherThreadId = GetWindowThreadProcessId(sci, NULL);

		AttachThreadInput(currentThreadId, otherThreadId, TRUE);
		SetFocus(sci);
		AttachThreadInput(currentThreadId, otherThreadId, FALSE);
	}
}
void DockingDialog::clearText()
{
	::SendMessage(m_scintilla, SCI_SETREADONLY, 0, 0);
	::SendMessage(m_scintilla, SCI_CLEARALL, 0, 0);
	::SendMessage(m_scintilla, SCI_SETREADONLY, 1, 0);
}

