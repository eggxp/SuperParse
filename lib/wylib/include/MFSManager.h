//---------------------------------------------------------------------------
#ifndef MFSManagerH
#define MFSManagerH

// bugfix 2006-06-15 δ���� ѹ������ļ� CompressedOfSize �� δѹ���� FileSizeLow ���󣬷�������Խ��
// 1029��:
// ԭʼ:        pMfsHandle->lpData = new BYTE[pMfsHandle->iSizeOfData];
//
// �޸�:        pMfsHandle->lpData = new BYTE[pMfsHandle->iSizeOfData < iCompressedOfSize ? iCompressedOfSize : pMfsHandle->iSizeOfData];

#include <windows.h>
#include "itemplat.h"                         // ͨ�ö�̬����ģ��
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a1			      // ���뷽ʽΪ1�ֽ�
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack(1)				      // ���뷽ʽΪ1�ֽ�
#endif //__MSC_VER
/****************************************************************************
 * MFS�ļ���ʽʾ��ͼ
 * +------------------+
 * |    �ļ�ͷ(255)   |
 * +------------------+
 * |   ����Ŀ¼�б�   |
 * |���и����ݰ�������|
 * |��Ϣ,�Լ�λ��.    |
 * +------------------+
 * |�������ݰ���ŵ�λ|
 * |��.               |
 * +------------------+
 ***************************************************************************/
typedef struct tagMfsHeader                            // ��־ͷ
{
  DWORD                       Signature;               // ��־
  DWORD                       Numbering;               // ���
  DWORD                       OSVersion;               // �汾
  DWORD                       Characteristics;         // ���ԣ����õļ����㷨������
  BYTE                        Copyright[64];           // ��Ȩ�������￪ʼ���ܼ�256�ֽ�
  DWORD                       SizeOfHeader;            // �ļ�ͷ��С(����Ŀ�б�)
  DWORD                       NumberOfDataDirectory;   // ����Ŀ�б���Ŀ(Ŀ¼�б���)
  DWORD                       PasswordOfAutoLock[4];   // �Զ����ܿ���(�ļ�����ʱ�����ֱ������,
                                                       // ��һ��������ļ����ļ���־ͷ������ø�
                                                       // ������ܣ����볤��128 Bit.)
  BYTE                        cReserved[168];          // ����Ϊ�Ժ�汾
}MFSHEADER, *PMFSHEADER;                               // ��С272�ֽ�

typedef struct tagMFSSectionHeader
{
  DWORD                       Size;                     // �����С,���ṹ�͸�������(������,�ļ���,����Ŀ¼,ѹ�����ݵ�)
  DWORD                       VersionOfSection;         // ����
  DWORD                       VersionOfCompressor;      // ѹ������İ汾
  char                        ItemName[64];             // ������
  char                        ImportDirectory[MAX_PATH];// ����Ŀ¼
  FILETIME                    CreationTime;             // ����ʱ��
  FILETIME                    LastWriteTime;            // ����޸�ʱ��
  FILETIME                    ImportTime;               // ����ʱ��
  DWORD                       FileSizeHigh;             // �ļ���С��λ
  DWORD                       FileSizeLow;              // �ļ���С��λ
  DWORD                       CompressedOfSize;         // ѹ������ļ���С
  DWORD                       PointerToCompressedData;  // ָ��ѹ���������
  DWORD                       CrcOfFile;                // ԭʼ�ļ���CRC (Cyclic Redundancy Check)
  DWORD                       SizeOfRemarks;            // ��ע�δ�С(0LΪ�ޱ�ע)
  DWORD                       PointerToRemarks;         // ָ��ע��
  BYTE                        cReserved[4];             // ����Ϊ����8�ı��������ܷ���
}MFSSECTIONHEADER, *PMFSSECTIONHEADER;                  // 392�ֽ�

typedef struct tagMFSDataDirectory
{
  char                        FileName[MAX_PATH];       // �ļ���
  PMFSSECTIONHEADER           DataOfCompressed;         // ָ��ѹ�����ݵ�ָ��
  DWORD                       CrcOfPassword;            // ����У������(0LΪ�޿���)
  DWORD                       Characteristics;          // ���־
  BYTE                        cReserved[8];             // ����Ϊ����8�ı��������ܷ���
}MFSDATADIRECTORY, *PMFSDATADIRECTORY;                  // 280�ֽ�

typedef struct tagMFSOperation
{
  struct tagMFSOperation     *pPrev;                    // ָ����һ���ָ��
  struct tagMFSOperation     *pNext;                    // ָ����һ���ָ��
  DWORD                       iOperationType;           // ����������
  char                        cFileName[MAX_PATH];      // �ļ���
  char                        cItemName[64];            // ������
  char                        cImportFileName[MAX_PATH];// ������ļ���
  DWORD                       iVersionOfCompressor;     // ѹ����ʽ
  DWORD                       iSizeOfData;              // ���ݵĴ�С
  LPBYTE                      lpData;                   // ����������
}MFS_OPERATION, *PMFS_OPERATION;

typedef struct tagMFSFileHandle
{
  DWORD                       iOffset;                  // ��ǰƫ��, ��ѹ��Only
  MFSSECTIONHEADER            mMFSSectionInfo;          // һЩ�ڵ���Ϣ
  DWORD                       iSizeOfData;              // ���ݵĴ�С, ��ѹ��Only
  LPBYTE                      lpData;                   // ����������
  BOOL                        bPassword;                // �Ƿ��м�����
  char                        cFileName[MAX_PATH];      // �ļ���
}MFSFILEHANDLE, *PMFSFILEHANDLE;

#define PACKAGE_MFS30_SIGNATURE               0x0000484C  // LH00(ѹ������־)
#define PACKAGE_MFS30_NUMBERING               0x20030107  // ���
#define PACKAGE_MFS30_OSVERSION               0x3373666D  // �汾 'mfs3'

// Encrypt Arithmetic
#define PACKAGE_MFS30_ENCRYPT_BASE            0x00000000  // �������㷨�����������㷨
#define PACKAGE_MFS30_ENCRYPT_DES             0x00000001  // �������㷨��des�㷨
#define PACKAGE_MFS30_ENCRYPT_BLOWFISH        0x00000002  // �������㷨��blowfish�㷨
#define PACKAGE_MFS30_ENCRYPT_IDEA            0x00000003  // �������㷨��idea�㷨
#define PACKAGE_MFS30_ENCRYPT_RSA             0x80000000  // �������㷨��rsa�㷨(�������Գ��㷨���)����֧��512, 1024, 2048bit Key

// Section Version
#define SECTION_VERSION_30                    0x00000030  // Ŀǰ�ڵ�汾Ϊ3.0

// Section Compressor Version
#define COMPRESSOR_VERSION_NONE               0x00000000  // ��ѹ��
#define COMPRESSOR_VERSION_ZLIB114            0x3431317A  // ѹ������汾 zlib 1.1.4

// Section Characteristics
#define SECTION_IS_NONE                       0x00000000  // ѹ������������
#define SECTION_IS_DATA                       0x00000001  // ѹ������������
#define SECTION_IS_REMARKS                    0x00000002  // ѹ�������б�ע����

// Dynamic Operation Characteristics
#define MFS_OPERATION_NONE                    0x00000000  // �޲���
#define MFS_OPERATION_ADD_FILE                0x00000001  // ���һ�����ļ����ļ���
#define MFS_OPERATION_DELETE_FILE             0x00000002  // ���ļ���ɾ��һ���ļ�
#define MFS_OPERATION_ADD_REMARK              0x00000003  // ���һ����ע���ļ���
#define MFS_OPERATION_DELETE_REMARK           0x00000004  // ɾ��һ����ע

// Error Result Value
#define MFS_NO_ERROR                          0x00000000  // �޴���
#define MFS_OPEN_FILE_FAIL                    0xC1010101  // ���ļ�ʧ��
#define MFS_MAPFILE_FAIL                      0xC1010102  // ӳ���ļ�ʧ��
#define MFS_INVALID_MFS_FILE                  0xC1010103  // mfs�ļ���ʽ��Ч
#define MFS_NEED_PRIVATE_KEY                  0xC1010104  // ��Ҫ˽��Key
#define MFS_NEED_PUBLIC_KEY                   0xC1010105  // ��Ҫ����Key
#define MFS_DECRYPT_FAIL                      0xC1010106  // ����ʧ��
#define MFS_ENCRYPT_FAIL                      0xC1010107  // ����ʧ��
#define MFS_OPERATION_ERROR                   0xC1010108  // һ������Դ���
#define MFS_CREATE_FILE_FAIL                  0xC1010109  // �����ļ�ʧ��
#define MFS_FATAL_ERROR                       0xC101010A  // ��������һ���ڴ����
#define MFS_FILE_EXISTS                       0xC101010B  // �ļ��Ѿ�����
#define MFS_INVAILD_PASSWORD                  0xC101010C  // ��Ч������
#define MFS_FILE_CRC_BAD                      0xC101010D  // �ļ�CRC����

// Version
#define MFS_VERSION                           ".mfs Manager v3.0"
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a.
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER
//---------------------------------------------------------------------------
enum TZCompressionLevel { zcNone, zcFastest, zcDefault, zcMax };
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
int _stdcall ZCompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, TZCompressionLevel level = zcDefault);
int _stdcall ZDecompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, int outEstimate);
void _stdcall ZFreeBuffer(LPVOID pBuffer);

extern DWORD dwZRandSeed;

void _stdcall ZRandomize(void);
DWORD _stdcall ZRandInt(DWORD i);
double ZRandExt(void);
double _stdcall ZRandG(double Mean, double StdDev);
int _stdcall ZGetRand(int x);
//---------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
class TMFSManager
{
private:
        HANDLE                          m_hMFSFile, m_hMFSMapFile;
        LPVOID                          m_pvBasePointer;
        MFSHEADER                       m_mMFSHeader;
        PMFSDATADIRECTORY               m_pMFSDataDirectory;
        IDataArray<MFSDATADIRECTORY>    m_aMFSDataDirectory;
        DWORD                           m_dwTotalOfOperation;
        PMFS_OPERATION                  m_pBaseOperation, m_pCurOperation;
        DWORD                           m_dwVersionOfCompressor;
        DWORD                           m_dwLastError;
        BOOL                            m_bModified;
        BOOL                            m_bValid;
        BOOL                            m_bNewFile;
        char                            m_cPassword[64];
        char                            m_cFilename[MAX_PATH];
        BOOL                            m_bPublicKey, m_bPrivateKey;
        BYTE                            m_cPublicKey[514];        // ����ר�ã�����Key
        BYTE                            m_cPrivateKey[1410];      // ר�����ڼ��ܣ�˽��Key
protected:
        VOID                    Init(VOID);
        VOID                    CreateMFSHeader(VOID);
        DWORD _stdcall          WriteMFSSectionData(HANDLE hFile, PMFSDATADIRECTORY pMFSDataDir);
        VOID _stdcall           AddOperation(PMFS_OPERATION pMFSOperation);
        VOID _stdcall           DeleteOperation(LPCSTR lpFilename);
        PMFS_OPERATION _stdcall IndexOfOperation(LPCSTR lpFilename);
        VOID                    ClearOperation(VOID);
        int _stdcall            IndexOf(LPCSTR lpFilename);
        VOID _stdcall           SaveFileName(LPCSTR lpFilename);
        static BOOL _stdcall    DecryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode);
        BOOL _stdcall           DecryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode);
        static BOOL _stdcall    EncryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode);
        BOOL _stdcall           EncryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode);
public:
        _stdcall                TMFSManager(LPSTR lpFilename = NULL, BOOL bCreated = FALSE);
                                ~TMFSManager();

        BOOL _stdcall           OpenMFSFile(LPSTR lpFilename, BOOL bCreated);
        BOOL                    Save();
        BOOL _stdcall           SaveAs(LPSTR lpNewFilename);
        BOOL                    Close();

        VOID _stdcall           SetVersionOfCompressor(DWORD iVersion);
        BOOL _stdcall           AddDirectory(LPCSTR lpDirectory, LPCSTR lpItemName);
        BOOL _stdcall           AddFile(LPCSTR lpImportFilename, LPCSTR lpItemName, LPCSTR lpFilename);
        BOOL _stdcall           AddRemark(LPCSTR lpFilename, LPVOID lpRemarks, DWORD iSizeOfRemarks);
        BOOL _stdcall           RemoveFile(LPCSTR lpFilename);

        HANDLE _stdcall         mfsOpenFile(LPSTR lpFilename, BOOL bPreRead);
        DWORD _stdcall          mfsSetFilePointer(HANDLE hFile, DWORD iDistanceToMove, DWORD dwMoveMethod); // ��ѹ����ʽOnly
        DWORD _stdcall          mfsReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
        DWORD _stdcall          mfsWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite); // ��ѹ����ʽOnly
        DWORD _stdcall          mfsGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
        BOOL _stdcall           mfsCloseFile(HANDLE hFile);
        DWORD _stdcall          mfsGetFileBuffer(HANDLE hFile, LPBYTE *lpData);

        BOOL _stdcall           mfsFileExists(LPCSTR lpFilename);
        BOOL                    mfsGetFileAttributes(LPCSTR lpFilename, PMFSSECTIONHEADER pmfsSectionHeader);

        VOID _stdcall           mfsSetLastError(DWORD iError);
        DWORD                   mfsGetLastError();

        int                     GetFileCount(VOID);
        PMFSDATADIRECTORY       GetDataDirectory(int Index);

        static DWORD _stdcall   GetCrc32(DWORD crc, LPBYTE buf, UINT len);
        BOOL                    IsValid(VOID);
        BOOL                    IsModified(VOID);
        VOID _stdcall           SetPasswordOfFile(LPCSTR lpPassword);
        VOID _stdcall           SetPrivateKeyOfFile(LPBYTE lpPrivateKey, DWORD iKeyLen);
        VOID _stdcall           SetPublicKeyOfFile(LPBYTE lpPublicKey, DWORD iKeyLen);
        VOID _stdcall           ClearPrivateKeyOfFile(VOID);
        VOID _stdcall           ClearPublicKeyOfFile(VOID);
        VOID _stdcall           SetEncryptModeOfFile(DWORD iMode);
        VOID _stdcall           SetCopyright(LPCSTR lpCopyright);
        LPSTR                   GetFilename(void);
        LPSTR                   GetVersionString();
};
//---------------------------------------------------------------------------
#endif
