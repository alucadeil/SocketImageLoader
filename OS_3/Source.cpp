#include <winsock.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

#define WINSOCK_VERSION 0x0101
int currentAddressNumber = 1;
string addressArray[100];


class ImageLink {
public:
	string hostName;
	string imagePath;
	string fileFormat;

	ImageLink(string hostName, string imagePath, string fileFormat) {
		this->hostName = hostName;
		this->imagePath = imagePath;
		this->fileFormat = fileFormat;
	}
};

void StartWinSock();
void StopWinSock();
ImageLink convertStrToLink(string inputLink);
char* createHandle(ImageLink link);
char* strToChar(string str);
void download(string get_url, string name_photo);

void main()
{
	string get_url;
	int i = 1;
	while (1) {
		cout << "Insert URL: ";
		cin >> get_url;
		string name_photo = to_string(i) + ".";
		thread thr(download, get_url, name_photo);
		thr.detach();
		i++;
	}
}


void download(string get_url, string name_photo) {
	ImageLink imageLink = convertStrToLink(get_url);
	char name[8];
	strcpy_s(name, name_photo.c_str());
	strcat_s(name, strToChar(imageLink.fileFormat));
	ofstream file;
	file.open(name, ios::binary);
	SOCKET s;
	int out = 1;
	StartWinSock();
	int write;

	struct hostent* hp;
	hp = gethostbyname(strToChar(imageLink.hostName));
	s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ssin;
	ssin.sin_family = AF_INET;
	ssin.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr[0];
	ssin.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr[1];
	ssin.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr[2];
	ssin.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr[3];
	ssin.sin_port = htons(80);

	int ifsockopen = connect(s, (sockaddr*)& ssin, sizeof(ssin));
	const char* sct = createHandle(imageLink);
	send(s, sct, strlen(sct), 0);
	char get[1];
	string pocket;
	while (ifsockopen == 0)
	{
		out = recv(s, get, sizeof(get), 0);

		if (out == 0)
		{
			break;
		}
		if (out == -1)
		{
			break;
		}
		pocket += string(get, sizeof(get));
	}
	closesocket(s);
	StopWinSock();
	pocket.erase(0, pocket.find("\r\n\r\n") + 4);

	file << pocket;
	//cout << name_photo << " download succsesfull" << endl;
	file.close();
}

void StartWinSock()
{
	WSADATA wsaData;
	if (WSAStartup(WINSOCK_VERSION, &wsaData))
	{
		//printf("Winsock not initialized\n");
		WSACleanup();
	}
	//else printf("Winsock initialized\n Insert URL: ");

}

void StopWinSock()
{
	WSACleanup();
	//if (WSACleanup())
		//printf("Error cleanup\n");
	//else printf("Cleanup is ok\n");
}

ImageLink convertStrToLink(string inputLink) {
	char hostName[100];
	char imagePath[100];
	char temporaryBuff[200];
	char transformBuff1[200];
	char transformBuff2[200];
	char fileFormat[10];

	for (int i = 0; i < inputLink.length(); i++) {
		transformBuff1[i] = inputLink[i];
	}
	transformBuff1[inputLink.length()] = '\0';
	sscanf(transformBuff1, "%*[^//]%s", transformBuff2);
	sscanf(transformBuff2, "%*2c%s", transformBuff1);

	inputLink = (string)transformBuff1;

	currentAddressNumber++;
	addressArray[currentAddressNumber] = inputLink;
	int length = inputLink.length();
	for (int j = 0; j < length; j++) {
		temporaryBuff[j] = inputLink[j];
		if (temporaryBuff[j] == '/') {
			addressArray[currentAddressNumber][j] = '.';
		}
		else {
			addressArray[currentAddressNumber][j] = inputLink[j];
		}
	}
	temporaryBuff[length] = '\0';
	sscanf(temporaryBuff, "%[^/]%s", hostName, imagePath);

	sscanf(imagePath, "%*[^.]%s", transformBuff1);
	sscanf(transformBuff1, "%*c%s", fileFormat);
	ImageLink* imageLink = new ImageLink(hostName, imagePath, fileFormat);
	return *imageLink;
}

char* createHandle(ImageLink link)
{
	char str[1024];
	string buff1 = "GET ";
	string http_buff1 = " HTTP/1.1\r\n";
	string buff2 = "Host: ";
	string buff3 = "\n\n";
	buff1 += link.imagePath;
	buff1 += http_buff1;
	buff1 += buff2;
	buff1 += link.hostName;
	buff1 += buff3;
	int length = buff1.length();
	for (int i = 0; i < length; i++)
	{
		str[i] = buff1[i];
	}
	str[length] = '\0';
	return str;
}

char* strToChar(string str)
{
	int length = str.length();
	char* a = new char[length];
	for (int i = 0; i < length; i++)
	{
		a[i] = str[i];
	}
	a[length] = '\0';
	return a;
}