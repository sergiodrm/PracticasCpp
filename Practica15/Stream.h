#pragma once



class CStream
{
public:

  explicit CStream();
  explicit CStream(const CStream&);
  ~CStream();

  virtual void Open(const char* _sStreamName) = 0;
  virtual void Read() = 0;
  virtual void Write() = 0;
  virtual void Close() = 0;

private:

  void* m_pStreamId;

};

