#include <iostream>
#include "core.hpp"
//#include "tinyxml.h"

int main(int argc, char *args[])
{
	/*TiXmlDocument testfile("test.xml");
	testfile.LoadFile();

	TiXmlElement *head;
	head = testfile.FirstChildElement("CATALOG");
	TiXmlElement *t1;
	t1 = head->FirstChildElement("CD");

	while (t1)
	{
		printf("%s\n", t1->FirstChildElement("TITLE"));
		t1 = t1->NextSiblingElement("CD");
	}*/
	eCore Core;

	Core.mainLoop();
				
	return 0;
}
