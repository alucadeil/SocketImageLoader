#ifndef SOME_UNIQUE_ID
#define SOME_UNIQUE_ID
#include <string>

using std::string;

class ImageUrl
{
public:
	string hostName;
	string imagePath;
	string fileFormat;

	ImageUrl(string hostName, string imagePath, string fileFormat);

	ImageUrl parseUrl(string url);
};

#endif