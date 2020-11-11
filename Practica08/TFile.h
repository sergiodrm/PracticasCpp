#pragma once

struct _iobuf;
typedef _iobuf FILE;

namespace FileUtilities
{
  
  enum class EFilesModes
  {
    Invalid = -1,
    Read,
    Write,
    ReadWrite,
    Count
  };

  enum class EFilesErrors
  {
    Invalid = -1,
    Success,
    OpenModeNotValid,
    FileAlreadyOpen,
    FileNotOpen,
    InputNotValid,
    CodeEOF,
    OpenError,
    CloseError,
    WriteError,
    Count
  };

  const char* GetModeAsStr(EFilesModes _eMode);
  EFilesModes GetStrAsMode(const char* _sMode);
  void PrintFileError(EFilesErrors _eError);
  

  class TFile
  {
  public:

    TFile();
    explicit TFile(const char* _sFileName, EFilesModes _eOpenMode);
    explicit TFile(const TFile& _oTFile) noexcept;
    explicit TFile(TFile&& _oTFile) noexcept;
    ~TFile();

    void OpenFile();
    void CloseFile();
    int ReadFile(char* _sOutput_, unsigned int _uNum);
    int WriteFile(const char* _sString, unsigned int _uNum);

    const TFile& operator=(const TFile& _oTFile);
    const TFile& operator=(TFile&& _oTFile) noexcept;

    const char* GetFilename();
    EFilesErrors GetErrorFlag();
    EFilesModes GetOpenMode();
    bool GetEOF();

  private:

    FILE* m_pFid;
    EFilesModes m_eOpenMode;
    EFilesErrors m_eErrorFlag;
    char* m_sFileName;
    bool m_bEOF;
  };
}

