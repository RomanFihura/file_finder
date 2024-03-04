#include "file_finder.h"

std::mutex mtx;
std::condition_variable cv;
bool search_finished = false;

void searchThread(const std::wstring& search_directory, const std::wstring& filename) {
    findFile(search_directory, filename);
    {
        std::lock_guard<std::mutex> lock(mtx);
        search_finished = true;
    }
    cv.notify_all();
}

void findFile(const std::wstring& search_directory, const std::wstring& filename) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((search_directory + L"\\*").c_str(), &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        std::vector<std::thread> threads;
        int threadCount = 0;
        do {
            if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
                std::wstring filePath = search_directory + L"\\" + findFileData.cFileName;
                if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
                    if (threadCount < 8) {
                        threads.emplace_back(searchThread, filePath, filename);
                        ++threadCount;
                    }
                    else {
                        findFile(filePath, filename); // Search synchronously if max threads reached
                    }
                }
                else if (wcscmp(findFileData.cFileName, filename.c_str()) == 0) {
                    std::wcout << L"File found: " << filePath << std::endl;
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
        for (auto& thread : threads) {
            thread.join();
        }
    }
}