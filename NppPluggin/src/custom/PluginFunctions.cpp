#include <string>
using std::string;

#include "NppApi.h"

void finallizePluginFunction() {

}

void decode() {
    try {
        string path = getFilePath();
        
        string text = getExactSelectedText();
        showTextToDialog(path + "\n" + text);

        path = "E:\\WorkSpace_longtv1804\\GIT\\NppPluggin\\Debug\\op.txt";
        openFile(path);
    }
    catch (const std::exception & e) {
        showMessageBox(e.what());
    }
}