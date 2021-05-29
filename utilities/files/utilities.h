#ifndef FOLDERCHOOSER_H
#define FOLDERCHOOSER_H

//https://stackoverflow.com/questions/12034943/win32-select-directory-dialog-from-c-c
#include <windows.h>
#include <string>
#include <shlobj.h>
//https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
#include <fstream>
#include <streambuf>

using namespace std;

string browseFolder(string start_path, string title, bool rep);

string readFile(string path);

#endif //FOLDERCHOOSER_H
