#include "mfc.h"

class CMyWinApp : public CWinApp {
	DECLARE_DYNAMIC(CMyWinApp)
public:
	CMyWinApp() { cout << "CMyWinApp Constructor \n"; }
	~CMyWinApp() { cout << "CMyWinApp Destructor \n"; }
	virtual BOOL InitInstance();
};


class CMyFrameWnd : public CFrameWnd {
	DECLARE_DYNAMIC(CMyFrameWnd)
public:
	CMyFrameWnd() { Create(); cout << "CMyFrameWnd Constructor \n"; }
	~CMyFrameWnd() { cout << "CMyFrameWnd Destructor \n"; }
};

// global function
void PrintAllClasses();
