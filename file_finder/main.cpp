#include "..\file_finder_server\file_finder.h"

int main() {
    std::wstring search_directory = L"C:\\";
    std::wstring filename;
    std::wcout << L"Enter the name of the file to search for: ";
    std::wcin >> filename;

    findFile(search_directory, filename);

    return 0;
}
