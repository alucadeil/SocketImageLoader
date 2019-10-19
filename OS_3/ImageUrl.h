#ifndef SOME_UNIQUE_ID
#define SOME_UNIQUE_ID
#include <string>
#include <regex>

using namespace std;

class ImageUrl
{
public:
	string hostName;
	string imagePath;

	ImageUrl(string hostName, string imagePath);

};

ImageUrl* parseUrl(string url);

#endif