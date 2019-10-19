#include "ImageUrl.h"


ImageUrl::ImageUrl(string hostName, string imagePath) {
	this->hostName = hostName;
	this->imagePath = imagePath;
}

ImageUrl* parseUrl(string url) {

	string Pattern = "http(s)?://([^/?:]+)(/?.+)";
	regex parse(Pattern);
	string hostName = regex_replace(url, parse, "$2");
	string path = regex_replace(url, parse, "$3");

	return new ImageUrl(hostName, path);
}