
// max001View.cpp: Cmax001View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "max001.h"
#endif

#include "max001Doc.h"
#include "max001View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmax001View

IMPLEMENT_DYNCREATE(Cmax001View, CView)

BEGIN_MESSAGE_MAP(Cmax001View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &Cmax001View::FindMax)
	ON_MESSAGE(WM_MIN, &Cmax001View::OnMinFound)
END_MESSAGE_MAP()

// Cmax001View 생성/소멸

Cmax001View::Cmax001View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cmax001View::~Cmax001View()
{
}

BOOL Cmax001View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cmax001View 그리기

void Cmax001View::OnDraw(CDC* pDC)
{
	Cmax001Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(10, 10, pDoc->str);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// Cmax001View 인쇄

BOOL Cmax001View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cmax001View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cmax001View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cmax001View 진단

#ifdef _DEBUG
void Cmax001View::AssertValid() const
{
	CView::AssertValid();
}

void Cmax001View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmax001Doc* Cmax001View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmax001Doc)));
	return (Cmax001Doc*)m_pDocument;
}
#endif //_DEBUG

UINT LThread(LPVOID pParam);
UINT LThread(LPVOID pParam) {
	SData* pData = (SData*)pParam;

	::PostMessage(pData->NotifyWindow, WM_MIN, 0, 0);

	return 0;

}

// Cmax001View 메시지 처리기


void Cmax001View::FindMax()
{
	data.arr[0] = 11;
	data.arr[1] = 24;
	data.arr[2] = 96;
	data.arr[3] = 123;
	data.arr[4] = 7;
	data.arr[5] = 64;
	data.arr[6] = 92;
	data.arr[7] = 22;
	data.arr[8] = 173;
	data.arr[9] = 5;
	data.min = INT_MAX;
	data.NotifyWindow = m_hWnd;
	AfxBeginThread(LThread, &data);

	for (int i = 0; i < 10; i++) {
		if (data.min > data.arr[i]) {
			data.min = data.arr[i];
		}
	}
	
	//MessageBox(_T("Sample Text"), _T("Title"), MB_YESNOCANCEL);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


LRESULT Cmax001View::OnMinFound(WPARAM wParam, LPARAM lParam) {
	Cmax001Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString msg;
	msg.Format(L"Minimum number: %d", data.min);
	pDoc->str = msg;
	TerminateThread(Thread, 0);
	Invalidate();
	return 0L;
}