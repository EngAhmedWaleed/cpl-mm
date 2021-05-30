#include "files.h"

static string browseFolder_(string start_path, string title);

string browseFolder(string start_path, string title, bool rep) {
    string path = browseFolder_(start_path, title);
    if (rep && path.empty())
        path = browseFolder(start_path, title, rep);
    return path;
}

string readFile(string path) {
    ifstream stream(path);
    string str((istreambuf_iterator<char>(stream)),
               istreambuf_iterator<char>());
    return str.substr(0, str.length() - 1);
}

vector<string> ls(string folder, string filter) {
    vector<string> names;
    string search_path = folder + "/" + filter;
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

static int CALLBACK browseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if (uMsg == BFFM_INITIALIZED) {
        string tmp = (const char *) lpData;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }
    return 0;
}

static string browseFolder_(string start_path, string title) {
    TCHAR path[MAX_PATH];

    const char *path_param = start_path.c_str();

    BROWSEINFO bi = {0};
    bi.lpszTitle = (title.c_str());
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = browseCallbackProc;
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
