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
  struct tagRBNode<T> * m_pLeft;  //ָ������
  struct tagRBNode<T> * m_pRight; //ָ���Һ���
  struct tagRBNode<T> * m_pParent;//ָ�򸸽ڵ�
  RB_COLOR m_Color;                //�ڵ���ɫ
  T m_TDataElemet;                //������
  tagRBNode(T & data, RB_COLOR bRed = RED) :
    m_pParent(nullptr),
    m_pLeft(nullptr),
    m_pRight(nullptr),
    m_TDataElemet(data),
    m_Color(bRed)
  {

  }
};

/*����ģ��ڵ����ͱ���*/
template<typename T>
using RBNode = tagRBNode<T>;

/*����ģ��ڵ�ָ�����ͱ���*/
template<typename T>
using PRBNode = tagRBNode<T>*;



template<typename T>
class CRBTree
{
  PRBNode<T> m_Root; //ָ����ڵ�
  int m_nNumOfNode;  //��¼�ڵ����
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
// ��������: CRBTree<T>::Delete
// ����Ȩ��: public
// ��������: ɾ��һ���ڵ�Ԫ��Ϊdata�Ľڵ�
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     T &  data:�����ҵ�Ԫ��
// ע��:     1.data������һ����ֵ,����������֧����ֵ��Ϊ����ʱ����
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
    /*������Ϊ����ֱ��ʹ���Һ������滻��ɾ���ڵ�*/
    pAdjust = pDelNode->m_pRight;
    pParentOfAdjust = pDelNode->m_pParent;
    ReplaceNode(pDelNode, pDelNode->m_pRight);
  }
  else if (pDelNode->m_pRight == nullptr)
  {
    /*������Ϊ����ʹ�ô�ɾ���ڵ��������滻��ɾ���ڵ�*/
    pAdjust = pDelNode->m_pLeft;
    pParentOfAdjust = pDelNode->m_pParent;
    ReplaceNode(pDelNode, pDelNode->m_pLeft);
  }
  else
  {
    /*��ɾ���ڵ����Һ��Ӷ����������������ѡ��һ���ڵ�ֵ��С�Ľڵ��������ɾ���ڵ�*/
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
      /*��С�ڵ㲻�Ǵ�ɾ���ڵ���Һ���,���Ƚ���С�ڵ��ԭ����λ����ժ����,��Сֵ�ڵ�������,�������Һ���,
        �����Һ��Ӻ��丸�ڵ��໥����*/
      ReplaceNode(pMinNode, pMinNode->m_pRight);
      pParentOfAdjust = pMinNode->m_pParent;
      /*����ɾ���ڵ���Һ�����Ϊ��С�ڵ���Һ���*/
      SET_RIGHT_CHILD(pMinNode, pDelNode->m_pRight);
      SET_PARENT(pMinNode, pMinNode->m_pRight);
    }
    
    /*����С�ڵ��滻��ɾ���ڵ�*/
    ReplaceNode(pDelNode, pMinNode);
    SET_COLOR(pMinNode, GET_COLOR(pDelNode));

    /*����ɾ���ڵ��������Ϊ��С�ڵ������*/
    SET_LEFT_CHILD(pMinNode, pDelNode->m_pLeft);
    SET_PARENT(pMinNode, pDelNode->m_pLeft);
  }

  
  if (ColorRecorder == BLACK)
  {
    /*��ɾ���Ľڵ��Ǻ�ɫ�Ļ����滻�ڵ�Ϊ��ɫʱ,����Ӱ��ڵ����ڵļ�·���Ϻڽڵ�ĸ���,����Ҫ����*/
    FixAfterDelete(pAdjust, pParentOfAdjust);
  }

  m_nNumOfNode--;
  delete pDelNode;
  return true;
}


/************************************************************************
// ��������: CRBTree<T>::Delete
// ����Ȩ��: public
// ��������: ɾ��һ���ڵ�Ԫ��Ϊdata�Ľڵ�
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     T & & data:�����ҵ�Ԫ��
// ע��:     1.data������һ����ֵ,����������֧����ֵ��Ϊ����ʱ����
************************************************************************/
template<typename T>
bool CRBTree<T>::Delete(T && data)
{
  return Delete(data);
}

/************************************************************************
// ��������: CRBTree<T>::FixAfterDelete
// ����Ȩ��: private
// ��������: ɾ���ڵ��,��pAdjustNodeָ��Ľڵ㿪ʼ���е���
// ����ֵ:   bool
// ����:     PRBNode<T> pAdjustNode:�������ڵ�λ��
// ����:     PRBNode<T> pParentOfAdjust:�������ڵ�ĸ��ڵ�
// ע��:
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
        /*Case1:�������ڵ���ֵܽڵ�Ϊ��ɫ,���ֵܽڵ���Ϊ��ɫ,�����ڵ���Ϊ��ɫ,���Ը��ڵ����һ������*/
        SET_BLACK_COLOR(pBrother);
        SET_RED_COLOR(pParent);
        LRotate(pParent);
        pBrother = pParent->m_pRight;
      }

      if ((pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft)) &&
          (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight)))
      {
        /*Case2:�������ڵ���ֵܽڵ�Ϊ��ɫ,���ֵܽڵ�����Һ��Ӷ��Ǻ�ɫ��(������Ҳ��Ϊ��ɫ),���ֵܽڵ�
                ��Ϊ��ɫ,�����丸�ڵ���Ϊ��һ�εĵ����ڵ�*/
        SET_RED_COLOR(pBrother);
        pAdjust = pParent;
        pParent = pAdjust->m_pParent;
      }
      else
      {
        /*��ʱ�ֵܽڵ�����ӱض����ڲ����Ǻ�ɫ��*/
        if (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight))
        {
          /*Case3:�ֵܽڵ��Ǻ�ɫ��,�ֵܽڵ�������Ǻ�ɫ,�ֵܽڵ���Һ����Ǻ�ɫ(������Ҳ��Ϊ��ɫ),
                  ���ֵܽڵ���Ϊ��ɫ,�ֵܽڵ��������Ϊ��ɫ,�����ֵܽڵ����һ������*/
          SET_RED_COLOR(pBrother);
          SET_BLACK_COLOR(pBrother->m_pLeft);
          RRotate(pBrother);
          pBrother = pParent->m_pRight;
        }
        
        /*Case4:��ʱ�ֵܽڵ���Һ��ӱض��Ǻ�ɫ��,���ӿ��п��޻�����ɫ����,�����ڵ����ɫ��ֵ���ֵܽڵ�
                �������ڵ���Ϊ��ɫ,�ڽ��ֵܽڵ���Һ��ӽڵ���Ϊ��ɫ,Ȼ��Ը��ڵ����һ������,����������
                �ڵ���Ϊ���ڵ�,���������*/
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
        /*Case1:�������ڵ���ֵܽڵ�Ϊ��ɫ,���ֵܽڵ���Ϊ��ɫ,�����ڵ���Ϊ��ɫ,���Ը��ڵ����һ������*/
        SET_BLACK_COLOR(pBrother);
        SET_RED_COLOR(pParent);
        LRotate(pParent);
        pBrother = pParent->m_pRight;
      }

      if ((pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft)) &&
          (pBrother->m_pRight == nullptr || IS_BLACK_COLOR(pBrother->m_pRight)))
      {
        /*Case2:�������ڵ���ֵܽڵ�Ϊ��ɫ,�ֵܽڵ�������ӽڵ�Ҳ�Ǻ�ɫ��,���ֵܽڵ���Ϊ��ɫ,
                �������ڵ���Ϊ��һ�εĵ����ڵ�*/
        SET_RED_COLOR(pBrother);
        pAdjust = pParent;
        pParent = pAdjust->m_pParent;
      }
      else
      {
        if (pBrother->m_pLeft == nullptr || IS_BLACK_COLOR(pBrother->m_pLeft))
        {
          /*Case3:�������ڵ���ֵܽڵ�Ϊ��ɫ,�ֵܵ����ӽڵ�Ϊ��ɫ,�Һ��ӽڵ�Ϊ��ɫ,���ֵܽڵ���Ϊ��ɫ,
                  ���ֵܽڵ���Һ�����Ϊ��ɫ,�����ֵܽ�������*/
          SET_RED_COLOR(pBrother);
          SET_BLACK_COLOR(pBrother->m_pRight);
          LRotate(pBrother);
          pBrother = pParent->m_pLeft;
        }

        /*Case3:��ʱ�������ڵ���ֵܽڵ��Ǻ�ɫ��,�ֵܽڵ�������Ǻ�ɫ��,�����ڵ����ɫ��ֵ���ֵܽڵ�,
                �������ڵ���Ϊ��ɫ,���ֵܽڵ��������Ϊ��ɫ,���Ը��ڵ����һ������,�����´ε����ڵ���
                Ϊ���ڵ�,���������*/
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
// ��������: CRBTree<T>::ReplaceNode
// ����Ȩ��: private
// ��������: ��pReplacerָ��Ľڵ��滻pBeReplacedָ��Ľڵ�
// ����ֵ:   bool
// ����:     PRBNode<T> pBeReplaced:���滻�Ľڵ�
// ����:     PRBNode<T> pReplacer�����滻�Ľڵ�
// ע��:     pBeReplaced����Ϊ��
************************************************************************/
bool CRBTree<T>::ReplaceNode(PRBNode<T> pBeReplaced, PRBNode<T> pReplacer)
{
  if (pBeReplaced == nullptr)
  {
    return false;
  }

  if (pBeReplaced == m_Root)
  {
    /*���ڵ㱻�滻*/
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
// ��������: CRBTree<T>::FindNodeByData
// ����Ȩ��: private
// ��������: ���������Ƿ����Ԫ��ֵΪdata�Ľڵ�
// ����ֵ:   ����ָ��ýڵ��ָ��,���û�иýڵ��򷵻ؿ�ָ��
// ����:     T & data:�����ҵ�Ԫ��
// ע��:
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
// ��������: CRBTree<T>::FixAfterInsert
// ����Ȩ��: private 
// ��������: �����½ڵ�������ά�����������
// ����ֵ:   bool
// ����:     PRBNode<T> pNewNode:�²���Ľڵ�
// ע��:     
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
        /*Case1:�������ڵ����ڵ�Ϊ��ɫ,��ô�游�ڵ�ض�ʱ��ɫ��,�򽫴������ڵ㸸�ڵ����ڵ���Ϊ
                ��Ϊ��ɫ,���游�ڵ���Ϊ��ɫ,�����������ڵ�����Ϊ�游�ڵ�
        */
        SET_BLACK_COLOR(pParent);
        SET_BLACK_COLOR(pUncle);
        SET_RED_COLOR(pGrand);
        pAdjust = pGrand;
        continue;
      }
      else
      {
        /*��ڵ��ʱһ���Ǻ�ɫ(������Ҳ��Ϊ��ɫ)*/
        if (!IS_LEFT_CHID(pParent, pAdjust))
        {
          /*case2:�������ڵ����丸�ڵ���Һ���,�����һ������,�����ô�����λ��*/
          pAdjust = pParent;
          LRotate(pParent);
          pParent = pAdjust->m_pParent;
        }

        /*Case3:��ʱ�������ڵ�Ϊ���ڵ������,���游�ڵ���Ϊ��ɫ,Ȼ����游�ڵ�ִ��һ������,�����ͽ�����*/
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
        /*Case1:��ڵ�Ϊ��ɫ*/
        SET_BLACK_COLOR(pUncle);
        SET_BLACK_COLOR(pParent);
        SET_RED_COLOR(pGrand);
        pAdjust = pGrand;
        continue;
      }
      else
      {
        /*��ʱ��ڵ�Ϊ��ɫ(������Ҳ��Ϊ��ɫ)*/
        if (IS_LEFT_CHID(pParent, pAdjust))
        {
          /*Case2:�������ڵ����丸�ڵ������,��Ը��ڵ��������*/
          pAdjust = pParent;
          RRotate(pParent);
          pParent = pAdjust->m_pParent;
        }

        /*Case3:��ʱ�������ڵ�Ϊ���ڵ���Һ���,�����ڵ���Ϊ��ɫ,�游�ڵ���Ϊ��ɫ,
                �ڶ��游�ڵ����һ���������ɽ�������*/
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
// ��������: CRBTree<T>::Insert
// ����Ȩ��: public 
// ��������: ����һ��ֵ
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     T & data:Ҫ�����ֵ
// ע��:     1.����Ĳ���data������һ����ֵ
            2.���data�Ѿ������򷵻�ʧ��
************************************************************************/
template<typename T>
bool CRBTree<T>::Insert(T & data)
{
  /*�Ȳ��Ҳ���λ��*/
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
      /*�������Ԫ���Ѿ�����*/
      return false;
    }
  }

  PRBNode<T> pNewNode = new RBNode<T>(data);
  if (pParentOfInsertLoc == nullptr)
  {
    /*��Ϊ��,��ֱ�Ӳ���*/
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
// ��������: CRBTree<T>::Insert
// ����Ȩ��: public 
// ��������: ����һ��ֵ
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     T & & data:�ڵ�ֵ
// ע��:     1.����Ĳ���data������һ����ֵ
            2.���data�Ѿ������򷵻�ʧ��
************************************************************************/
template<typename T>
bool CRBTree<T>::Insert(T && data)
{
  return Insert(data);
}


/************************************************************************
// ��������: CRBTree<T>::LRotate
// ����Ȩ��: private 
// ��������: ��һ�Խڵ��������
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     PRBNode<T> ParentOfPair:�������ĸ��ڵ�
// ע��:     ParentOfPair����Ҫ���Һ���
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
// ��������: CRBTree<T>::RRotate
// ����Ȩ��: private 
// ��������: ��һ�Խڵ��������
// ����ֵ:   bool:�ɹ�����true,ʧ�ܷ���false
// ����:     PRBNode<T> ParentOfPair:�������ĸ��ڵ�
// ע��:     ParentOfPair����Ҫ������
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