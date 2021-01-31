// practica4.cpp
//
#include <stdio.h>
#include "consola.h"

struct TEntity;
typedef void (*funcEntity)(TEntity *);


// ***************************************************************************************
// ENTIDAD
// ***************************************************************************************
struct TEntity
{
	int m_ix;
	int m_iy;
	funcEntity *m_funcs;
	TEntity(funcEntity *funcs, int x, int y)
	{
		m_ix = x;
		m_iy = y;
		m_funcs = funcs;
	}
};

// ***************************************************************************************
// FUNCIONES VARIAS
// *************************************************************************************** 

void CheckScreenLimits(int& _x_, int& _y_)
{
  const unsigned int MAX_X = 20;
  const unsigned int MAX_Y = 20;
  const unsigned int MIN_X = 0;
  const unsigned int MIN_Y = 0;

  // Check X
  while (_x_ < MIN_X) _x_ += MAX_X;

  if (_x_ > MAX_X)
  {
    _x_ %= MAX_X;
  }
  // Check Y
  while (_y_ < MIN_Y) _y_ += MAX_Y;

  if (_y_ > MAX_Y)
  {
    _y_ %= MAX_Y;
  }
}


// ***************************************************************************************
// FUNCIONES DE DIBUJO
// *************************************************************************************** 

void Draw_Internal(int _x, int _y, const char cCharToDraw)
{
  gotoxy(_x, _y);
  printf("%c", cCharToDraw);
}

void DrawAEntity(TEntity* _pEntity)
{
  CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
  Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'A');
}

void DrawBEntity(TEntity* _pEntity)
{
  CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
  Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'B');
}

void DrawCEntity(TEntity* _pEntity)
{
  CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
  Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'C');
}

void DrawDEntity(TEntity* _pEntity)
{
  CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
  Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'D');
}


// ***************************************************************************************
// FUNCIONES DE MOVIMIENTO
// *************************************************************************************** 

void MoveRight(TEntity* _pEntity)
{
  _pEntity->m_ix++;
}

void MoveLeft(TEntity* _pEntity)
{
  _pEntity->m_ix--;
}

void MoveDown(TEntity* _pEntity)
{
  _pEntity->m_iy++;
}

void MoveUp(TEntity* _pEntity)
{
  _pEntity->m_iy--;
}

void MoveDiagonal(TEntity* _pEntity)
{
  _pEntity->m_ix++;
  _pEntity->m_iy++;
}


// ***************************************************************************************
// MAIN
// ***************************************************************************************
unsigned int uKey;
int main()
{
  // Tabla de entidades y su longitud
  TEntity* tEntities[6] = { nullptr };
  const unsigned int uSizeTEntities = sizeof(tEntities) / sizeof(TEntity*);

	{
		// Inicializacion de entidades

    // Entidad 1: letra "A" que se mueve hacia la derecha.
    funcEntity tFunctionEntity1[] = { &DrawAEntity, &MoveRight };
    tEntities[0] = new TEntity(tFunctionEntity1, 0, 0);

    // Entidad 2: letra "A" que se mueve hacia arriba.
    funcEntity tFunctionEntity2[] = { &DrawAEntity, &MoveUp };
    tEntities[1] = new TEntity(tFunctionEntity2, 4, 2);

    // Entidad 3: letra "B" que se mueve en diagonal.
    funcEntity tFunctionEntity3[] = { &DrawBEntity, &MoveDiagonal };
    tEntities[2] = new TEntity(tFunctionEntity3, 2, 4);

    // Entidad 4: letra "B" que se mueve hacia arriba.
    funcEntity tFunctionEntity4[] = { &DrawBEntity, &MoveUp };
    tEntities[3] = new TEntity(tFunctionEntity4, 0, 0);

    // Entidad 5: letra "C" que se mueve hacia la izquierda.
    funcEntity tFunctionEntity5[] = { &DrawCEntity, &MoveLeft };
    tEntities[4] = new TEntity(tFunctionEntity5, 10, 6);

    // Entidad 6: letra "D" que se mueve hacia abajo.
    funcEntity tFunctionEntity6[] = { &DrawDEntity, &MoveDown };
    tEntities[5] = new TEntity(tFunctionEntity6, 3, 2);
	}
	
	// Bucle de juego
	while (true)
	{
    // Limpiar la pantalla antes de escribir
		clear();

    // Bucle para recorrer la tabla de entidades creada
		for (unsigned int uIndex = 0; uIndex < uSizeTEntities; uIndex++)
		{
      // Coger la entidad
      TEntity* tEntity = tEntities[uIndex];
      // Comprobar que la entidad haya sido inicializada
      if (tEntity)
      {
        // Coger las funciones guardadas de la entidad
        funcEntity pDraw = tEntity->m_funcs[0];
        funcEntity pMove = tEntity->m_funcs[1];

        // Invocar a las funciones
        pDraw(tEntity);
        pMove(tEntity);

      } // else Mensaje warning de no inicializacion
		}
    Sleep(100); // Sleep ms
	}
}

