#include "mfc.h"
#include <cstring>

class CMyWinApp : public CWinApp {
public:
	CMyWinApp() { cout << "CMyWinApp Constructor \n"; }
	~CMyWinApp() { cout << "CMyWinApp Destructor \n"; }
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


class CMyFrameWnd : public CFrameWnd {
	//DECLARE_DYNAMIC(CMyFrameWnd)
	DECLARE_DYNCREATE(CMyFrameWnd)
public:
	CMyFrameWnd() { Create(); cout << "CMyFrameWnd Constructor \n"; }
	~CMyFrameWnd() { cout << "CMyFrameWnd Destructor \n"; }

	void SayHello() { cout << "Hello CMyFrameWnd" << endl; }

	DECLARE_MESSAGE_MAP()
};

class CMyDoc : public CDocument {
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc() { cout << "CMyDoc Constructor \n"; }
	~CMyDoc() { cout << "CMyDoc Destructor \n"; }

	DECLARE_MESSAGE_MAP()
};

class CMyView : public CView {
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView() { cout << "CMyView Constructor \n"; }
	~CMyView() { cout << "CMyView Destructor \n"; }

	DECLARE_MESSAGE_MAP()
};

// global function
void PrintAllClasses();
