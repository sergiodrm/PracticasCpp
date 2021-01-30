#pragma once

#include <list>

// ***************************************************************************************
// VARIABLES GLOBALES
// ***************************************************************************************
constexpr  unsigned int MAX_X = 10;
constexpr unsigned int MAX_Y = 10;
constexpr unsigned int MIN_X = 0;
constexpr unsigned int MIN_Y = 0;
struct TEntity;
extern std::list<TEntity*> g_tEntities;


// ***************************************************************************************
// ENTIDAD
// ***************************************************************************************
typedef void (*funcEntity)(TEntity*);
struct TEntity
{

  int m_ix;
  int m_iy;
  int m_iHealth;
  funcEntity* m_funcs;
  TEntity(funcEntity* funcs, int x, int y);

  static TEntity* Create();
  static void Destroy(TEntity*& _pEntity_);
};

namespace Utils
{
  void ResolveCollisions(TEntity*);
  void CheckScreenLimits(int& _x_, int& _y_);
  int RandInRange(int _iMin, int _iMax);
  funcEntity GetRandomMovementFunction();
  funcEntity GetRandomDrawFunction();
}

namespace Movement
{
  void MoveRight(TEntity*);
  void MoveLeft(TEntity*);
  void MoveUp(TEntity*);
  void MoveDown(TEntity*);
  void MoveDiagonal(TEntity*);
}

namespace Draw
{
  void Draw_Internal(int _x, int _y, const char _cCharToDraw);
  void DrawAEntity(TEntity*);
  void DrawBEntity(TEntity*);
  void DrawCEntity(TEntity*);
  void DrawDEntity(TEntity*);
}