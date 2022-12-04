#pragma once
#include <string>
using std::string;

//#include "../../DockingFeature/Docking.h"
#include "../../DockingFeature/DockingDialog.h"

// dialog class
class ResultDialog {
private:
    DockingDialog* mDockingDialog;

    void showDialog();
    void hideDialog();
    void message(const char* msg);
    void clear();
    void writeText(string text);

public:
    ResultDialog();
    ~ResultDialog();
    void init(HANDLE h, NppData data);
    void showText(string str);
};
