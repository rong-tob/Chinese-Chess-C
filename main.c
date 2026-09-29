#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> // Include Windows header for CP_UTF8
#include <mmsystem.h> //播放音效用
#pragma comment(lib, "winmm.lib")
#include "rule.h"
#include "core.h"

int main(int argc, char *argv[]) {
	SetConsoleOutputCP(CP_UTF8);//用來顯示繁體中文，避免亂碼
	SetConsoleCP(CP_UTF8);//用來顯示繁體中文，避免亂碼
	system("mode con cols=105 lines=35");//設置控制台窗口大小
	
	PlaySound(TEXT("effect_sound/guitar.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效	
	Show_menu();//顯示菜單	
	Get_command();//獲取用戶命令
	
	system("pause");
	return 0;
}
