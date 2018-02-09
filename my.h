#include "mfc.h"
#include <cstring>

class CMyWinApp : public CWinApp {
public:
	CMyWinApp() { cout << "CMyWinApp Constructor \n"; }
	~CMyWinApp() { cout << "CMyWinApp Destructor \n"; }
	virtual BOOL InitInstance();
};


class CMyFrameWnd : public CFrameWnd {
	//DECLARE_DYNAMIC(CMyFrameWnd)
	DECLARE_DYNCREATE(CMyFrameWnd)
public:
	CMyFrameWnd() { Create(); cout << "CMyFrameWnd Constructor \n"; }
	~CMyFrameWnd() { cout << "CMyFrameWnd Destructor \n"; }

	void SayHello() { cout << "Hello CMyFrameWnd" << endl; }
};

// global function
void PrintAllClasses();
