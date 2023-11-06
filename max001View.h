
// max001View.h: Cmax001View 클래스의 인터페이스
//

#pragma once

struct SData {
	int arr[10];
	int min;
	HWND NotifyWindow;
};

class Cmax001View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cmax001View() noexcept;
	DECLARE_DYNCREATE(Cmax001View)

// 특성입니다.
public:
	Cmax001Doc* GetDocument() const;

// 작업입니다.
public:
	

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~Cmax001View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void FindMax();
	SData data;
	CWinThread* Thread;
	LRESULT OnMinFound(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // max001View.cpp의 디버그 버전
inline Cmax001Doc* Cmax001View::GetDocument() const
   { return reinterpret_cast<Cmax001Doc*>(m_pDocument); }
#endif

