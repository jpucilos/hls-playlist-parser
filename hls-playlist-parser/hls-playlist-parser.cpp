// hls-playlist-parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>

//For this assignment we'll be using the Win32 API URLDownloadToFile
#include <windows.h>
#pragma comment(lib, "Urlmon.lib")

//Include our object for storing and sorting M3U8 files
#include "M3U8.hpp"

//In this quick test, we're taking a playlist from a given URL, parsing it, sorting it based on several fields, and then printing it back out to an output file
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

        //Sort Tags based on attribute value bandwidth
        playlistFile.sortPlaylist("BANDWIDTH");

        //Write back to new file
        std::ofstream outFile("sortedPlaylistBandwidth.m3u8");
        playlistFile.writeToFile(outFile);
        outFile.close();

        //Sort Tags based on attribute value average bandwidth
        playlistFile.sortPlaylist("AVERAGE-BANDWIDTH");

        //Write back to new file
        std::ofstream outFile2("sortedPlaylistAverageBandwidth.m3u8");
        playlistFile.writeToFile(outFile2);
        outFile2.close();

    }
    else{
        std::cout << "File Fetch unsuccessful" << '\n';
        return 0;
    }

}
