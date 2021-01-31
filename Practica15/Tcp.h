#pragma once
#include "Stream.h"


class CTcp : public CStream
{
public:
  CTcp();
  ~CTcp() override;
  void Open(const char* _sStreamName) override;
  void Read() override;
  void Write() override;
  void Close() override;


};

