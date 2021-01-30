
#include "Funcs.h"
#include <queue>
#include <ctime>
#include "consola.h"

std::list<TEntity*> g_tEntities;

// ***************************************************************************************
// MAIN
// ***************************************************************************************

int main(int argc, char* argv[])
{
  srand(static_cast<unsigned int>(time(nullptr)));

	// Bucle de juego
	while (true)
	{
    // Limpiar la pantalla antes de escribir
		clear();

    // Cola de entidades para borrar tras recorrer toda la lista
    std::queue<TEntity*> tDeletedEntitiesQueue;
    // Bucle para recorrer la tabla de entidades creada
		for (TEntity* pIterator : g_tEntities)
		{
      // Comprobar que la entidad haya sido inicializada
      if (pIterator != nullptr)
      {
        if (pIterator->m_iHealth != 0)
        {
          // Coger las funciones guardadas de la entidad
          funcEntity pColl = pIterator->m_funcs[0];
          funcEntity pDraw = pIterator->m_funcs[1];
          funcEntity pMove = pIterator->m_funcs[2];

          // Invocar a las funciones
          pColl(pIterator);
          pDraw(pIterator);
          pMove(pIterator);
        }
        else
        {
          // No borrar las entidades mientras se recorre la lista!
          // Guardarlas a parte y borrarlas luego.
          tDeletedEntitiesQueue.push(pIterator);
        }
      } // else Mensaje warning de no inicializacion
		}

    // Borrar las entidades eliminadas durante el bucle
    while (!tDeletedEntitiesQueue.empty())
    {
      g_tEntities.remove(tDeletedEntitiesQueue.front());
      TEntity::Destroy(tDeletedEntitiesQueue.front());
      tDeletedEntitiesQueue.pop();
    }

    // Chequear el numero de entidades en juego
    if (g_tEntities.size() < 5)
    {
      /*int x = Utils::RandInRange(MIN_X, MAX_X);
      int y = Utils::RandInRange(MIN_Y, MAX_Y);
      funcEntity pFunctions[] = { &Utils::ResolveCollisions, Utils::GetRandomMovementFunction(), Utils::GetRandomDrawFunction() };
      TEntity* pEntity = new TEntity(pFunctions, x, y);
      */
      g_tEntities.push_back(TEntity::Create());
    }

    Sleep(100); // Sleep ms
	}

  // Habria que borrar los news restantes en la lista, pero al ser bucle infinito... @todo
}

