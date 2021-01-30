
#include "Funcs.h"
#include "consola.h"
#include <cstdio>


// ***************************************************************************************
// ENTIDAD
// ***************************************************************************************

TEntity::TEntity(funcEntity* funcs, int x, int y)
{
  m_ix = x;
  m_iy = y;
  m_funcs = funcs;
  m_iHealth = Utils::RandInRange(3, 6);
}

TEntity* TEntity::Create()
{
  int x = Utils::RandInRange(MIN_X, MAX_X);
  int y = Utils::RandInRange(MIN_Y, MAX_Y);
  TEntity* pEntity;
  {
    funcEntity* pFunctions = new funcEntity[3];
    pFunctions[0] = &Utils::ResolveCollisions;
    pFunctions[1] = Utils::GetRandomMovementFunction();
    pFunctions[2] = Utils::GetRandomDrawFunction();
    pEntity = new TEntity(pFunctions, x, y);
  }
  return pEntity;
}

void TEntity::Destroy(TEntity*& _pEntity_)
{
  if (_pEntity_ == nullptr)
    return;
  delete _pEntity_->m_funcs;
  delete _pEntity_;
  _pEntity_ = nullptr;
}

// ***************************************************************************************
// FUNCIONES UTILS
// *************************************************************************************** 

void Utils::CheckScreenLimits(int& _x_, int& _y_)
{
  auto VarInLimitsLambda = [](int& _iVar_, int _iMin, int _iMax)
  {
    while (_iVar_ < _iMin)
      _iVar_ += _iMax;
    if (_iVar_ > _iMax)
      _iVar_ %= _iMax;
  };

  // Check X
  VarInLimitsLambda(_x_, MIN_X, MAX_X);
  // Check Y
  VarInLimitsLambda(_y_, MIN_Y, MAX_Y);
}

int Utils::RandInRange(int _iMin, int _iMax)
{
  return (rand() % _iMax) + _iMin;
}

funcEntity Utils::GetRandomMovementFunction()
{
  int iRandom = RandInRange(0, 4);
  switch (iRandom)
  {
  case 0: return &Movement::MoveUp;
  case 1: return &Movement::MoveDown;
  case 2: return &Movement::MoveLeft;
  case 3: return &Movement::MoveRight;
  case 4: return &Movement::MoveDiagonal;
  }
}

funcEntity Utils::GetRandomDrawFunction()
{
  int iRandom = RandInRange(0, 3);
  switch (iRandom)
  {
  case 0: return &Draw::DrawAEntity;
  case 1: return &Draw::DrawBEntity;
  case 2: return &Draw::DrawCEntity;
  case 3: return &Draw::DrawDEntity;
  }
}

void Utils::ResolveCollisions(TEntity* _pEntity)
{
  if (_pEntity != nullptr && _pEntity->m_iHealth != 0)
  {
    for (TEntity* pIterator : g_tEntities)
    {
      if (pIterator != nullptr && pIterator != _pEntity && pIterator->m_iHealth != 0)
      {
        if (pIterator->m_ix == _pEntity->m_ix && pIterator->m_iy == _pEntity->m_iy)
        {
          pIterator->m_iHealth--;
          _pEntity->m_iHealth--;
        }
      }
    }
  }
}

// ***************************************************************************************
// FUNCIONES DE MOVIMIENTO
// *************************************************************************************** 

void Movement::MoveRight(TEntity* _pEntity)
{
  _pEntity->m_ix++;
  Utils::CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
}

void Movement::MoveLeft(TEntity* _pEntity)
{
  _pEntity->m_ix--;
  Utils::CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
}

void Movement::MoveDown(TEntity* _pEntity)
{
  _pEntity->m_iy++;
  Utils::CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
}

void Movement::MoveUp(TEntity* _pEntity)
{
  _pEntity->m_iy--;
  Utils::CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
}

void Movement::MoveDiagonal(TEntity* _pEntity)
{
  _pEntity->m_ix++;
  _pEntity->m_iy++;
  Utils::CheckScreenLimits(_pEntity->m_ix, _pEntity->m_iy);
}

// ***************************************************************************************
// FUNCIONES DE DIBUJO
// *************************************************************************************** 

void Draw::Draw_Internal(int _x, int _y, const char _cCharToDraw)
{
  gotoxy(_x, _y);
  printf("%c", _cCharToDraw);
}

void Draw::DrawAEntity(TEntity* _pEntity)
{
  Draw::Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'A');
}

void Draw::DrawBEntity(TEntity* _pEntity)
{
  Draw::Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'B');
}

void Draw::DrawCEntity(TEntity* _pEntity)
{
  Draw::Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'C');
}

void Draw::DrawDEntity(TEntity* _pEntity)
{
  Draw::Draw_Internal(_pEntity->m_ix, _pEntity->m_iy, 'D');
}

