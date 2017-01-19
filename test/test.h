#pragma once
#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
using namespace std;
#include <sql.h>
#include <sqlext.h>

// Basic Win API Settings
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Test");

// Data struct
typedef struct characterData
{
	int id;
	int level;
	int exp;
};


// Functions
bool initSetting(HWND);
bool CharacterProc(HWND, WPARAM);
bool ItemProc(HWND, WPARAM);
int SearchingQuery(HWND, TCHAR*, characterData*);
int CreateQuery(HWND, characterData*);
bool SetEditBoxWithValue(HWND, int);
bool IsStringEmpty(TCHAR*);
bool CharacterSearchProc(HWND);
bool CharacterCreateProc(HWND);
int ConvertTCharToInt(TCHAR*);
bool MakeCreateData(HWND, characterData*);
bool CheckCharacterIdAlreadyExist(HWND, TCHAR*);

// Enum & Const Values
enum CharacterMenu
{
	EDIT_ID = 101, EDIT_LV, EDIT_EXP,
	BTN_CREATE = 201, BTN_SEARCH, BTN_DELETE,

	EDIT_ITEM_ID = 301, BTN_ITEM_SEARCH, BTN_ITEM_DELETE
};

const int EDIT_BUF_SIZE = 32;

// Variables
HWND hIdEdit;
HWND hLvEdit;
HWND hExpEdit;
HWND hItemEdit;