#include <iostream>
#include "Tree.h"
#include "Monom.h"
#include "Map.h"

int main()
{
  /*TMonom a(3);
  a.SetK(5);
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  a.SetK(4.5);
  std::cout << a;
  TMap<char*, int> b(20);
  char* i = "First";
  int d = 5;
  b.Add(&i, &d);
  TTreeMap<char*, TMonom> c;
  c.Add(&i, &a);
  TTreeMap<char*, TMonom> v(c);
  v.Delete(&i);
  TMonom g = c.Find(&i);*/

  TTreeMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  TTreeMap<char*, int> v(a);
  v.Delete(&c2);
  return 0;
}