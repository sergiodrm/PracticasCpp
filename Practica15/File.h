#pragma once
#include "Stream.h"


class CFile : public CStream
{
public:

  CFile();
  ~CFile() override;

  void Open(const char* _sStreamName) override;
  void Read() override;
  void Write() override;
  void Close() override;



};

