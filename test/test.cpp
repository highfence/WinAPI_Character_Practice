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
		ItemProc(hWnd, wParam);
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
	CreateWindow(TEXT("button"), TEXT("아이템 검색"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 200, 600, 150, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("ID : "), WS_CHILD | WS_VISIBLE, 40, 230, 100, 25, hWnd, (HMENU)-1, g_hInst, NULL);
	CreateWindow(TEXT("static"), TEXT("캐릭터 보유 아이템"), WS_CHILD | WS_VISIBLE, 220, 200, 140, 25, hWnd, (HMENU)-1, g_hInst, NULL);

	hItemEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 70, 230, 100, 20, hWnd, (HMENU)EDIT_ITEM_ID, g_hInst, NULL);

	CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 40, 270, 130, 25, hWnd, (HMENU)BTN_ITEM_SEARCH, g_hInst, NULL);
	CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 40, 300, 130, 25, hWnd, (HMENU)BTN_ITEM_DELETE, g_hInst, NULL);

	return true;
}


// 캐릭터 관련 함수들을 처리해주는 함수.
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
		CharacterDeleteProc(hWnd);
		return true;
	}

	return false;
}

// 아이템 관련 함수들을 처리해주는 함수.
bool ItemProc(HWND hWnd, WPARAM wParam)
{
	// TODO :: 여기서 부터 짭시다.
	// 캐릭터를 고르면 item이 자동으로 리스트가 나오게 해야할지 아니면 따로 할지 고민중.
	switch (LOWORD(wParam))
	{
	case BTN_ITEM_SEARCH :
		ItemSearchProc(hWnd);
		return true;

	case BTN_ITEM_DELETE :
		ItemDeleteProc(hWnd);
		return true;

	case LIST_ITEM :
		ListSelectProc(hWnd, wParam);
		return true;
	}
	return false;
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
	TCHAR idStr[EDIT_BUF_SIZE];
	GetWindowText(hIdEdit, idStr, EDIT_BUF_SIZE);

	if (IsStringEmpty(idStr))
	{
		MessageBox(hWnd, TEXT("값을 입력해주세요."), TEXT("ERROR_NO_INPUT"), MB_OK);
	}
	else
	{
		characterData* searchingData = new characterData;
		int returnVal = SearchingQuery(hWnd, idStr, searchingData, true);
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
	TCHAR idStr[EDIT_BUF_SIZE];
	GetWindowText(hIdEdit, idStr, EDIT_BUF_SIZE);

	if (IsStringEmpty(idStr))
	{
		MessageBox(hWnd, TEXT("값을 입력해주세요."), TEXT("ERROR_NO_INPUT"), MB_OK);
	}
	else
	{
		bool IsCharacterIdExist = CheckCharacterIdAlreadyExist(hWnd, idStr);
		if (IsCharacterIdExist == true)
		{
			MessageBox(hWnd, TEXT("이미 존재하는 ID입니다."), TEXT("ERROR_EXIST_ID"), MB_OK);
			return true;
		}

		characterData* createData = new characterData;
		bool IsDataCreatedWell = MakeCreateData(hWnd, createData);

		if (IsDataCreatedWell == false)
		{
			MessageBox(hWnd, TEXT("올바른 값을 입력해주세요."), TEXT("ERROR_INVALID_INPUT"), MB_OK);
		}
		else
		{
			CreateQuery(hWnd, createData);
		}
		delete createData;
	}

	return true;
}

// 캐릭터 삭제를 진행하는 함수.
bool CharacterDeleteProc(HWND hWnd)
{
	TCHAR idStr[EDIT_BUF_SIZE];
	GetWindowText(hIdEdit, idStr, EDIT_BUF_SIZE);

	if (IsStringEmpty(idStr))
	{
		MessageBox(hWnd, TEXT("삭제할 id값을 입력해주세요."), TEXT("ERROR_NO_INPUT"), MB_OK);
	}
	else
	{
		bool IsCharacterIdExist = CheckCharacterIdAlreadyExist(hWnd, idStr);
		if (IsCharacterIdExist == false)
		{
			MessageBox(hWnd, TEXT("ID가 존재하지 않습니다."), TEXT("ERROR_NO_ID"), MB_OK);
		}
		else
		{
			DeleteQuery(hWnd, idStr);
		}
	}

	return true;
}

// Item을 검색하는 과정을 진행하는 함수.
bool ItemSearchProc(HWND hWnd)
{
	TCHAR idStr[EDIT_BUF_SIZE];
	GetWindowText(hItemEdit, idStr, EDIT_BUF_SIZE);

	if (IsStringEmpty(idStr))
	{
		MessageBox(hWnd, TEXT("찾으시려는 캐릭터의 ID값을 입력해주세요."), TEXT("ERROR_NO_INPUT"), MB_OK);
	}
	else
	{
		bool IsCharacterIdExist = CheckCharacterIdAlreadyExist(hWnd, idStr);
		if (IsCharacterIdExist == false)
		{
			MessageBox(hWnd, TEXT("ID가 존재하지 않습니다."), TEXT("ERROR_NO_ID"), MB_OK);
		}
		else
		{
			ListRefresh(hWnd, idStr, true);
		}
	}

	return true;
}

// Item을 삭제하는 과정을 진행하는 함수.
bool ItemDeleteProc(HWND hWnd)
{
	// TODO :: 여기서부터 합시다.
	TCHAR humanIdStr[EDIT_BUF_SIZE];
	GetWindowText(hItemEdit, humanIdStr, EDIT_BUF_SIZE);
	
	// 리스트에서 item이 선택 되지 않았을 경우, selectedList는 INT_MIN상태.
	if (g_SelectedListIdx == INT_MIN)
	{
		MessageBox(hWnd, TEXT("삭제할 아이템을 선택해 주세요."), TEXT("ERROR_INVALID_INPUT"), MB_OK);
	}
	else
	{
		ItemDeleteQuery(hWnd, humanIdStr);
		ListRefresh(hWnd, humanIdStr, false);
	}

	return true;
}

// List의 아이템이 선택 되었을 경우를 처리하는 함수.
bool ListSelectProc(HWND hWnd, WPARAM wParam)
{
	switch (HIWORD(wParam))
	{
	case LBN_SELCHANGE :
		g_SelectedListIdx = SendMessage(hItemList, LB_GETCURSEL, 0, 0);
		break;
	}

	return true;
}

// TCHAR*형의 id를 받아 db에서 검색. 인자로 받은 구조체에 채워주는 함수.
// 마지막 인자는 MessageBox를 띄울 것인지 결정(단순 서치만 할경우 false, 띄울 경우 true)
int SearchingQuery(HWND hWnd, TCHAR* inputId, characterData* outData, bool IsMessageBoxPop)
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
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL접속이 실패했습니다."), TEXT("ERROR_SQL_CONNECT"), MB_OK);
		}
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
				if (IsMessageBoxPop == true)
				{
					MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_FETCH"), MB_OK);
				}
				// TODO :: 종료 추가.
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
			else
			{
				if (IsMessageBoxPop == true)
				{
					MessageBox(hWnd, TEXT("찾으시는 데이터가 존재하지 않습니다."), TEXT("ERROR_DATA_NOT_FOUND"), MB_OK);
				}
				// TODO :: 종료 추가.
				return -1;
			}
		}
	}
	else
	{
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
		}
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// 인자로 받은 구조체를 db에 넣어주는 함수.
int CreateQuery(HWND hWnd, characterData* createData)
{
	// TODO :: 함수로 쪼개기.
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
	std::wstring createId(std::to_wstring(createData->id));
	std::wstring createLv(std::to_wstring(createData->level));
	std::wstring createExp(std::to_wstring(createData->exp));

	std::wstring inputString = L"insert into testdb.human VALUES('" + createId + L"', '" + createLv + L"', '" + createExp + L"')";
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		MessageBox(hWnd, TEXT("성공적으로 생성되었습니다."), TEXT("SAVE"), MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// TCHAR*형으로 받은 id에 해당하는 캐릭터를 db에서 삭제해주는 함수.
int DeleteQuery(HWND hWnd, TCHAR* inputId)
{
	// TODO :: 함수로 쪼개기.
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
	std::wstring deleteId = inputId;

	std::wstring inputString = L"delete from testdb.human where id =" + deleteId;
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		MessageBox(hWnd, TEXT("성공적으로 삭제되었습니다."), TEXT("DELETE"), MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// TCHAR*형의 캐릭터 ID를 받아 캐릭터가 가지고 있는 아이템을 조회해주는 함수.
// 인자는 핸들, 캐릭터 ID, itemData를 담을 벡터, MessageBox을 띄울지 말지 결정 (true라면 경고창이 나옴)
int ItemSearchingQuery(HWND hWnd, TCHAR* inputId, std::vector<itemData>* dataVec, bool IsMessageBoxPop)
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
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL접속이 실패했습니다."), TEXT("ERROR_SQL_CONNECT"), MB_OK);
		}
		return -1;
	}

	// 형변환
	std::wstring searchingId = inputId;
	std::wstring inputString = L"select i.id, i.type, i.name from testdb.human_has_item as h \
inner join testdb.item as i ON h.item_id = i.id where h.human_id =" + searchingId;
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);


	if (ret == SQL_SUCCESS)
	{
		int iCount = 0;
		SQLLEN iIdLen, iTypeLen, iNameLen;

		while (TRUE)
		{
			ret = SQLFetch(hStmt);
			itemData fetchData;
			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			{
				if (IsMessageBoxPop == true)
				{
					MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_FETCH"), MB_OK);
				}
				return -1;
			}
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(hStmt, 1, SQL_C_ULONG, &fetchData.id, 0, &iIdLen);
				SQLGetData(hStmt, 2, SQL_C_WCHAR, fetchData.type, ITEM_TYPE_MAX_LENGTH, &iTypeLen);
				SQLGetData(hStmt, 3, SQL_C_WCHAR, fetchData.name, ITEM_NAME_MAX_LENGTH, &iNameLen);

				dataVec->push_back(fetchData);
			}
			else if (dataVec->size() == 0)
			{
				if (IsMessageBoxPop == true)
				{
					MessageBox(hWnd, TEXT("찾으시는 데이터가 존재하지 않습니다."), TEXT("ERROR_DATA_NOT_FOUND"), MB_OK);
				}
				// TODO :: 종료 추가.
				return -1;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
		}
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// g_SelecteListIdx로 선택된 아이템을 db에서 해당하는 item을 삭제해 주는 함수.
int ItemDeleteQuery(HWND hWnd, TCHAR* humanIdStr)
{
	// TODO :: 함수로 쪼개기.
	// 캐릭터랑 합쳐볼까?
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
	std::wstring inputId = humanIdStr;
	int itemId = 0;
	ItemIdSearchingQuery(hWnd, &itemId, false);

	if (itemId == 0)
	{
		MessageBox(hWnd, TEXT("아이템 이름에 문제가 있습니다."), TEXT("ERROR_INVALID_NAME"), MB_OK);
	}

	std::wstring inputString = L"delete from testdb.human_has_item where item_id=" + to_wstring(itemId) + L" and human_id =" + inputId;
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		MessageBox(hWnd, TEXT("성공적으로 삭제되었습니다."), TEXT("DELETE"), MB_OK);
	}
	else
	{
		MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// g_SelectedListIdx가 있는 리스트의 id를 찾는 함수.
// 인자로 윈도우 핸들과, 반환할 int*형 id값을 받는다.
int ItemIdSearchingQuery(HWND hWnd, int* itemId, bool IsMessageBoxPop)
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
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL접속이 실패했습니다."), TEXT("ERROR_SQL_CONNECT"), MB_OK);
		}
		return -1;
	}

	// 형변환
	TCHAR searchingItemName[EDIT_BUF_SIZE];
	SendMessage(hItemList, LB_GETTEXT, g_SelectedListIdx, (LPARAM)searchingItemName);
	std::wstring itemName = searchingItemName;
	std::wstring inputString = L"select id from testdb.item where name = '" + itemName + L"'";
	const wchar_t *inputWChar = inputString.c_str();

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLWCHAR*)inputWChar, SQL_NTS);


	if (ret == SQL_SUCCESS)
	{
		int iCount = 0;
		SQLLEN iIdLen;

		while (TRUE)
		{
			ret = SQLFetch(hStmt);
			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			{
				if (IsMessageBoxPop == true)
				{
					MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_FETCH"), MB_OK);
				}
				// TODO :: 종료 처리.
				return -1;
			}
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(hStmt, 1, SQL_C_ULONG, itemId, 0, &iIdLen);
				break;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		if (IsMessageBoxPop == true)
		{
			MessageBox(hWnd, TEXT("SQL도중 데이터를 읽어오지 못했습니다."), TEXT("ERROR_SQL_EXCUTING"), MB_OK);
		}
	}

	// 접속 종료 및 반환.
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;

}

// TCHAR*형의 인자를 넣으면 int형 값으로 바꾸어주는 함수. 만약 숫자가 아닌 값이 있다면 INT_MIN 반환.
int ConvertTCharToInt(TCHAR* inputTChar)
{
	int ret = 0;
	int size = _tcslen(inputTChar);

	for (int idx = 0; idx < size; ++idx)
	{
		if (inputTChar[idx] >= '0' && inputTChar[idx] <= '9')
		{
			ret = ret * 10 + (inputTChar[idx] - '0');
		}
		else
		{
			return INT_MIN;
		}
	}

	return ret;

}

// 생성할 characterData의 정보를 window에서 얻어와서 채워넣어 주는 함수.
// 정상적으로 생성되었을 경우 true를, 아닐 경우 false반환.
bool MakeCreateData(HWND hWnd, characterData* makeData)
{
	TCHAR str[EDIT_BUF_SIZE];

	// Window에서 정보를 얻어와서 저장.
	GetWindowText(hIdEdit, str, EDIT_BUF_SIZE);
	makeData->id = ConvertTCharToInt(str);
	GetWindowText(hLvEdit, str, EDIT_BUF_SIZE);
	makeData->level = ConvertTCharToInt(str);
	GetWindowText(hExpEdit, str, EDIT_BUF_SIZE);
	makeData->exp = ConvertTCharToInt(str);

	// 반환값이 이상할 경우, false 반환.
	if (makeData->id == INT_MIN || makeData->level == INT_MIN || makeData->exp == INT_MIN)
	{
		return false;
	}

	return true;
}

// 캐릭터 정보를 생성하기 전에 ID가 존재하는지 확인해주는 함수.
// 존재할 경우 True를, 아닐경우 false반환.
bool CheckCharacterIdAlreadyExist(HWND hWnd, TCHAR* searchingId)
{
	characterData* checkData = new characterData;
	int retVal = SearchingQuery(hWnd, searchingId, checkData, false);
	delete checkData;

	if (retVal == 0)
	{
		return true;
	}

	return false;
	
}

// 쿼리 결과를 이용하여 아이템의 리스트를 만들어주는 함수.
bool MakeItemList(HWND hWnd, std::vector<itemData>* dataVec)
{
	hItemList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 220, 230, 200, 100, hWnd, (HMENU)LIST_ITEM, g_hInst, NULL);

	int size = dataVec->size();
	for (int idx = 0; idx < size; ++idx)
	{
		SendMessage(hItemList, LB_ADDSTRING, 0, (LPARAM)dataVec->at(idx).name);
	}

	return true;
}

// 리스트를 갱신하는 작업을 해주는 함수.
// 인자로 윈도우 핸들, TCHAR*형식의 id, 그리고 MessageBox를 띄울지 말지 결정하는 값을 가진다.
bool ListRefresh(HWND hWnd, TCHAR* idStr, bool IsMessageBoxPop)
{
	vector<itemData>* dataVec = new vector<itemData>;
	ItemSearchingQuery(hWnd, idStr, dataVec, IsMessageBoxPop);
	MakeItemList(hWnd, dataVec);

	// vector 메모리 해제.
	vector<itemData>().swap(*dataVec);

	// 삭제를 위해서 selectedListIdx초기화.
	g_SelectedListIdx = INT_MIN;

	return true;
}