#pragma once
#include "Stream.h"


class CCom : public CStream
{
public:
  CCom();
  ~CCom() override;

  void Open(const char* _sStreamName) override;
  void Read() override;
  void Write() override;
  void Close() override;


};

