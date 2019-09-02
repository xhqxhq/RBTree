// RedBlackTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<time.h>
#include "RBTree.h"
//#include "Ohter.h"
int main()
{

  CRBTree<int> IntTree;
  /*
  IntTree.Insert(38);
  IntTree.Insert(31);
  IntTree.Insert(12);
  IntTree.Insert(19);
  IntTree.Insert(123);
  IntTree.Insert(324);
  IntTree.Insert(698);
  IntTree.Insert(780);
  IntTree.Insert(234);
  IntTree.Insert(888);
  IntTree.Insert(89);
  IntTree.Insert(85);
  IntTree.Insert(81);


  IntTree.Delete(123);
  IntTree.Delete(234);
  IntTree.Delete(12);
  IntTree.Delete(888);
  IntTree.Delete(19);
  IntTree.Delete(698);
  IntTree.Delete(81);
  IntTree.Delete(38);
  IntTree.Delete(31);
  IntTree.Delete(324);
  IntTree.Delete(780);
  IntTree.Delete(89);
  IntTree.Delete(85);
  */
  for (int iIndex = 0; iIndex < 1000; iIndex++)
  {
    IntTree.Insert(iIndex);
  }
  for (int iIndex = 0; iIndex < 1000; iIndex++)
  {
    IntTree.Delete(iIndex);
  }
  /*
  RBTree<int> IntTree;
  int Num = 38;
  IntTree.insert(Num);
  Num = 31;
  IntTree.insert(Num);
  Num = 12;
  IntTree.insert(Num);
  Num = 19;
  IntTree.insert(Num);
  Num = 123;
  IntTree.insert(Num);
  Num = 324;
  IntTree.insert(Num);
  Num = 698;
  IntTree.insert(Num);
  Num = 780;
  IntTree.insert(Num);
  Num = 234;
  IntTree.insert(Num);
  Num = 888;
  IntTree.insert(Num);
  Num = 89;
  IntTree.insert(Num);
  Num = 85;
  IntTree.insert(Num);
  Num = 81;
  IntTree.insert(Num);

  Num = 123;
  IntTree.remove(Num);
  Num = 234;
  IntTree.remove(Num);
  Num = 12;
  IntTree.remove(Num);
  Num = 888;
  IntTree.remove(Num);
  Num = 19;
  IntTree.remove(Num);
  Num = 698;
  IntTree.remove(Num);
  Num = 81;
  IntTree.remove(Num);
  Num = 38;
  IntTree.remove(Num);
  Num = 31;
  IntTree.remove(Num);
  Num = 324;
  IntTree.remove(Num);
  Num = 780;
  IntTree.remove(Num);
  Num = 89;
  IntTree.remove(Num);
  Num = 85;
  IntTree.remove(Num);
 */
  return 0;
}

