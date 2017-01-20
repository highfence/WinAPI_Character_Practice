#pragma once

#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
using namespace std;
#include <sql.h>
#include <sqlext.h>

#include "define.h"

// Basic Win API Settings
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Test");

// Enum & Const Values
enum CharacterMenu
{
	EDIT_ID = 101, EDIT_LV, EDIT_EXP,
	BTN_CREATE = 201, BTN_SEARCH, BTN_DELETE,

	EDIT_ITEM_ID = 301, BTN_ITEM_SEARCH, BTN_ITEM_DELETE, LIST_ITEM
};

const int EDIT_BUF_SIZE = 32;
const int ITEM_TYPE_MAX_LENGTH = 40;
const int ITEM_NAME_MAX_LENGTH = 40;

// Data struct
typedef struct characterData
{
	int id;
	int level;
	int exp;
};

typedef struct itemData
{
	int id;
	wchar_t type[ITEM_TYPE_MAX_LENGTH];
	wchar_t name[ITEM_NAME_MAX_LENGTH];
};


// Functions
bool initSetting(HWND);
bool SetEditBoxWithValue(HWND, int);
int ConvertTCharToInt(TCHAR*);
bool IsStringEmpty(TCHAR*);
bool DBFree(SQLHENV, SQLHDBC, SQLHSTMT);
bool DBConnect(SQLHENV, SQLHDBC, SQLHSTMT);

// Character Functions
bool CharacterProc(HWND, WPARAM);
bool CharacterSearchProc(HWND);
bool CharacterCreateProc(HWND);
bool CharacterDeleteProc(HWND);
int SearchingQuery(HWND, TCHAR*, characterData*, bool);
int CreateQuery(HWND, characterData*);
int DeleteQuery(HWND, TCHAR*);
bool MakeCreateData(HWND, characterData*);
bool CheckCharacterIdAlreadyExist(HWND, TCHAR*);

// Item Functions
bool ItemProc(HWND, WPARAM);
bool ItemSearchProc(HWND);
bool ItemDeleteProc(HWND);
bool ListSelectProc(HWND, WPARAM);
int ItemSearchingQuery(HWND, TCHAR*, std::vector<itemData>*, bool);
int ItemDeleteQuery(HWND, TCHAR*);
int ItemIdSearchingQuery(HWND, int*, bool);
bool ListRefresh(HWND, TCHAR*, bool);
bool MakeItemList(HWND, std::vector<itemData>*);



// Variables
HWND hIdEdit;
HWND hLvEdit;
HWND hExpEdit;
HWND hItemEdit;
HWND hItemList;

int g_SelectedListIdx = INT_MIN;