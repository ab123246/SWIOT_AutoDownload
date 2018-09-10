#include <iostream>
#include <windows.h>

class codecvt_char{
	public:
		wchar_t* ToWideChar(const char* pStr, int nCodePage);
		char* ToMultiByte(const wchar_t* pWStr, int nCodePage);
		char* CPTransform(const char* pStrSrc, int nCPSrc, int nCPTar);
		char* GB2312ToUTF8(const char* pStrGB2312);
		char* UTF8ToGB2312(const char* pStrUTF8);
		char* GB2312ToBIG5(const char* pStrBIG5);
		char* BIG5ToGB2312(const char* pStrBIG5);
		char* UTF8ToBIG5(const char* pStrUTF8);
		char* BIG5ToUTF8(const char* pStrBIG5);
};
