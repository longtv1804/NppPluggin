#include <string>
using std::string;

#include "NppApi.h"

void finallizePluginFunction() {

}

void decode() {
    try {
        //list<string> bundle = getSelectedText();
        //showResult(listToString(bundle));
        string text = "this is test";
        showTextToDialog(text);
    }
    catch (const std::exception & e) {
        showMessageBox(e.what());
    }
}