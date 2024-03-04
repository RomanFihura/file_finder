#pragma once
#include <iostream>
#include <windows.h> //operations with files and catalogues
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

void findFile(const std::wstring& search_directory, const std::wstring& filename);
void searchThread(const std::wstring& search_directory, const std::wstring& filename);