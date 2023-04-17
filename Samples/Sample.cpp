#include <iostream>
#include "Tree.h"
#include "Monom.h"
#include "Map.h"
#include "AVLTree.h"
#include "HMap.h"

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

  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  char* c4 = "Fourth";
  char* c5 = "Fith";
  char* c6 = "Sixth";
  char* c7 = "Seventh";
  int b = 5, c = 90, d = 55;
  /*TTree<char*, int> a;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c4, &b);
  a.Add(&c5, &b);
  TTree<char*, int> v(a);
  TTreeItem<char*, int> k(&b, &c6);
  TTreeItem<char*, int> k1(&b, &c7);
  k.SetRight(&k1);
  v.Add(&k);
  a.Delete(&c1);
  a.DeleteSubTree(&c3);*/

  //TAVLTree<char*, int> a;

 /* THMap<char*, int> a;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c4, &b);
  a.Add(&c5, &b);
  a.Add(&c6, &b);
  a.Add(&c7, &b);
  a.Add(&c7, &c);
  a.Add(&c7, &d);
  THMap<char*, int> bruh(a);
  bruh.Delete(&c3);
  a.Find(&c7);
  a.Delete(&c5);
  a.Delete(&c7);*/
  return 0;
}