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
		std::vector<std::pair<std::string, std::string>>attributeList;
		std::string uri;

		//Comparator so that we can sort values based on attribute
		bool operator < (const PlaylistTag& tag) const
		{
			std::string valueLeft;
			std::string valueRight;

			//Let's find this tag's attribute value
			for (size_t i = 0; i < attributeList.size(); i++)
			{
				if (attributeList[i].first.compare(m_attributeToSort) == 0)
				{
					valueLeft = attributeList[i].second;
				}
			}

			//Now let's find the tag we're comaring to's attribute value
			for (size_t i = 0; i < tag.attributeList.size(); i++)
			{
				if (tag.attributeList[i].first.compare(m_attributeToSort) == 0)
				{
					valueRight = tag.attributeList[i].second;
				}
			}

			//Check if value wasn't found in either direction before checking which value is greater
			if (valueLeft.empty() && !valueRight.empty())
			{
				return true;
			}
			else if (!valueLeft.empty() && valueRight.empty())
			{
				return false;
			}
			else
			{
				//Check if we're dealing with strings or ints
				char* isNotAnInteger;
				long convertedIntLeft = strtol(valueLeft.c_str(), &isNotAnInteger, 10);
				if (isNotAnInteger)
				{
					long convertedIntRight = strtol(valueRight.c_str(), &isNotAnInteger, 10);
					return convertedIntLeft < convertedIntRight;
				}
				return valueLeft < valueRight;
			}
		}
	};

	std::vector<PlaylistTag> m_playListData;
	static std::string m_attributeToSort;

public:

	//Default constructor
	M3U8();

	//Constructor that takes a file as a parameter and parses it
	M3U8(std::ifstream& inFile);

	//Method for parshing a file into a M3U8 object
	void parsePlaylistFile(std::ifstream& inFile);

	//Method for writing data back out to a file
	void writeToFile(std::ofstream& outFile);
	
	//Method for sorting a file based on Attribute Value
	void sortPlaylist(const std::string& attribute);

	//Default Destructor
	~M3U8();
	
};
#endif