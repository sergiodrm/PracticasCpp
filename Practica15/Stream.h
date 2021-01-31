#pragma once



class CStream
{
protected:

  typedef CStream Super;

public:

  explicit CStream();
  virtual ~CStream();

  virtual void Open(const char* _sStreamName);
  virtual void Read();
  virtual void Write();
  virtual void Close();

private:

  void* m_pStreamId;

};

