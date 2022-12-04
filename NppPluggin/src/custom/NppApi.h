#pragma once
#include <string>
#include <list>
#include <windows.h>
using std::string;
using std::list;

/*
 * get current document which is displayed.
 */
HWND getCurrentScintilla();

string listToString(list<string> bundle);

/*
 * show a text in a windows similar as searching result.
*/
void showTextToDialog(string text);

/*
 * show pupup as notification
*/
void showMessageBox(string str);


void showTextInCurentDocument(string str);
void showTextInNewDocument(string str);


list<string> getSelectedText();
string getExactSelectedText();


