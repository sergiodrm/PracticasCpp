
#include <iostream>

#include "List.h"
#include "Mesh.h"
#include "Sprite.h"
#include "RenderableObject.h"
#include <assert.h>

int main()
{
  constexpr int iArraySize = 5;
  CSprite tSprites[iArraySize];
  CMesh tMeshes[iArraySize];
  CList oRenderList;

  
  for (unsigned int uIndex = 0; uIndex < iArraySize; uIndex++)
  {
    oRenderList.Push(tSprites[uIndex]);
    oRenderList.Push(tMeshes[uIndex]);
  }

  for (unsigned int uIndex = 0; uIndex < static_cast<unsigned int>(oRenderList.Size()); uIndex++)
  {
    IRenderableObject* pCurrentRenderObject = oRenderList.Next();
    assert(pCurrentRenderObject != nullptr);
    pCurrentRenderObject->Render();
  }
  printf("\n\n");

  IRenderableObject* pRenderObject = oRenderList.First();
  assert(pRenderObject != nullptr);
  pRenderObject->Render();

  oRenderList.Pop();

  printf("\n\n");
  pRenderObject = oRenderList.First();
  assert(pRenderObject != nullptr);
  pRenderObject->Render();

  printf("\n\n");
  oRenderList.Reset();
  pRenderObject = oRenderList.Next();
  if (pRenderObject == nullptr)
  {
    printf("Lista vacia\n");
  }
  

  return 0;
}