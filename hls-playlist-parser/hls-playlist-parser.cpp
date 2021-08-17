// hls-playlist-parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>

//For this assignment we'll be using the Win32 API URLDownloadToFile
#include <windows.h>
#pragma comment(lib, "Urlmon.lib")

//Include our object for storing and sorting M3U8 files
#include "M3U8.hpp"

int main()
{
    //The URL to download from 
    const wchar_t* srcURL = L"https://lw.bamgrid.com/2.0/hls/vod/bam/ms02/hls/dplus/bao/master_unenc_hdr10_all.m3u8";

    //The destination file 
    const wchar_t* destFile = L"fetchedPlaylist.m3u8";

    //Attempt to download the file to a local copy for processing
    if (URLDownloadToFile(NULL, srcURL, destFile, 0, NULL) == S_OK){

        std::cout << "Successfully fetched file from the requested URL" << '\n';

        //Setup M3U8 with fstream constructor to be parsed and have it's attributes sorted
        std::ifstream infile("fetchedPlaylist.m3u8");
        M3U8 playlistFile(infile);
        infile.close();

        //Write back to new file
        //Note: the output's attribute lists are already sorted when the playlist object is created, since it uses a map for storage
        std::ofstream outFile("sortedPlaylist.m3u8");
        playlistFile.writeToFile(outFile);
        outFile.close();
    }
    else{
        std::cout << "File Fetch unsuccessful" << '\n';
        return 0;
    }

}
