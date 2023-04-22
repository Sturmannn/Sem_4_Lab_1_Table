#include <iostream>
#include "Tree.h"
#include "Monom.h"
#include "Map.h"
#include "AVLTree.h"
#include "HMap.h"
#include "RBTree.h"

int main()
{
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  char* c4 = "Fourth";
  char* c5 = "Fith";
  char* c6 = "Sixth";
  char* c7 = "Seventh";
  char* c8 = "Sea";
  char* c9 = "Seb";
  int b = 5, c = 90, d = 55;

  TAVLTree<char*, int> a;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c4, &b);
  a.Add(&c5, &b);
  a.Add(&c6, &b);
  a.Add(&c7, &b);
  a.Add(&c8, &b);
  a.Add(&c9, &b);

  a.Delete(&c5);
  a.DeleteSubTree(&c6);

  return 0;
}