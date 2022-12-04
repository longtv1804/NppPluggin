#include "DialogController.h"

void ResultDialog::showDialog()
{
    assert(mDockingDialog);
    if (mDockingDialog)
    {
        //GILRelease release;
        mDockingDialog->doDialog();
    }
}
void ResultDialog::hideDialog()
{
    assert(mDockingDialog);
    if (mDockingDialog)
    {
        //GILRelease release;
        mDockingDialog->hide();
    }
}
void ResultDialog::message(const char* msg)
{
    assert(mDockingDialog);
    if (mDockingDialog)
    {
        //GILRelease release;
        mDockingDialog->writeCmdText(strlen(msg), msg);
    }
}
void ResultDialog::clear()
{
    assert(mDockingDialog);
    if (mDockingDialog)
    {
        //GILRelease release;
        mDockingDialog->clearText();
    }
}
void ResultDialog::writeText(string text)
{
    assert(mDockingDialog);
    if (mDockingDialog)
    {
        mDockingDialog->writeText(text.size(), text.c_str());
    }
}

ResultDialog::ResultDialog() {
    mDockingDialog = new DockingDialog();
}
ResultDialog::~ResultDialog() {
    if (mDockingDialog) delete mDockingDialog;
}

void ResultDialog::init(HANDLE h, NppData data) {
    mDockingDialog->initDialog((HINSTANCE)h, data);
}
void ResultDialog::showText(string str) {
    clear();
    showDialog();
    writeText(str);
}