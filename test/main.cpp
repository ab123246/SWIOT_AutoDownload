#include <iostream>

/*run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "stdafx.h"
#include <string>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

class Person
{
public:
	string	m_sName;
	string	m_sNickName;
	int		m_nAge;
};
/*
void SaveXml(Person* person, string file)
{	
	TiXmlDocument xmlDoc;

	TiXmlNode* rootElement = xmlDoc.InsertEndChild(TiXmlElement("Person"));

	rootElement
		->InsertEndChild(TiXmlElement("Name"))
		->InsertEndChild(TiXmlText(person->m_sName.c_str()));

	rootElement
		->InsertEndChild(TiXmlElement("NickName"))
		->InsertEndChild(TiXmlText(person->m_sNickName.c_str()));

	char buffer[256];
	_itoa(person->m_nAge, buffer,10);
	rootElement
		->InsertEndChild(TiXmlElement("Age"))
		->InsertEndChild(TiXmlText(buffer));

	xmlDoc.SaveFile(file.c_str());
}
*/
void LoadXml(string file, Person* person)
{	
	TiXmlDocument xmlDoc(file.c_str());

	xmlDoc.LoadFile();

	if(xmlDoc.ErrorId() > 0)
		return;

	TiXmlElement* pRootElement = xmlDoc.RootElement();

	if(!pRootElement)
		return;

	TiXmlElement* pNode = NULL;
	
	pNode = pRootElement->FirstChildElement("Name");
	if(pNode)
	{
		person->m_sName = pNode->GetText();		
	}

	pNode = pRootElement->FirstChildElement("NickName");
	if(pNode)
	{
		person->m_sNickName = pNode->GetText();		
	}

	pNode = pRootElement->FirstChildElement("Age");
	if(pNode)
	{
		person->m_nAge = atoi(pNode->GetText());		
	}
}

int main(int argc, _TCHAR* argv[])
{
	string file = "Person.xml";

	//Person Larry;
	/*Larry.m_sName		= "Larry";
	Larry.m_sNickName	= "ø‰∆n";
	Larry.m_nAge		= 30;*/
	
	//SaveXml(&Larry, file);


	Person NewLarry;

	LoadXml(file, &NewLarry);

	printf("Name: %s\r\n", NewLarry.m_sName.c_str());
	printf("NickName: %s\r\n", NewLarry.m_sNickName.c_str());
	printf("Age: %d\r\n", NewLarry.m_nAge);
return 0;
 }  
	
