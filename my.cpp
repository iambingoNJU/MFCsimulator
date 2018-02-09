#include "my.h"

// Global object
CMyWinApp theApp;

IMPLEMENT_DYNAMIC(CMyWinApp, CWinApp)
IMPLEMENT_DYNAMIC(CMyFrameWnd, CFrameWnd)

BOOL CMyWinApp::InitInstance() {
	cout << "CMyWinApp::InitInstance\n";
	m_pMainWnd = new CMyFrameWnd;
	return TRUE;
}

void PrintAllClasses() {
	CRuntimeClass *pClass;
	for(pClass = CRuntimeClass::pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass) {
		cout << pClass->m_lpszClassName << endl;
		cout << pClass->m_nObjectSize << endl;
		cout << pClass->m_wSchema << endl;
	}
}

//-------------------------------------------
// main
//-------------------------------------------
int main() {
	CWinApp* pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	// PrintAllClasses();

	CView* pView = new CView();
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CWinApp)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CView)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CCmdTarget)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CObject)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CDocument)) << endl;
	cout << "Result: " << pView->IsKindOf(RUNTIME_CLASS(CMyFrameWnd)) << endl;

	return 0;
}
