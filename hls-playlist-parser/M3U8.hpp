/*
	M3U8.hpp
	
	This header file contains the class declaration for M3U8,
	an object that can fetch a M3U8 HLS playlist file from a 
	remote URL, parse and sort the data from said file, and output
	to a new file
	
	Author: Joseph Puciloski
	Date: August 15th, 2021

*/
#ifndef M3U8_hpp
#define M3U8_hpp

#include <fstream>
#include <map>
#include <vector>

class M3U8 {
private:

	//Let's make a container for the data that can be represented in each of our tags
	struct PlaylistTag
	{
		std::string tag;
		//Note: by using a map here the attributes are sorted alphabetically as they're inserted
		std::map<std::string, std::string> attributeList;
		std::string uri;

	};

	std::vector<PlaylistTag> m_playListData;
	
public:

	//Default constructor
	M3U8();

	//Constructor that takes a file as a parameter and parses it
	M3U8(std::ifstream& inFile);

	//Method for parshing a file into a M3U8 object
	void parsePlaylistFile(std::ifstream& inFile);

	//Method for writing data back out to a file
	void writeToFile(std::ofstream& outFile);
	
	//Default Destructor
	~M3U8();
	
	//
	
};
#endif