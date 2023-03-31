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
  char* c3 = "Third";
  char* c4 = "Fourth";
  char* c5 = "Fith";
  char* c6 = "Sixth";
  char* c7 = "Seventh";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c4, &b);
  a.Add(&c5, &b);
  TTreeMap<char*, int> v(a);
  TTreeItem<char*, int> k(&b, &c6);
  TTreeItem<char*, int> k1(&b, &c7);
  k.SetRight(&k1);
  v.Add(&k);
  v.Delete(&c6);
  v.DeleteSubTree(&c3);
  return 0;
}