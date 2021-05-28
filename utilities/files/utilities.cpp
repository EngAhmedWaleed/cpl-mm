#include "utilities.h"

#pragma ide diagnostic ignored "UnusedParameter"
#pragma ide diagnostic ignored "modernize-use-nullptr"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {

    if (uMsg == BFFM_INITIALIZED) {
        std::string tmp = (const char *) lpData;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}

std::string BrowseFolder(std::string start_path, std::string title) {
    TCHAR path[MAX_PATH];

    const char *path_param = start_path.c_str();

    BROWSEINFO bi = {0};
    bi.lpszTitle = (title.c_str());
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (LPARAM) path_param;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0) {
        //get the name of the folder and put it in path
        SHGetPathFromIDList(pidl, path);

        //free memory used
        IMalloc *imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc))) {
            imalloc->Free(pidl);
            imalloc->Release();
        }

        return path;
    }

    return "";
}

std::string readFile(std::string path) {
    std::ifstream stream(path);
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return str.substr(0, str.length() - 1);
}
