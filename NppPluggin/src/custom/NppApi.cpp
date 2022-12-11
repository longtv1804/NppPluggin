#include <atlstr.h> // for convert TCHAR >< string

#include "NppApi.h"
#include "DialogController.h"
#include "../menuCmdID.h"
#include "Feature.h"

#ifdef FEATURE_DEBUG_LOG
#include "../../../Logging/Logging.h"
using std::to_string;
#endif // FEATURE_DEBUG_LOG

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
list<string> getSelectedLines() {
    HWND curScintilla = getCurrentScintilla();
    //if (curScintilla == null) return null;

    int startPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int endPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    int startLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, startPos, 0);
    int endLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, endPos, 0);

    char textLine[MAX_LINE_CHAR];
    list<string> ret;
    for (int i = startLine; i <= endLine; i++) {
        int len = (int) ::SendMessage(curScintilla, SCI_LINELENGTH, i, 0);
        ::SendMessage(curScintilla, SCI_GETLINE, i, (LPARAM)textLine);
        string text(textLine, len);
        ret.push_back(text);
    }
    return ret;
}

string getExactSelectedText() {
    HWND curScintilla = getCurrentScintilla();
    if (curScintilla == NULL) return "";

    int startPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int endPos = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    int startLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, startPos, 0);
    int endLine = (int) ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, endPos, 0);

    if (startLine != endLine) {
        throw new std::exception("selected text should be on a single line");
    }
    else if (endPos <= startPos) {
        return "";
    }
    else {
        TCHAR text[MAX_LINE_CHAR] = { 0, };
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)text);
        std::wstring tempStr(text);
        return string(tempStr.begin(), tempStr.end());
    }
}

string getFilePath() {
    TCHAR cpath[MAX_PATH] = { 0, };
    bool res = ::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, (WPARAM)MAX_PATH, (LPARAM)cpath);
    std::wstring tempStr(cpath);
    string path(tempStr.begin(), tempStr.end());
    return path; 
}

string getFileName() {
    TCHAR cName[MAX_PATH] = { 0, };
    bool res = ::SendMessage(nppData._nppHandle, NPPM_GETFILENAME, (WPARAM)MAX_PATH, (LPARAM)cName);
    std::wstring tempStr(cName);
    return string(tempStr.begin(), tempStr.end());
}

string getCurrentFileDirectory() {
    string path = getFilePath();
    string fileName = getFileName();
    if (path.empty() || fileName.empty()) {
        return "";
    }
    int pos = path.find(fileName);
    if (pos == string::npos) {
        return "";
    }
    return path.erase(pos, fileName.size());
}

void openFile(string path) {
    TCHAR tPath[MAX_PATH];
    _tcscpy_s(tPath, CA2T(path.c_str()));
    
    ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)tPath);
}