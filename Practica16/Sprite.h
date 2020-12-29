#pragma once

#include "RenderableObject.h"
#include <iostream>

class CSprite : public IRenderableObject
{
public:

  CSprite() : m_iSpriteId(m_iCounter) 
  {
    printf("Creando sprite %d\n", m_iCounter);
    m_iCounter++;
  }

  ~CSprite() 
  { 
    printf("Eliminando sprite %d\n", m_iSpriteId);
    --m_iCounter;
  }

  virtual void Render() const override
  {
    // Implementacion del metodo heredado de la interfaz
    printf("Renderizando sprite %d\n", m_iSpriteId);
  }

private:

  int m_iSpriteId;
  static int m_iCounter;

};


