#include "test.h" 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE PrevhInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS WndClass;
	HWND hWnd;
	MSG Message;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE :
		if (!initSetting(hWnd))
		{
			MessageBox(hWnd, TEXT("초기화 중에 오류가 발생했습니다. \n"), TEXT("INIT_ERROR"), MB_OK);
			return 0;
		}
		break;

	case WM_COMMAND :
		CharacterProc(hWnd, wParam);
		break;

	case WM_DESTROY :
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

bool initSetting(HWND hWnd)
{
	// 캐릭터
	CreateWindow(TEXT("button"), TEXT("캐릭터"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 600, 150, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("ID : "), WS_CHILD | WS_VISIBLE , 40, 50, 100, 25, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("Lv : "), WS_CHILD | WS_VISIBLE , 40, 80, 100, 25, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("EXP :"), WS_CHILD | WS_VISIBLE , 40, 110, 100, 25, hWnd, (HMENU)-1, g_hInst, NULL);

	hIdEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 90, 50, 100, 20, hWnd, (HMENU)EDIT_ID, g_hInst, NULL);
	hLvEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 90, 80, 100, 20, hWnd, (HMENU)EDIT_LV, g_hInst, NULL);
	hExpEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 90, 110, 100, 20, hWnd, (HMENU)EDIT_EXP, g_hInst, NULL);

	CreateWindow(TEXT("button"), TEXT("생성"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 45, 100, 30, hWnd, (HMENU)BTN_CREATE, g_hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 355, 45, 100, 30, hWnd, (HMENU)BTN_SEARCH, g_hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 460, 45, 100, 30, hWnd, (HMENU)BTN_DELETE, g_hInst, NULL);

	// 아이템
	CreateWindow(TEXT("button"), TEXT("아이템"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 200, 600, 150, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("ID : "), WS_CHILD | WS_VISIBLE, 40, 250, 100, 25, hWnd, (HMENU)-1, g_hInst, NULL);

	hItemEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 90, 250, 100, 20, hWnd, (HMENU)EDIT_ITEM_ID, g_hInst, NULL);

	CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 40, 280, 100, 25, hWnd, (HMENU)BTN_ITEM_SEARCH, g_hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 40, 310, 100, 25, hWnd, (HMENU)BTN_ITEM_DELETE, g_hInst, NULL);

	return true;
}


bool CharacterProc(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case BTN_CREATE :
		CharacterCreateProc(hWnd);
		return true;

	case BTN_SEARCH :
		CharacterSearchProc(hWnd);
		return true;


	case BTN_DELETE :
		return true;
	}

	return false;
}


int SearchingQuery(HWND hWnd, TCHAR* inputId, characterData* outData)
{
	// TODO :: 문자열 매직넘버 처리.
	int ret;
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	ret = SQLConnect(hDbc, (SQLWCHAR*)L"LOCAL", SQL_NTS, (SQLWCHAR*)L"root", SQL_NTS, (SQLWCHAR*)L"dlrmsdnjs93", SQL_NTS);
	if (!(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO))
	{
		MessageBox(hWnd, TEXT("SQL접속이 실패했습니다."), TEXT("ERROR_SQL_CONNECT"), MB_OK);
		return -1;
	}

	// 형변환
	std::wstring searchingId = inputId;
	std::wstring inputString = L"select * from testdb.human where id =" + searchingId;
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);


	if (ret == SQL_SUCCESS)
	{
		int iCount = 0;
		SQLLEN iIdLen, iLvLen, iExpLen;

		while (TRUE)
		{
			ret = SQLFetch(hStmt);
			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			{
				MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_FETCH"), MB_OK);
				return -1;
			}
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(hStmt, 1, SQL_C_ULONG, &outData->id, 0, &iIdLen);
				SQLGetData(hStmt, 2, SQL_C_ULONG, &outData->level, 0, &iLvLen);
				SQLGetData(hStmt, 3, SQL_C_ULONG, &outData->exp, 0, &iExpLen);

				// id 데이터는 최대 한 개만 받으므로.
				break;
			}
			else MessageBox(hWnd, TEXT("찾으시는 데이터가 존재하지 않습니다."), TEXT("ERROR_DATA_NOT_FOUND"), MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
		return -1;
	}
	
	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;
	
}

// EditBox의 핸들과 int값을 받아 EditBox의 값을 바꾸어주는 함수.
bool SetEditBoxWithValue(HWND inputHandle, int textValue)
{
	TCHAR settingChar[EDIT_BUF_SIZE] = { 0 };
	_stprintf_s(settingChar, _countof(settingChar), _T("%d"), textValue);
	SetWindowText(inputHandle, settingChar);
	return true;
}

// TCHAR의 맨 앞이 널문자인지 확인해주는 함수.
bool IsStringEmpty(TCHAR* inputStr)
{
	if (inputStr[0] == '\0')
	{
		return true;
	}

	return false;

}

// 캐릭터 서치를 진행하는 함수.
bool CharacterSearchProc(HWND hWnd)
{
	TCHAR str[EDIT_BUF_SIZE];
	GetWindowText(hIdEdit, str, EDIT_BUF_SIZE);

	if (IsStringEmpty(str))
	{
		MessageBox(hWnd, TEXT("값을 입력해주세요."), TEXT("ERROR_NO_INPUT"), MB_OK);
	}
	else
	{
		characterData* searchingData = new characterData;
		int returnVal = SearchingQuery(hWnd, str, searchingData);
		if (returnVal == 0)
		{
			SetEditBoxWithValue(hIdEdit, searchingData->id);
			SetEditBoxWithValue(hLvEdit, searchingData->level);
			SetEditBoxWithValue(hExpEdit, searchingData->exp);
		}
		delete searchingData;
	}

	return true;
}

// 캐릭터 생성을 진행하는 함수.
bool CharacterCreateProc(HWND hWnd)
{
	// TODO :: 여기서부터 합시다.
	TCHAR str[EDIT_BUF_SIZE];
	GetWindowText(hIdEdit, str, EDIT_BUF_SIZE);

	return true;
}