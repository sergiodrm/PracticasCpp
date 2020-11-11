
#include <iostream>

class CA
{
  CA() { printf("Constructor clase CA.\n") };
  ~CA() { printf("Destructor clase CA.\n") };
};

class CB : public CA
{
  CB() { printf("Constructor clase CB.\n") };
  ~CB() { printf("Destructor clase CB.\n") };
};

class CC : public CB
{
  CC() { printf("Constructor clase CC.\n") };
  ~CC() { printf("Destructor clase CC.\n") };
};


int main()
{
  {
    CA oA;
  }
  {
    CB oB;
  }
  {
    CC oC;
  }

  printf("\n\n\n");
  return 0;
}