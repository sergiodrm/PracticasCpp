#pragma once
#include "RenderableObject.h"
#include <iostream>

class CMesh : public IRenderableObject
{
public:

  CMesh() : m_iMeshId(m_iCounter)
  {
    printf("Creando mesh %d\n", m_iCounter);
    m_iCounter++;
  }
  ~CMesh()
  {
    printf("Eliminando mesh %d\n", m_iMeshId);
    --m_iCounter;
  }

  virtual void Render() const override
  {
    // Implementacion del metodo heredado de la interfaz
    printf("Renderizando mesh %d\n", m_iMeshId);
  }

private:

  int m_iMeshId;
  static int m_iCounter;

};



