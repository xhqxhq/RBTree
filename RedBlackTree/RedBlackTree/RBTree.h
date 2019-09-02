#pragma once
enum RB_COLOR
{
  RED,
  BLACK
};

#define IS_LEFT_CHID(parent,child) ((((parent)->m_pLeft) == (child)) ? true:false)
#define IS_EMPTY(pointer) (((pointer) == nullptr)?true:false)
#define SET_COLOR(pointer,color)                            \
do                                                          \
{                                                           \
  if ((pointer) != nullptr)                                 \
  {                                                         \
    (pointer)->m_Color = color;                             \
  }                                                         \
}                                                           \
while(0)

#define GET_COLOR(pointer)((pointer)->m_Color)

#define SET_RED_COLOR(pointer)                              \
do                                                          \
{                                                           \
  if((pointer) != nullptr)                                  \
  {                                                         \
    (pointer)->m_Color = RED;                               \
  }                                                         \
} while (0)   

#define SET_BLACK_COLOR(pointer)                            \
do                                                          \
{                                                           \
  if((pointer) != nullptr)                                  \
  {                                                         \
    (pointer)->m_Color = BLACK;                             \
  }                                                         \
} while (0)   

#define IS_RED_COLOR(pointer)     ((((pointer)->m_Color) == RED) ?true:false)
#define IS_BLACK_COLOR(pointer)   ((((pointer)->m_Color) == BLACK) ?true:false)


#define SET_PARENT(parent, child)                           \
if(child != nullptr)                                         \
{                                                           \
  child->m_pParent = parent;                                \
}                                                         


#define SET_LEFT_CHILD(parent,child)                        \
do                                                          \
{                                                           \
  parent->m_pLeft = child;                                  \
  SET_PARENT(parent,child)                                  \
}                                                           \
while(0)  


#define SET_RIGHT_CHILD(parent,child)                       \
do                                                          \
{                                                           \
  parent->m_pRight = child;                                 \
  SET_PARENT(parent,child)                                  \
}                                                           \
while(0)

#define LINK_GRANDFATHER_GRANDSON(parent,grandson)          \
do                                                          \
{                                                           \
  if(parent->m_pParent == nullptr)                            \
  {                                                           \
    m_Root = grandson;                                        \
  }else if (parent->m_pParent->m_pLeft == parent)             \
  {                                                           \
    parent->m_pParent->m_pLeft = grandson;                    \
  }                                                           \
  else                                                        \
  {                                                           \
    parent->m_pParent->m_pRight = grandson;                   \
  }                                                           \
  grandson->m_pParent = parent->m_pParent;                    \
}while(0)


template<typename T>
struct tagRBNode
{
  struct tagRBNode<T> * m_pLeft;  //指向左孩子
  struct tagRBNode<T> * m_pRight; //指向右孩子
  struct tagRBNode<T> * m_pParent;//指向父节点
  RB_COLOR m_Color;                //节点颜色
  T m_TDataElemet;                //数据域
  tagRBNode(T & data, RB_COLOR bRed = RED) :
    m_pParent(nullptr),
    m_pLeft(nullptr),
    m_pRight(nullptr),
    m_TDataElemet(data),
    m_Color(bRed)
  {

  }
};

/*定义模版节点类型别名*/
template<typename T>
using RBNode = tagRBNode<T>;

/*定义模版节点指针类型别名*/
template<typename T>
using PRBNode = tagRBNode<T>*;



template<typename T>
class CRBTree
{
  PRBNode<T> m_Root; //指向根节点
  int m_nNumOfNode;  //记录节点个数
public:
  CRBTree();
  bool Insert(T && data);
  bool Insert(T & data);
  bool Delete(T && data);
  bool Delete(T & data);
private:
  bool LRotate(PRBNode<T> ParentOfPair);
  bool RRotate(PRBNode<T> ParentOfPair);
  bool FixAfterInsert(PRBNode<T> pNewNode);
  PRBNode<T> FindNodeByData(T & data);
  bool ReplaceNode(PRBNode<T> pBeReplaced, PRBNode<T> pReplacer);
  bool FixAfterDelete(PRBNode<T> pAdjustNode, PRBNode<T> pParentOfAdjust);
};



template<typename T>
CRBTree<T>::CRBTree() :
  m_nNumOfNode(0),
  m_Root(nullptr)
{

}


/************************************************************************
// 函数名称: CRBTree<T>::Delete
// 访问权限: public
// 函数功能: 删除一个节点元素为data的节点
// 返回值:   bool:成功返回true,失败返回false
// 参数:     T &  data:待查找的元素
// 注意:     1.data必须是一个左值,本函数用于支持左值作为参数时调用
************************************************************************/
template<typename T>
bool CRBTree<T>::Delete(T & data)
{
  PRBNode<T> pDelNode = FindNodeByData(data);
  PRBNode<T> pParentOfAdjust = nullptr;
  PRBNode<T> pAdjust = nullptr;

  if (pDelNode == nullptr)
  {
    return false;
  }

  RB_COLOR ColorRecorder = GET_COLOR(pDelNode);

  if (pDelNode->m_pLeft == nullptr)
  {
    /*左子树为空则直接使用右孩子来替换待删除节点*/
    pAdjust = pDelNode->m_pRight;
    pParentOfAdjust = pDelNode->m_pParent;
    ReplaceNode(pDelNode, pDelNode->m_pRight);
  }
  else if (pDelNode->m_pRight == nullptr)
  {
    /*右子树为空则使用待删除节点左孩子来替换待删除节点*/
    pAdjust = pDelNode->m_pLeft;
    pParentOfAdjust = pDelNode->m_pParent;
    ReplaceNode(pDelNode, pDelNode->m_pLeft);
  }
  else
  {
    /*待删除节点左右孩子都存在则从右子树中选择一个节点值最小的节点来替代待删除节点*/
    PRBNode<T> pMinNode = pDelNode->m_pRight;
    while (pMinNode->m_pLeft != nullptr)
    {
      pMinNode = pMinNode->m_pLeft;
    }

    ColorRecorder = GET_COLOR(pMinNode);
    pAdjust = pMinNode->m_pRight;

    pParentOfAdjust = pMinNode;
    if (pMinNode != pDelNode->m_pRight)
    {
      /*最小节点不是待删除节点的右孩子,则先将最小节点从原来的位置上摘出来,最小值节点无左孩子,可能有右孩子,
        将其右孩子和其父节点相互链接*/
      ReplaceNode(pMinNode, pMinNode->m_pRight);
      pParentOfAdjust = pMinNode->m_pParent;
      /*将待删除节点的右孩子置为最小节点的右孩子*/
      SET_RIGHT_CHILD(pMinNode, pDelNode->m_pRight);
      SET_PARENT(pMinNode, pMinNode->m_pRight);
    }
    
    /*用最小节点替换待删除节点*/
    ReplaceNode(pDelNode, pMinNode);
    SET_COLOR(pMinNode, GET_COLOR(pDelNode));

    /*将待删除节点的左孩子置为最小节点的左孩子*/
    SET_LEFT_CHILD(pMinNode, pDelNode->m_pLeft);
    SET_PARENT(pMinNode, pDelNode->m_pLeft);
  }

  
  if (ColorRecorder == BLACK)
  {
    /*被删除的节点是黑色的或者替换节点为黑色时,都会影响节点所在的简单路径上黑节点的个数,所以要调整*/
    FixAfterDelete(pAdjust, pParentOfAdjust);
  }

  m_nNumOfNode--;
  delete pDelNode;
  return true;
}


/************************************************************************
// 函数名称: CRBTree<T>::Delete
// 访问权限: public
// 函数功能: 删除一个节点元素为data的节点
// 返回值:   bool:成功返回true,失败返回false
// 参数:     T & & data:待查找的元素
// 注意:     1.data必须是一个右值,本函数用于支持右值作为参数时调用
************************************************************************/
template<typename T>
bool CRBTree<T>::Delete(T && data)
{
  return Delete(data);
}

/************************************************************************
// 函数名称: CRBTree<T>::FixAfterDelete
// 访问权限: private
// 函数功能: 删除节点后,从pAdjustNode指向的节点开始进行调整
// 返回值:   bool
// 参数:     PRBNode<T> pAdjustNode:待调整节点位置
// 参数:     PRBNode<T> pParentOfAdjust:待调整节点的父节点
// 注意:
************************************************************************/
template<typename T>
bool CRBTree<T>::FixAfterDelete(PRBNode<T> pAdjustNode, PRBNode<T> pParentOfAdjust)
{
  PRBNode<T> pBrother = nullptr;
  PRBNode<T> pAdjust = pAdjustNode;
  PRBNode<T> pParent = pParentOfAdjust;
  while ((pAdjust == nullptr || IS_BLACK_COLOR(pAdjust)) && pAdjust != m_Root)
  {
    if (IS_LEFT_CHID(pParent,pAdjust))
    {
      pBrother = pParent->m_pRight;
      if(IS_RED_COLOR(pBrother))
      {
        /*Case1:待调整节点的兄弟节点为红色,将兄弟节点置为黑色,将父节点置为红色,并对父节点进行一次左旋*/
        SET_BLACK_COLOR(pBrother);
        SET_RED_COLOR(pParent);
        LRotate(pParent);
        pBrother = pParent->m_pRight;
      }

      if ((pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft)) &&
          (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight)))
      {
        /*Case2:待调整节点的兄弟节点为黑色,且兄弟节点的左右孩子都是黑色的(不存在也视为黑色),则将兄弟节点
                置为红色,并将其父节点置为下一次的调整节点*/
        SET_RED_COLOR(pBrother);
        pAdjust = pParent;
        pParent = pAdjust->m_pParent;
      }
      else
      {
        /*此时兄弟节点的左孩子必定存在并且是红色的*/
        if (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight))
        {
          /*Case3:兄弟节点是黑色的,兄弟节点的左孩子是红色,兄弟节点的右孩子是黑色(不存在也视为黑色),
                  将兄弟节点置为红色,兄弟节点的左孩子置为黑色,并对兄弟节点进行一次右旋*/
          SET_RED_COLOR(pBrother);
          SET_BLACK_COLOR(pBrother->m_pLeft);
          RRotate(pBrother);
          pBrother = pParent->m_pRight;
        }
        
        /*Case4:此时兄弟节点的右孩子必定是红色的,左孩子可有可无或者颜色任意,将父节点的颜色赋值给兄弟节点
                并将父节点置为黑色,在将兄弟节点的右孩子节点置为黑色,然后对父节点进行一次左旋,并将待调整
                节点置为根节点,则调整结束*/
        SET_COLOR(pBrother, GET_COLOR(pParent));
        SET_BLACK_COLOR(pParent);
        SET_BLACK_COLOR(pBrother->m_pRight);
        LRotate(pParent);
        pAdjust = m_Root;
      }
    }
    else
    {
      pBrother = pParent->m_pLeft;
      if (IS_RED_COLOR(pBrother))
      {
        /*Case1:待调整节点的兄弟节点为红色,将兄弟节点置为黑色,将父节点置为红色,并对父节点进行一次左旋*/
        SET_BLACK_COLOR(pBrother);
        SET_RED_COLOR(pParent);
        LRotate(pParent);
        pBrother = pParent->m_pRight;
      }

      if ((pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft)) &&
          (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight)))
      {
        /*Case2:待调整节点的兄弟节点为黑色,兄弟节点的两个子节点也是黑色的,则将兄弟节点置为红色,
                并将父节点置为下一次的调整节点*/
        SET_RED_COLOR(pBrother);
        pAdjust = pParent;
        pParent = pAdjust->m_pParent;
      }
      else
      {
        if (pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft))
        {
          /*Case3:待调整节点的兄弟节点为黑色,兄弟的左孩子节点为黑色,右孩子节点为红色,则将兄弟节点置为红色,
                  将兄弟节点的右孩子置为黑色,并对兄弟进行左旋*/
          SET_RED_COLOR(pBrother);
          SET_BLACK_COLOR(pBrother->m_pRight);
          LRotate(pBrother);
          pBrother = pParent->m_pLeft;
        }

        /*Case3:此时待调整节点的兄弟节点是黑色的,兄弟节点的左孩子是红色的,将父节点的颜色赋值给兄弟节点,
                并将父节点置为黑色,将兄弟节点的左孩子置为黑色,并对父节点进行一次右旋,并将下次调整节点置
                为根节点,则调整结束*/
        SET_COLOR(pBrother, GET_COLOR(pParent));
        SET_BLACK_COLOR(pBrother->m_pLeft);
        SET_BLACK_COLOR(pParent);
        RRotate(pParent);
        pAdjust = m_Root;
      }
    }
  }

  SET_BLACK_COLOR(pAdjust);
  return true;
}


template<typename T>
/************************************************************************
// 函数名称: CRBTree<T>::ReplaceNode
// 访问权限: private
// 函数功能: 用pReplacer指向的节点替换pBeReplaced指向的节点
// 返回值:   bool
// 参数:     PRBNode<T> pBeReplaced:待替换的节点
// 参数:     PRBNode<T> pReplacer用于替换的节点
// 注意:     pBeReplaced不能为空
************************************************************************/
bool CRBTree<T>::ReplaceNode(PRBNode<T> pBeReplaced, PRBNode<T> pReplacer)
{
  if (pBeReplaced == nullptr)
  {
    return false;
  }

  if (pBeReplaced == m_Root)
  {
    /*根节点被替换*/
    m_Root = pReplacer;
    SET_PARENT(nullptr, pReplacer);
  }
  else if (IS_LEFT_CHID(pBeReplaced->m_pParent, pBeReplaced))
  {
    SET_LEFT_CHILD(pBeReplaced->m_pParent, pReplacer);
  }
  else
  {
    SET_RIGHT_CHILD(pBeReplaced->m_pParent, pReplacer);
  }
  return true;
}



/************************************************************************
// 函数名称: CRBTree<T>::FindNodeByData
// 访问权限: private
// 函数功能: 查找树中是否存在元素值为data的节点
// 返回值:   返回指向该节点的指针,如果没有该节点则返回空指针
// 参数:     T & data:待查找的元素
// 注意:
************************************************************************/
template<typename T>
PRBNode<T> CRBTree<T>::FindNodeByData(T & data)
{
  PRBNode<T> pSearch = m_Root;
  while (pSearch != nullptr)
  {
    if (data > pSearch->m_TDataElemet)
    {
      pSearch = pSearch->m_pRight;
    }
    else if (data < pSearch->m_TDataElemet)
    {
      pSearch = pSearch->m_pLeft;
    }
    else
    {
      break;
    }
  }
  return pSearch;
}


/************************************************************************
// 函数名称: CRBTree<T>::FixAfterInsert
// 访问权限: private 
// 函数功能: 插入新节点后调整以维护红黑树性质
// 返回值:   bool
// 参数:     PRBNode<T> pNewNode:新插入的节点
// 注意:     
************************************************************************/
template<typename T>
bool CRBTree<T>::FixAfterInsert(PRBNode<T> pNewNode)
{
  PRBNode<T> pParent = nullptr;
  PRBNode<T> pUncle = nullptr;
  PRBNode<T> pGrand = nullptr;
  PRBNode<T> pAdjust = pNewNode;
  while ((pParent = pAdjust->m_pParent) && IS_RED_COLOR(pParent))
  {
    pGrand = pParent->m_pParent;
    if (IS_LEFT_CHID(pGrand, pParent))
    {
      pUncle = pGrand->m_pRight;
      if (pUncle != nullptr && IS_RED_COLOR(pUncle))
      {
        /*Case1:待调整节点的叔节点为红色,那么祖父节点必定时黑色的,则将待调整节点父节点和叔节点置为
                置为黑色,将祖父节点置为红色,并将待调整节点设置为祖父节点
        */
        SET_BLACK_COLOR(pParent);
        SET_BLACK_COLOR(pUncle);
        SET_RED_COLOR(pGrand);
        pAdjust = pGrand;
        continue;
      }
      else
      {
        /*叔节点此时一定是黑色(不存在也视为黑色)*/
        if (!IS_LEFT_CHID(pParent, pAdjust))
        {
          /*case2:待调整节点是其父节点的右孩子,则进行一次左旋,并重置待调整位置*/
          pAdjust = pParent;
          LRotate(pParent);
          pParent = pAdjust->m_pParent;
        }

        /*Case3:此时待调整节点为父节点的左孩子,将祖父节点置为红色,然后对祖父节点执行一次右旋,调整就结束了*/
        SET_BLACK_COLOR(pParent);
        SET_RED_COLOR(pGrand);
        RRotate(pGrand);
      }
    }
    else
    {
      pUncle = pGrand->m_pLeft;
      if (pUncle != nullptr && IS_RED_COLOR(pUncle))
      {
        /*Case1:叔节点为红色*/
        SET_BLACK_COLOR(pUncle);
        SET_BLACK_COLOR(pParent);
        SET_RED_COLOR(pGrand);
        pAdjust = pGrand;
        continue;
      }
      else
      {
        /*此时叔节点为黑色(不存在也视为黑色)*/
        if (IS_LEFT_CHID(pParent, pAdjust))
        {
          /*Case2:待调整节点是其父节点的左孩子,则对父节点进行右旋*/
          pAdjust = pParent;
          RRotate(pParent);
          pParent = pAdjust->m_pParent;
        }

        /*Case3:此时待调整节点为父节点的右孩子,将父节点置为黑色,祖父节点置为红色,
                在对祖父节点进行一次左旋即可结束调整*/
        SET_BLACK_COLOR(pParent);
        SET_RED_COLOR(pGrand);
        LRotate(pGrand);
      }
    }
  }
  SET_BLACK_COLOR(m_Root);
  return true;
}

/************************************************************************
// 函数名称: CRBTree<T>::Insert
// 访问权限: public 
// 函数功能: 插入一个值
// 返回值:   bool:成功返回true,失败返回false
// 参数:     T & data:要插入的值
// 注意:     1.传入的参数data必须是一个左值
            2.如果data已经存在则返回失败
************************************************************************/
template<typename T>
bool CRBTree<T>::Insert(T & data)
{
  /*先查找插入位置*/
  PRBNode<T> pParentOfInsertLoc = m_Root;
  PRBNode<T> pSearchLoc = m_Root;
  while (pSearchLoc != nullptr)
  {
    pParentOfInsertLoc = pSearchLoc;
    if (pSearchLoc->m_TDataElemet < data)
    {
      pSearchLoc = pSearchLoc->m_pRight;
    }
    else if (pSearchLoc->m_TDataElemet > data)
    {
      pSearchLoc = pSearchLoc->m_pLeft;
    }
    else
    {
      /*带插入的元素已经存在*/
      return false;
    }
  }

  PRBNode<T> pNewNode = new RBNode<T>(data);
  if (pParentOfInsertLoc == nullptr)
  {
    /*树为空,则直接插入*/
    m_Root = pNewNode;
  }
  else if(pParentOfInsertLoc->m_TDataElemet > data)
  {
    SET_LEFT_CHILD(pParentOfInsertLoc, pNewNode);
    SET_PARENT(pParentOfInsertLoc, pNewNode);
  }
  else
  {
    SET_RIGHT_CHILD(pParentOfInsertLoc, pNewNode);
    SET_PARENT(pParentOfInsertLoc, pNewNode);
  }

  m_nNumOfNode++;
  FixAfterInsert(pNewNode);
  return true;
}


/************************************************************************
// 函数名称: CRBTree<T>::Insert
// 访问权限: public 
// 函数功能: 插入一个值
// 返回值:   bool:成功返回true,失败返回false
// 参数:     T & & data:节点值
// 注意:     1.传入的参数data必须是一个右值
            2.如果data已经存在则返回失败
************************************************************************/
template<typename T>
bool CRBTree<T>::Insert(T && data)
{
  return Insert(data);
}


/************************************************************************
// 函数名称: CRBTree<T>::LRotate
// 访问权限: private 
// 函数功能: 对一对节点进行左旋
// 返回值:   bool:成功返回true,失败返回false
// 参数:     PRBNode<T> ParentOfPair:待左旋的父节点
// 注意:     ParentOfPair必须要有右孩子
************************************************************************/
template<typename T>
bool CRBTree<T>::LRotate(PRBNode<T> ParentOfPair)
{
  PRBNode<T>  pRChildOfParent = ParentOfPair->m_pRight;
  if (ParentOfPair == nullptr || pRChildOfParent == nullptr)
  {
    return false;
  }

  LINK_GRANDFATHER_GRANDSON(ParentOfPair, pRChildOfParent);

  SET_RIGHT_CHILD(ParentOfPair, pRChildOfParent->m_pLeft);
  SET_PARENT(ParentOfPair, pRChildOfParent->m_pLeft);

  SET_LEFT_CHILD(pRChildOfParent, ParentOfPair);
  SET_PARENT(pRChildOfParent, ParentOfPair);
  return true;
}


/************************************************************************
// 函数名称: CRBTree<T>::RRotate
// 访问权限: private 
// 函数功能: 对一对节点进行右旋
// 返回值:   bool:成功返回true,失败返回false
// 参数:     PRBNode<T> ParentOfPair:待右旋的父节点
// 注意:     ParentOfPair必须要有左孩子
************************************************************************/
template<typename T>
bool CRBTree<T>::RRotate(PRBNode<T> ParentOfPair)
{
  PRBNode<T> pLChildOfParent = ParentOfPair->m_pLeft;
  if (ParentOfPair == nullptr || pLChildOfParent == nullptr)
  {
    return false;
  }


  LINK_GRANDFATHER_GRANDSON(ParentOfPair, pLChildOfParent);

  SET_LEFT_CHILD(ParentOfPair, pLChildOfParent->m_pRight);
  SET_PARENT(ParentOfPair, pLChildOfParent->m_pRight);

  SET_RIGHT_CHILD(pLChildOfParent, ParentOfPair);
  SET_PARENT(pLChildOfParent, ParentOfPair);
  return true;
}