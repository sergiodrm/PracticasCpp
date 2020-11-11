
#include <iostream>

/* Mascaras */
#define MASK_PLAYER_LIFE 0xFF000000
#define MASK_AMMO 0x00FF0000
#define MASK_PARTNERS 0x0000F000
#define MASK_BERSERKER 0x00000008
#define MASK_SHIELD 0x00000004
#define MASK_INFINITE_AMMO 0x00000002
#define MASK_INVULNERABLE 0x00000001


/* Formas de generar mascaras
#define MASK
const unsigned int uMask = 0xF000;
constexpr unsigned int s_uMask = 0xFF00
*/


// Declaracion de las funciones

// Devolver el numero de balas del jugador
unsigned int GetPlayerAmmo(unsigned int _iValue);

// Aniadir mas balas
// @return nuevo _uValue
unsigned int AddBullets(unsigned int _uValue, unsigned int _uBalas);

// @return modo balas
bool HasPlayerInfiniteBullets(unsigned int _uValue);

// Activar modo balas infinitas
unsigned int SetInfiniteBullets(unsigned int _uValue);


int main()
{
  /* 143 vida; 37 balas; 2 compis; Balas infinitas (0x8F252002)*/
  unsigned int uValue(0x8F252001);

  // Probar funcion de lectura de numero de balas
  printf("Ammo: %d\n", GetPlayerAmmo(uValue));

  // Sumar un numero de balas y comprobar la suma
  uValue = AddBullets(uValue, 200);
  printf("Ammo: %d\n", GetPlayerAmmo(uValue));

  // Tiene el player balas infinitas?
  if (HasPlayerInfiniteBullets(uValue))
  {
    printf("El jugador tiene balas infinitas!\n");
  } else printf("El jugador no tiene balas infinitas\n");

  // Activar el bit de balas infinitas
  uValue = SetInfiniteBullets(uValue);
  // Comprobar el bit de balas infinitas
  if (HasPlayerInfiniteBullets(uValue))
  {
    printf("El jugador tiene balas infinitas!\n");
  }
  else printf("El jugador no tiene balas infinitas\n");


  printf("\n\n\n\n\n\n");
  return 0;
}

// Definicion de las funciones

unsigned int GetPlayerAmmo(unsigned int _iValue)
{
  unsigned int uTemp = _iValue & MASK_AMMO;
  return uTemp >> 16;
}

unsigned int AddBullets(unsigned int _uValue, unsigned int _uBalas)
{
  // Obtener el numero de balas y sumarle la cantidad pedida
  unsigned int uNumBullets = GetPlayerAmmo(_uValue);
  uNumBullets += _uBalas;

  // Ojo! Trabajamos con 8 bits para el numero de balas
  // Hay que comprobar que el nuevo numero de balas no excede 255
  // Si excede -> devolver con el numero justo de balas
  // Si no excede -> introducir nuevo valor en el codigo binario
  if (uNumBullets > 255)
    uNumBullets = 255;
  

  // Desplazar el nuevo valor de balas a la posicion en la cadena
  unsigned int uBinNewNumBullets = uNumBullets << 16;
  unsigned int uValueWithoutBullets = _uValue & ~MASK_AMMO;

  return uValueWithoutBullets | uBinNewNumBullets;
}

bool HasPlayerInfiniteBullets(unsigned int _uValue)
{
  bool bInfiniteBullets = (_uValue & MASK_INFINITE_AMMO) != 0;
  return bInfiniteBullets;
}

unsigned int SetInfiniteBullets(unsigned int _uValue)
{
  return _uValue | MASK_INFINITE_AMMO;
}
