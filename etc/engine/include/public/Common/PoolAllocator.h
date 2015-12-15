////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


struct PoolInfo {
  PoolInfo() : m_pInfo(0) {}
  char * m_pInfo;
  int m_iCount;

  void Init(int count) {
    memset(m_pInfo, ~0, GetInfoSize(count));
    m_iCount = count;
  }

	int GetNextBusyPosition(int startpos, int count) const {
		if (true) {
			int startBitCount = startpos % 8;
			int startBit = 0;
			for (int i =0 ; i < startBitCount; ++i)
				startBit |= 1 << i;
			
			startBit = ~startBit;
			for (int i  = startpos / 8, end = GetInfoSize(count); i < end; ++i) {
				DWORD index;
				DWORD val = (~m_pInfo[i]) & startBit;
				startBit = -1;
				if (_BitScanForward(&index, val))  {
					int newPos = index + i * 8;
					if (newPos < count)
						return newPos;
					else
						break;
				}
			}
		}
		return -1;

	}

  int GetFreePosition(int count) const {

    if (m_iCount > 0) {
      for (int i =0, end = GetInfoSize(count); i < end; ++i) {
        DWORD index;
        DWORD val = m_pInfo[i];
        if (_BitScanForward(&index, val))  {
          int newPos = index + i * 8;
          if (newPos < count)
            return newPos;
          else
            break;
        }
      }
    }
    return -1;
  }

  void SetPositionAsBusy(int pos) {
    m_iCount--;
    int num = pos / 8;
    int bit = pos % 8;

    //assert((m_pInfo[num] & ~(1 << bit)));
    m_pInfo[num] &= ~(1 << bit);

  }

  void SetPositionAsFree(int pos) {
    m_iCount++;
    int num = pos / 8;
    int bit = pos % 8;
    //assert(!(m_pInfo[num] & (1 << bit)));
    m_pInfo[num] |= 1 << bit;
  }

  size_t GetInfoSize(int count) const{
    return (count / 8) + 1;
  }

};

template<class A, int N >
class CPool
{
public:
  CPool() : m_pPrev(0), m_pNext(0), m_pData(0) {}

	void DumpAliveObjects()
	{

		int start = -1; 

		while(true)
		{
			start = m_Info.GetNextBusyPosition(start+1, m_iCount);

			if (start != -1) {
				A* ptr = (A*)((A*)m_pData + start);
        (void)ptr;
				//ptr->DumpAliveObject();
			}
		}
	}

  A * GetPointer() {
    int pos = m_Info.GetFreePosition(m_iCount);
    if (pos != -1) {
      m_Info.SetPositionAsBusy(pos);
      return (A*)((A*)m_pData + pos);
    }

    return 0;
  }

  bool RemovePointer(A * p) {
    if ((char*)p >= m_pData && (char*)p < m_pData + m_iCount * sizeof(A)) {
      int pos = ((char*)p - m_pData)/sizeof(A);
      m_Info.SetPositionAsFree(pos);
      return true;
    }

    return false;
  }

  void Init(CPool * prev, CPool * next, int count) {
    m_pPrev = prev;
    m_pNext = next;
    size_t align = GetMinimalAlignmentSize(count);
    m_pData = (char*)_aligned_malloc(sizeof(A) * count + align/*guard*/ +
      m_Info.GetInfoSize(count), N);
    m_iCount = count;
    m_Info.m_pInfo = m_pData + sizeof(A) * count + align;
    m_Info.Init(count);
#ifdef _DEBUG
    memset(m_pData + sizeof(A) * count, 0xDEADBEAF, align);
#endif
  }

  size_t GetMinimalAlignmentSize(int count) const
  {
    size_t actualSize = sizeof(A) * count;
    size_t delta = actualSize - N *(int)(actualSize / N);
    if (delta == 0)
      delta = N;

    return delta;
  }

  void Remove() {
    if (m_pPrev)
      m_pPrev->m_pNext = m_pNext;
    if (m_pNext)
      m_pNext->m_pPrev = m_pPrev;

    _aligned_free(m_pData);
  }

  /*private:*/
  CPool * m_pPrev;
  CPool * m_pNext;
  char * m_pData;
  int m_iCount;
  PoolInfo m_Info;
};

template<class A, int N>
class CPoolArray
{
private:
public:
  CPoolArray(int count) : m_pHead(0), m_iCount(count) {}

  ~CPoolArray(void) {}

	void DumpAliveObjects()
	{
		CPool<A,N> * p = m_pHead;

		while (p) {
			p->DumpAliveObjects();
			p = p->m_pNext;
		}
	}

  A * New() {
    if (!m_pHead) {
      m_pHead = new CPool<A, N>;
      m_pHead->Init(0, 0, m_iCount);
    }

		if (m_bDumpAliveObjects)
			DumpAliveObjects();

    CPool<A,N> * p = m_pHead;
    CPool<A,N> * pOld = 0;

    while (p) {
      A * po = p->GetPointer();
      if (po) {
        return ::new(po) A;
      } else {
        pOld = p;
        p = p->m_pNext;
      }
    }

    if (!p) {
      p = new CPool<A, N>;
      p->Init(pOld, 0, m_iCount);
      pOld->m_pNext = p;
    }

    A * po = p->GetPointer();
    if (po) {
      return ::new(po) A;
    }

    assert(0);
    return 0;
  } 

  void Delete(void * poi) {
    CPool<A,N> * p = m_pHead;

    while(p) {
      if (p->RemovePointer((A*)poi)) {
        ((A*)poi)->~A();
        return;
      }
      p = p->m_pNext;
    }

    assert(0);
  }

  void DeleteNoDestructor(void * poi) {
    CPool<A,N> * p = m_pHead;

    while(p) {
      if (p->RemovePointer((A*)poi)) {
        return;
      }
      p = p->m_pNext;
    }

    assert(0);
  }

private:
  CPool<A, N>* m_pHead;
  int m_iCount;
	bool static m_bDumpAliveObjects;
};

template <class A,int N> bool CPoolArray<A,N>::m_bDumpAliveObjects = false;