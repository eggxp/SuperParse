/*
ʹ��API HOOK�Դ���ҳ�������йҹ�,�Ա�֤BCB6�Ժ��C++ Builder�汾��DFM�����ļ��ؼ��ļ���->����ת������������

//����:������
//����������: 2004.12

ʹ�þ���:


*/

//---------------------------------------------------------------------------
#ifndef UnicodeSupportH
#define UnicodeSupportH
//---------------------------------------------------------------------------
typedef int (WINAPI *WIDECHARTOMULTIBYTE)(UINT CodePage, DWORD dwFlags,
                                          LPCWSTR lpWideCharStr, int cchWideChar,
                                          LPSTR lpMultiByteStr, int cchMultiByte,
                                          LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar);
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

bool InitSimplifiedChinese(void);
bool DeInitSimplifiedChinese(void);

#ifdef __cplusplus
}
#endif //__cplusplus
//---------------------------------------------------------------------------
#endif
