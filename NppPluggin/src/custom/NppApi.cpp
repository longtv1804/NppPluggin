#include "NppApi.h"
//#include <WinUser.h>
#include "DialogController.h"
#include "../menuCmdID.h"

ResultDialog* mResultDialog = NULL;

// variables from PluginDefinition.cpp
extern NppData nppData;
extern HANDLE hModule;

void finallizeNppApi() {
    if (mResultDialog != NULL) {
        delete mResultDialog;
    }
}

HWND getCurrentScintilla() {
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1) {
        return NULL;
    }
    return ((which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle);
}


string listToString(list<string> bundle) {
    string ret = "";
    for (string str : bundle) {
        ret += str;
    }
    return ret;
}
void showTextToDialog(string text) {
    if (mResultDialog == NULL) {
        mResultDialog = new ResultDialog();
        mResultDialog->init(hModule, nppData);
    }
    mResultDialog->showText(text);
}

void showMessageBox(string str) {
    ::MessageBox(NULL, (LPWSTR)str.c_str(), TEXT("IPC-QMI-Decoder"), MB_OK);
}
void showTextInCurentDocument(string str) {
    ::SendMessage(getCurrentScintilla(), SCI_SETTEXT, 0, (LPARAM)str.c_str());
}
void showTextInNewDocument(string str) {
    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);
    ::SendMessage(getCurrentScintilla(), SCI_SETTEXT, 0, (LPARAM)str.c_str());
}

#define MAX_LINE_CHAR 5000
list<string> getSelectedText() {
    HWND curScintilla = getCurrentScintilla();
    //if (curScintilla == null) return null;

    int startPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int endPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    int startLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, startPos, 0);
    int endLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, endPos, 0);

    char* textLine = new char[MAX_LINE_CHAR];
    list<string> ret;
    for (int i = startLine; i <= endLine; i++) {
        int len = (int) ::SendMessage(curScintilla, SCI_LINELENGTH, i, 0);
        ::SendMessage(curScintilla, SCI_GETLINE, i, (LPARAM)textLine);
        string text(textLine, len);
        ret.push_back(text);
    }
    return ret;
}
