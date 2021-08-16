// hls-playlist-parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

//For this assignment we'll be using the Win32 API URLDownloadToFile
#include <windows.h>
#pragma comment(lib, "Urlmon.lib")

//Include our object for storing and sorting M3U8 files
#include "M3U8.hpp"

int main()
{
    // the URL to download from 
    const wchar_t* srcURL = L"https://lw.bamgrid.com/2.0/hls/vod/bam/ms02/hls/dplus/bao/master_unenc_hdr10_all.m3u8";

    // the destination file 
    const wchar_t* destFile = L"temp.m3u8";

    //Attempt to download the file to a local copy for processing
    if (URLDownloadToFile(NULL, srcURL, destFile, 0, NULL) == S_OK){
        std::cout << "Successfully fetched file from the requested URL" << '\n';
    }
    else{
        std::cout << "File Fetch unsuccessful" << '\n';
        return 0;
    }


}
