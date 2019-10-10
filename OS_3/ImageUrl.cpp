#include "ImageUrl.h"

ImageUrl::ImageUrl(string hostName, string imagePath, string fileFormat) {
	this->hostName = hostName;
	this->imagePath = imagePath;
	this->fileFormat = fileFormat;
}

ImageUrl::parseUrl(string url) {

	string hostPattern = "https?:\/\/([\w\.]+[a-z]{2,6}\.?)";

	return;
}