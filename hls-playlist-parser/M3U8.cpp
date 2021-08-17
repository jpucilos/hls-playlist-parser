/*
	M3U8.cpp

	This source file contains the definitions for M3U8,
	an object that can fetch a M3U8 HLS playlist file from a
	remote URL, parse and sort the data from said file, and output
	to a new file

	Author: Joseph Puciloski
	Date: August 15th, 2021

*/
#include "M3U8.hpp"
#include <sstream>
#include <algorithm>

//Set up our static attribute to sort variable
std::string M3U8::m_attributeToSort;
 
//Constructor that takes an file as input
M3U8::M3U8(std::ifstream& inFile) {
	parsePlaylistFile(inFile);
}

//Method for parshing a file into a M3U8 object
void M3U8::parsePlaylistFile(std::ifstream& inFile)
{
	//Let's read the file one line at a time and handle each tag as a string
	std::string line;
	while (std::getline(inFile, line))
	{
		//Check if this is a valid tag, i.e. begins with #EXT
		if (line.substr(0, 4).compare("#EXT") == 0)
		{
			//Create temporary tag along with a variable to track index of the string
			PlaylistTag temp;
			int tempIndex = line.find(':');

			//Start by finding and saving the tag name, then erasing this from the string
			if (tempIndex != std::string::npos)
			{
				temp.tag = line.substr(0, tempIndex);
				line.erase(0, tempIndex + 1);

				//Next, let's fill the attributeList for this tag, if applicable
				while (true)
				{
					tempIndex = line.find('=');
					if (tempIndex == std::string::npos)
					{
						//This is the case for tags such as #EXT-X-VERSION:<n>, we can consider the key to be empty for tags like these
						std::string emptyString = "";
						temp.attributeList.push_back(std::pair<std::string, std::string>(emptyString, line));
						break;
					}
					else
					{
						//This tag has a key and value, let's save a copy of the key temporarily and trim the string
						std::string tempKey = line.substr(0, tempIndex);
						line.erase(0, tempIndex + 1);

						//Now let's find either a comma or the end of string
						tempIndex = line.find(',');
						if (tempIndex == std::string::npos)
						{
							//We've reached the end of the atrribute list, add entry and break
							temp.attributeList.push_back(std::pair<std::string, std::string>(tempKey, line));
							break;
						}
						else
						{
							//This isn't the last attribute to process, so let's save a copy of the value temporarily and trim the string
							std::string tempValue = line.substr(0, tempIndex);
							line.erase(0, tempIndex + 1);
							temp.attributeList.push_back(std::pair<std::string, std::string>(tempKey, tempValue));
						}
					}
				}
			}
			else
			{
				//This is the case where this tag doesn't contain a colon, tag is the whole line
				temp.tag = line;
			}

			//Check if Tag has a URI and add to tag
			if (temp.tag.compare("#EXT-X-STREAM-INF") == 0)
			{
				std::getline(inFile, line);
				temp.uri = line;
			}

			//Now that we've filled our playlistTag, let's push it onto our vector for holding the tags
			m_playListData.push_back(temp);
		}
	}
}

//Method for writing data back out to a file, with the option for filtering out tags
//that don't contain a certain attribute
void M3U8::writeToFile(std::ofstream& outFile)
{
	//Let's iterate through the tags of our playlist data
	for (auto& it : m_playListData){

		//Start with tag
		outFile << it.tag;
		
		//Now let's handle the attributes list
		if(!it.attributeList.empty()) { 
			outFile << ":";
			for (auto attr_it = it.attributeList.begin(); attr_it != it.attributeList.end(); ++attr_it) {
				
				//This is the case of an attribute list of one value and no key
				if (attr_it->first.compare("") == 0) {
					outFile << attr_it->second;
				}
				else{
					outFile << attr_it->first + "=" + attr_it->second;
					if (std::next(attr_it) != it.attributeList.end()) {
						//Print a comma for all but the end
						outFile << ",";
					}
				}
			}

			//This handles printed the URI along with a new line
			if (!it.uri.empty()){
				outFile << '\n' << it.uri;
			}
		}
		//Next tag, new line
		outFile << '\n';
	}
}

//Method for sorting a file based on Attribute Value
void M3U8::sortPlaylist(const std::string& attribute)
{
	m_attributeToSort = attribute;
	std::sort(m_playListData.begin(), m_playListData.end());
}

//Default, no parameter constructor for our object
M3U8::M3U8(){}

//Default destructor for this project
M3U8::~M3U8() {}