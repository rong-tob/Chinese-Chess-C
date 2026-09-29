#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mmsystem.h> //播放音效用
#pragma comment(lib, "winmm.lib")
#include "core.h"
#include "rule.h"

// 繪製菜單
void Show_menu() { //數字是設置顏色(上網查)
    printf("====================================================================================================\n");
    printf("|  \033[1;36m    起         \033[30m|＼_\033[37;／▏ \033[0;33m╱\033[30;43m◤                ◢\033[37;40m                \033[30;43m◤            \033[37;40m                      |\n");
    printf("|  \033[1;36m觀  手        \033[30m／   \033[37m  \\ \033[0;33m／                 \033[30;43m◤                ◢\033[37;40m                                  |\n");
    printf("|  \033[1;36m棋  無      \033[30m／  ■ \033[37m■ ▏               \033[0;30;43m◤                ◢\033[37;40m                                      |\n");
    printf("|  \033[1;36m不  回     \033[30m／     \033[37m   │               \033[0;30;43m◤                ◢\033[37;40m                \033[33m◢\033[37m                     |\n");
    printf("|  \033[1;36m語  大    \033[30m／  \\  ×  /             \033[30;43m◤                ◢\033[37;40m                \033[30;43m◤  \033[37;40m                     |\n");
    printf("|  \033[1;36m真  丈   \033[30mㄟ     \\ __\033[0;30;43m◤            \033[33;40m◤                \033[30;43m◤                ◢\033[37;40m                        |\n");
    printf("|  \033[1;36m君  夫   \033[30m◥◣   ▕\033[37;43m▏           \033[0;33m◤                \033[30;43m◤                ◢\033[37;40m                             |\n");
    printf("|  \033[1;36m子        \033[30m\\◥\033[0m◣ \033[1;30m▕\033[37;43m▎         \033[0;33m◤                \033[30;43m◤                ◢\033[37;40m                               |\n");
    printf("|           \033[33m╱\033[30;43m◤\033[1;40m\\\033[0m◥\033[1;47m▇▇\033[0;43m        \033[33;40m◤                \033[30;43m◤                ◢\033[37;40m                                 |\n");
    printf("|                                                                                                  |\n");
    printf("|                                                                                                  |\n");
    printf("|     ######      #     #       #####      ###     #      ######      ######      ######           |\n");
    printf("|     #           #     #         #        # #     #      #           #           #                |\n");
    printf("|     #           #     #         #        #  #    #      #           #           #                |\n");
    printf("|     #           #######         #        #   #   #      ####        ######      ####             |\n");
    printf("|     #           #     #         #        #    #  #      #                #      #                |\n");
    printf("|     #           #     #         #        #     # #      #                #      #                |\n");
    printf("|     ######      #     #       #####      #     ###      ######      ######      ######           |\n");
    printf("|                                                                                                  |\n");
    printf("|     ######      #     #       ######      ######       ######                                    |\n");
    printf("|     #           #     #       #           #            #             開始遊戲                     |\n");
    printf("|     #           #     #       #           #            #                                         |\n");
    printf("|     #           #######       #####       ######       ######        遊戲幫助                     |\n");
    printf("|     #           #     #       #                #            #                                    |\n");
    printf("|     #           #     #       #                #            #        結束遊戲                     |\n");
    printf("|     ######      #     #       ######      ######       ######                                    |\n");
    printf("|==================================================================================================|\n");
}

// 獲取指令
void Get_command() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);//hStdin：用於讀取使用者輸入
    DWORD cNumRead, fdwMode;//cNumRead：用來儲存讀取的事件數量,fdwMode：用來儲存輸入模式的設置
    INPUT_RECORD irInBuf[128];//irInBuf：用來存儲讀取的輸入事件
    COORD pos;//pos：用來表示螢幕上的座標
    int command = 0;//command：用來儲存並執行使用者輸入的命令

    // 啟用滑鼠輸入和快速模式
    SetConsoleMode(hStdin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    /*需要複雜輸入處理，特別是需要處理滑鼠操作*/

    while (command == 0) {
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);/*讀取控制台輸入事件，最多128個事件，存儲在irInBuf中，並將實際讀取的事件數量存儲在cNumRead中*/
        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == MOUSE_EVENT && irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {/*如果事件類型是滑鼠事件並且左鍵被按下*/
                pos = irInBuf[i].Event.MouseEvent.dwMousePosition;/*獲取滑鼠位置*/

                if (pos.Y == 21 && pos.X >= 70 && pos.X <= 79) { // 開始遊戲的座標範圍
                    command = 1;/*開始遊戲*/
                } else if (pos.Y == 23 && pos.X >= 70 && pos.X <= 79) { // 遊戲幫助的座標範圍
                    command = 2;/*遊戲幫助*/
                } else if (pos.Y == 25 && pos.X >= 70 && pos.X <= 79) { // 退出遊戲的座標範圍
                    command = 3;/*退出遊戲*/
                }
            }
            if (irInBuf[i].EventType == KEY_EVENT) {/*如果事件類型是鍵盤事件*/
                if (irInBuf[i].Event.KeyEvent.bKeyDown && irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {/*如果鍵盤事件是鍵被按下且按下的是ESC鍵*/
                    command = 3; // 按下ESC則退出遊戲
                }
            }
        }
        /*當 command 被設定為非零值時，循環結束，並清除螢幕。具體來說：
        當左鍵單擊特定座標範圍內時，設定不同的命令值來對應開始遊戲、顯示遊戲幫助或退出遊戲。
        當按下ESC鍵時，設定命令值為3，來退出遊戲。*/
    }

    system("cls");

    PlaySound(TEXT("effect_sound/button_click.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效 
    if(command == 1) { Start_game(); }
    else if(command == 2) { Instruction(); }
    else if(command == 3) { exit(0); }
    else { Error_hint(); Show_menu(); Get_command(); }
}

// 顯示遊戲說明
void Instruction() { 
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD cNumRead, fdwMode;
    INPUT_RECORD irInBuf[128];
    COORD pos;
    int command = 0;

    // 啟用滑鼠輸入和快速模式
    SetConsoleMode(hStdin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    printf("\n                                              象棋口訣\n");
    printf("                                    將軍不離九宮內，士止相隨不出官。\n");
    printf("                                    象飛四方營四角，馬行一步一尖沖。\n");
    printf("                                    炮須隔子打一子，車行直路任西東。\n");
    printf("                                    唯卒只能行一步，過河橫進退無蹤。\n"); 
    printf("\n\nChinese Chess 是一款雙人休閒小遊戲。選擇'開始遊戲'，可以與好友開啟一局有趣的中國象棋對弈！\n\n");
    printf("詳細操作：\n首先，紅方先行運棋：根據螢幕上出現的指示完成運棋操作(注意：輸入座標時兩個數值中間需用空格分開)，");
    printf("當完成紅方運棋後，輪到藍方運棋回合，同理，藍");
    printf("方運棋結束後重複上述操作，直至一方的主帥被吃掉，遊戲結束。快邀請您的好友一齊來下象棋吧！\n\n");
    printf("                                         (請按 ESC 返回主菜單)");

    while (command == 0) {
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);/*讀取控制台輸入事件，最多128個事件，存儲在irInBuf中，並將實際讀取的事件數量存儲在cNumRead中*/
        for (DWORD i = 0; i < cNumRead; i++) {/*從 irInBuf[0] 到 irInBuf[cNumRead - 1]*/
            if (irInBuf[i].EventType == KEY_EVENT) {/*如果是鍵盤事件*/
                if (irInBuf[i].Event.KeyEvent.bKeyDown && irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    /*如果鍵盤事件是鍵被按下且按下的是ESC鍵*/
                    command = 88;/*按下ESC則退出遊戲(當偵測到 ESC 鍵被按下時，將 command 變數設置為88)*/
                }/*總結:按下 ESC 鍵，將 command 變數設置為88，從而退出這個無限循環。ps.用於控制程式的流程，例如退出菜單、取消操作等*/
            }
        }
    }
    system("cls");

    PlaySound(TEXT("effect_sound/button_click.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    if(command==88) {Show_menu();Get_command();}
    else {Error_hint();Instruction();}
}

// 繪製棋盤和棋子
void Draw_map(int map[19][18]) {/*19行18列的地圖*/
    int i,j;/*二微陣列變數*/
    printf("\n");
    printf("\n提示：            ");
    printf("直到把對方的\033[41m帥\033[0m/\033[46m將\033[0m吃掉才算勝利哦！\n\n");/*print遊戲規則提示信息 ps.有顏色標註*/
    printf("                                                  藍方\n"); 
    for(i = 0; i < 19; i++) {
        printf ("                               "); /*打印前導空格，讓棋盤居中*/
        for (j = 0; j < 18; j++) {
            if(map[i][j] >= 0 && map[i][j] <= 9) { /*檢查地圖數值是否在有效範圍內*/
                switch(map[i][j]){
                    case 0:
                        if (i == 0 && j == 1) { printf("╔ "); break; } // 左上角
                        else if (i == 0 && j == 17) { printf("╗"); break; } // 右上角
                        else if (i == 18 && j == 1) { printf("╚ "); break; } // 左下角
                        else if (i == 18 && j == 17) { printf("╝"); break; } // 右下角
                        else if (i != 0 && j == 1 || i != 18 && j == 1) { printf("╟ "); break; } // 左邊框
                        else if (i != 0 && j == 17 || i != 18 && j == 17) { printf("╢"); break; } // 右邊框
                        else if (i == 2 && j == 9 || i == 16 && j == 9) { printf("╳ "); break; } // 特殊標記
                        else if (i == 0 && j != 1 || i == 10 && j != 1) { printf("╤ "); break; } // 上邊框
                        else if (i == 18 && j != 1 || i == 8 && j != 17) { printf("╧ "); break; } // 下邊框
                        else { printf("┼ "); break; } // 中間交叉點
                    case 1: // 如果地圖格子的值為 1，則根據具體位置打印不同的線條字符
                        if (i == 0 || i == 18) { printf("═ "); break; } // 上下邊框線
                        else if (j == 1) { printf("║"); break; } // 左邊框線
                        else if (j == 17) { printf(" ║"); break; } // 右邊框線
                        else if (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 11 || j == 13 || j == 15) {
                            if (i != 0 && i != 18) { printf(" │"); break; } // 垂直線條
                        } else if (i == 2 || i == 4 || i == 6 || i == 12 || i == 14 || i == 16) {
                            if (j != 1 && j != 17) { printf("──"); break; } // 水平線條
                        } else if (i == 8 || i == 10) { printf("══"); break; } // 特別的水平線條
                        else { printf("  "); break; } // 空格
                    case 2: printf("楚"); break; // 如果地圖格子的值為 2，print“楚”
                    case 3: printf("河"); break; // 如果地圖格子的值為 3，print“河”
                    case 4: printf("漢"); break; // 如果地圖格子的值為 4，print“漢”
                    case 5: printf("界"); break; // 如果地圖格子的值為 5，print“界”
                    case 6: printf("  "); break; // 如果地圖格子的值為 6，print空格
                    case 7: printf("★"); break; // 如果地圖格子的值為 7，print“★” 
                }
            } else {
                switch(map[i][j]) {
                    case 101: printf("9   "); break;
                    case 102: printf("    "); break;
                    case 103: printf("8   "); break;
                    case 104: printf("7   "); break;
                    case 105: printf("6   "); break;
                    case 106: printf("5   "); break;
                    case 107: printf("4   "); break;
                    case 108: printf("3   "); break;
                    case 109: printf("2   "); break;
                    case 110: printf("1   "); break;
                    case 'a': printf("\033[41m兵\033[0m"); break; // 紅兵
                    case 'A': printf("\033[46m卒\033[0m"); break; // 藍卒
                    case 'b': printf("\033[41m炮\033[0m"); break; // 紅炮
                    case 'B': printf("\033[46m砲\033[0m"); break; // 藍砲
                    case 'c': printf("\033[41m車\033[0m"); break; // 紅車
                    case 'C': printf("\033[46m車\033[0m"); break; // 藍車
                    case 'd': printf("\033[41m馬\033[0m"); break; // 紅馬
                    case 'D': printf("\033[46m馬\033[0m"); break; // 藍馬
                    case 'p': printf("\033[41m相\033[0m"); break; // 紅相
                    case 'E': printf("\033[46m象\033[0m"); break; // 藍象
                    case 's': printf("\033[41m士\033[0m"); break; // 紅士
                    case 'F': printf("\033[46m仕\033[0m"); break; // 藍仕
                    case 'z': printf("\033[41m帥\033[0m"); break; // 紅帥
                    case 'G': printf("\033[46m將\033[0m"); break; // 藍將
                }/*41紅,46藍,0重置*/
            }
        }
        printf("\n");
    }
    printf("                                                  紅方\n");
    printf("                               0       1   2   3   4   5   6   7   8\n\n");
}

// 輸出操作錯誤提示
void Error_hint() {
    PlaySound(TEXT("effect_sound/error.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    MessageBoxW(NULL, L"沒有找到該序號對應的操作,請再試一次", L"操作錯誤", MB_OK | MB_ICONERROR);
}

// 吃自己的子警告
void Self_hint() {
    PlaySound(TEXT("effect_sound/error.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    MessageBoxW(NULL, L"！警告！： 您不能吃掉自己的棋子", L"操作錯誤", MB_OK | MB_ICONWARNING);
}

// 棋子的移動不符合棋法警告
void Rule_hint() {
    PlaySound(TEXT("effect_sound/error.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    MessageBoxW(NULL, L"！警告！： 您這樣運棋是不合法的", L"操作錯誤", MB_OK | MB_ICONWARNING);
}

// 擅動對方棋子警告
void Object_hint() {
    PlaySound(TEXT("effect_sound/error.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    MessageBoxW(NULL, L"！警告！： 您不能移動對方的棋子", L"操作錯誤", MB_OK | MB_ICONWARNING);
}

// 該座標沒有棋子提醒
void Gap_hint() {
    PlaySound(TEXT("effect_sound/error.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
    MessageBoxW(NULL, L"！警告！： 您輸入的座標沒有棋子，還請您認真一點", L"操作錯誤", MB_OK | MB_ICONWARNING);
}

// 判斷遊戲是否結束，以及誰是勝利者。如果遊戲結束，將顯示主菜單並播放音效
void Go_on(int map[19][18]) {
    int i, j;
    int flag_1 = 0, flag_2 = 0;

    for(i = 0; i < 19; i++) {   
        for (j = 0; j < 18; j++) {/*檢查是否有紅方的帥 (將)*/
            if(map[i][j] == 'z') { flag_1 = 1; }/*如果找到紅帥，設置 flag_1 為 1*/
            /*檢查是否有藍方的將 (帥)*/
            else if(map[i][j] == 'G') { flag_2 = 1; }/*如果找到藍將，設置 flag_2 為 1*/
        }
    } 

    /*如果紅方的帥不在棋盤上，藍方獲勝*/
    if(flag_1 == 0 && flag_2 == 1) {
        system("cls");// 清屏
        Show_menu(); // 顯示主菜單
        PlaySound(TEXT("effect_sound/firework.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
        printf("\n                                (´ΘωΘ`)本局遊戲結束！恭喜藍方獲勝！\n");
        printf("\n                                           已為您返回主菜單");
        Get_command();// 等待玩家指令
    } else if(flag_1 == 1 && flag_2 == 0) {// 如果藍方的將不在棋盤上，紅方獲勝
        system("cls");// 清屏     
        Show_menu(); // 顯示主菜單
        PlaySound(TEXT("effect_sound/firework.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
        printf("\n                                (´ΘωΘ`)本局遊戲結束！恭喜紅方獲勝！\n");
        printf("\n                                           已為您返回主菜單");
        Get_command();// 等待玩家指令
    }
}

// 坐標轉換函數
//將棋盤上的抽象座標轉換為具體的顯示位置，使得在顯示或操作棋盤時能夠正確定位
int convertX(int x) {//列
    switch (x) {
        case 0: return 1; // x = 0 對應棋盤列 1
        case 1: return 3; // x = 1 對應棋盤列 3
        case 2: return 5;
        case 3: return 7;
        case 4: return 9;
        case 5: return 11;
        case 6: return 13;
        case 7: return 15;
        case 8: return 17;
        default: return -1; // 如果輸入的 x 超過範圍，返回 -1 表示錯誤
    }
}

int convertY(int y) {//行
    switch (y) {
        case 0: return 18; // y = 0 對應棋盤行 18
        case 1: return 16; // y = 1 對應棋盤行 16
        case 2: return 14;
        case 3: return 12;
        case 4: return 10;
        case 5: return 8;
        case 6: return 6;
        case 7: return 4;
        case 8: return 2;
        case 9: return 0;
        default: return -1;// 如果輸入的 y 超過範圍，返回 -1 表示錯誤
    }
}

// 將滑鼠點擊坐標轉換為棋盤坐標(將螢幕座標轉換為棋盤上的格子座標)
void convertToChessboardCoordinates(int clickX, int clickY, int *chessX, int *chessY) {
    int offsetX = clickX - 35; // 將 X 座標偏移 35 單位，調整為相對棋盤的起點
    int offsetY = clickY - 15; // 將 Y 座標偏移 15 單位，調整為相對棋盤的起點
    *chessX = round(offsetX / 2.0) / 2; // 將偏移後的 X 座標轉換為棋盤的 X 座標，使用 round 進行四捨五入
    *chessY = 4 - round(offsetY / 2.0); // 將偏移後的 Y 座標轉換為棋盤的 Y 座標，使用 round 進行四捨五入
}

// 獲取滑鼠點擊坐標
void getMouseClickCoordinates(int *x, int *y) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);//hStdin：用於讀取使用者輸入
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//hStdout：用於讀取使用者輸出
    DWORD cNumRead;//cNumRead：用來儲存讀取的事件數量
    INPUT_RECORD irInBuf[128];//irInBuf：用來存儲讀取的輸入事件
    COORD pos, initialPos;//pos：用來表示螢幕上的座標,初始位置
    CONSOLE_SCREEN_BUFFER_INFO csbi;// 用於存儲控制台緩衝區的訊息

    // 獲取當前滑鼠位置
    //這段程式碼的主要目的是保存當前的滑鼠位置，這樣在進行其他操作（例如讀取滑鼠點擊位置）後，可以將滑鼠恢復到這個初始位置，以確保螢幕輸出的一致性和整潔性
    GetConsoleScreenBufferInfo(hStdout, &csbi);
    initialPos = csbi.dwCursorPosition;//儲存 GetConsoleScreenBufferInfo 函數獲取到的控制台緩衝區資訊

    // 設置控制台模式，啟用擴展標誌、視窗輸入和滑鼠輸入(確保接下來能夠正確地處理滑鼠點擊並將其轉換為棋盤上的位置)
    SetConsoleMode(hStdin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    /*ENABLE_EXTENDED_FLAGS：啟用擴展標誌，這是為了使用 ENABLE_WINDOW_INPUT 和 ENABLE_MOUSE_INPUT 標誌*/
    *x = 0, *y = 0;/*代碼初始化 x 和 y 變數(x,y初始化不為零，將它們設置為 0。這些變數用於存儲滑鼠點擊位置的棋盤坐標。*/
    while (1) {
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead); // 讀取輸入,儲讀取的輸入在irInBuf(大大小為128),儲存讀取的事件數量在cNumRead
        for (DWORD i = 0; i < cNumRead; i++) {
            // 檢查是否有滑鼠事件且按下左鍵
            if (irInBuf[i].EventType == MOUSE_EVENT && irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                pos = irInBuf[i].Event.MouseEvent.dwMousePosition;// 獲取滑鼠位置
                convertToChessboardCoordinates(pos.X, pos.Y, x, y);// 將滑鼠位置轉換為棋盤坐標

                // 恢復光標位置
                SetConsoleCursorPosition(hStdout, initialPos);
                return;
            }
        }
    }
}

// 紅方移動
void Red_move(int map[19][18]) {
    int first_1, first_2, end_1, end_2; // 起始(first)和終點(end)座標
    int x1, y1, x2, y2;//轉換後的棋盤座標，將玩家輸入的座標轉換為棋盤上實際使用的座標

    // 提示紅方玩家輸入想要移動的棋子座標
    printf("現在請\033[41m紅\033[0m方運棋               (⊙+⊙)請輸入您想要移動的棋子座標：");
    // getMouseClickCoordinates(&first_1, &first_2);
    // printf("%d %d\n", first_1, first_2);
    scanf("%d %d", &first_1, &first_2);// 使用鍵盤輸入座標

    // 如果輸入的座標為88，則清屏並顯示主選單，等待下一個命令
    if(first_1 == 88 || first_2 == 88) { system("cls"); Show_menu(); Get_command(); }

    // 提示紅方玩家輸入棋子目標位置的座標
    printf("                             (> O <)現在輸入您想要讓棋子到達的座標：");
    // getMouseClickCoordinates(&end_1, &end_2);
    // printf("%d %d\n", end_1, end_2);
    scanf("%d %d", &end_1, &end_2);

    sleep(1);// 暫停1秒

    // 如果輸入的座標為88，則清屏並顯示主選單，等待下一個命令
    if(end_1 == 88 || end_2 == 88) { system("cls"); Show_menu(); Get_command(); }

    system("cls"); // 清屏

    // 將輸入的座標轉換為棋盤座標 ps.詳細解釋在藍方(void Blue_move)
    x1 = convertX(first_1);
    y1 = convertY(first_2);
    x2 = convertX(end_1);
    y2 = convertY(end_2);

    // 如果轉換後的座標無效，顯示錯誤提示並返回
    if (x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1) {
        Gap_hint();
        return;
    }

    // 檢查並執行紅方的移動規則
    Red_rule(map, y1, x1, y2, x2);
}

// 藍方移動
void Blue_move(int map[19][18]) {
    int first_1, first_2, end_1, end_2; // 宣告變數，用來儲存起始和終點座標
    int x1, y1, x2, y2;// 宣告變數，用來儲存轉換後的棋盤座標

    // 提示藍方玩家輸入想要移動的棋子座標
    printf("現在請\033[46m藍\033[0m方運棋               (⊙+⊙)請輸入您想要移動的棋子座標：");
    // getMouseClickCoordinates(&first_1, &first_2);
    // printf("%d %d\n", first_1, first_2);
    scanf("%d %d", &first_1, &first_2);

    if(first_1 == 88 || first_2 == 88) { system("cls"); Show_menu(); Get_command(); }

    printf("                             (> O <)現在輸入您想要讓棋子到達的座標：");
    // getMouseClickCoordinates(&end_1, &end_2);
    // printf("%d %d\n", end_1, end_2);
    scanf("%d %d", &end_1, &end_2);

    sleep(1);// 暫停1秒

    // 如果輸入的座標為88，則清屏並顯示主選單，等待下一個命令
    if(end_1 == 88 || end_2 == 88) { system("cls"); Show_menu(); Get_command(); }

    system("cls");// 清屏

    // 將輸入的座標轉換為棋盤座標(確保玩家輸入的座標能夠正確對應到棋盤顯示中的實際位置)
    x1 = convertX(first_1);// 將玩家輸入的棋子初始 x 座標轉換為棋盤顯示座標
    y1 = convertY(first_2);
    x2 = convertX(end_1);// 將玩家輸入的目標 x 座標轉換為棋盤顯示座標
    y2 = convertY(end_2);

    /*
    例如:

    (玩家輸入的座標)
    int first_1 = 2;  // 玩家想移動的棋子的 x 座標
    int first_2 = 3;  // 玩家想移動的棋子的 y 座標
    int end_1 = 4;    // 目標位置的 x 座標
    int end_2 = 5;    // 目標位置的 y 座標
    (轉換座標)
    int x1 = convertX(first_1); // x1 變為 5
    int y1 = convertY(first_2); // y1 變為 12
    int x2 = convertX(end_1);   // x2 變為 9
    int y2 = convertY(end_2);   // y2 變為 8

    轉換後的座標為 (x1, y1) 和 (x2, y2)，它們對應於棋盤上實際的位置
    */

    // 如果轉換後的座標無效，顯示錯誤提示並返回
    if (x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1) {//檢查座標轉換是否有效,若座標轉為 -1，表示該座標無效。若座標無效，程式會顯示錯誤提示並終止當前操作
        Gap_hint();// 顯示錯誤提示，告訴玩家座標無效
        return;// 結束函數，不執行後續的移動邏輯
    }

    // 檢查並執行紅方的移動規則
    Blue_rule(map, y1, x1, y2, x2);
}
/*
流程:
1.玩家輸入起始座標 first_1 和 first_2
2.如果玩家輸入的座標為 88，則返回主選單
3.玩家輸入目標座標 end_1 和 end_2
4.如果玩家輸入的座標為 88，則返回主選單
5.清屏
6.將起始和目標座標轉換為棋盤座標 x1, y1, x2, y2
7.如果轉換後的座標無效，顯示錯誤提示並返回
8.根據轉換後的棋盤座標，檢查並執行相應的移動規則（紅方或藍方）
*/
/*
總結
步驟如下：
1.提示玩家輸入想要移動的棋子座標
2.如果玩家輸入的座標為88，則返回主選單
3.提示玩家輸入棋子目標位置的座標
4.如果玩家輸入的座標為88，則返回主選單
5.清屏
6.將輸入的座標轉換為棋盤座標
7.如果轉換後的座標無效，顯示錯誤提示並返回
8.檢查並執行相應的移動規則（紅方或藍方）
*/

// 判斷紅棋移動是否合法
void Red_rule(int map[19][18], int y_1, int x_1, int y_2, int x_2) {    
    //y_1 和 x_1:起始位置
    //y_2 和 x_2 :棋子的目標位置，也就是棋子移動後的位置
    PlaySound(TEXT("effect_sound/piece_place_down.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效

    // 檢查起始位置是否為特殊棋盤標記(0~7前面有打特殊標記分別代表的意思)
    if(map[y_1][x_1] == 0 || map[y_1][x_1] == 1 || map[y_1][x_1] == 2 || map[y_1][x_1] == 3) {
        Gap_hint(); // 提示不可移動
        Draw_map(map); // 重畫棋盤
        Go_on(map); // 繼續遊戲
        Red_move(map); // 紅方繼續移動
    } else if(map[y_1][x_1] == 4 || map[y_1][x_1] == 5 || map[y_1][x_1] == 6 || map[y_1][x_1] == 7) {
        Gap_hint(); Draw_map(map); Go_on(map); Red_move(map);
    } else if(map[y_1][x_1] == map[y_2][x_2]) {//檢查起始位置和目標位置是否相同,相同就表示不能移動到同樣的位置
        Gap_hint(); Draw_map(map); Go_on(map); Red_move(map);
    } else {
        if(map[y_1][x_1] >= 'a' && map[y_1][x_1] <= 'z') {

            // 檢查目標位置是否為藍方棋子(大寫字母))
            if((map[y_2][x_2] >= 'a' && map[y_2][x_2] <= 'z') && (map[y_1][x_1] >= 'a' && map[y_1][x_1] <= 'z')) {
                Self_hint(); // 提示不能吃自己
                Draw_map(map); // 重畫棋盤
                Go_on(map); // 繼續遊戲
                Red_move(map); // 由紅方移動
            } else {
                Move_rule(map, y_1, x_1, y_2, x_2);  // 移動棋子            
                Draw_map(map);  // 重畫棋盤
                Go_on(map);     // 繼續遊戲
                Blue_move(map); // 藍方繼續移動
            }
        } else if(map[y_1][x_1] >= 'A' && map[y_1][x_1] <= 'Z') {
            Object_hint();  // 提示不能移動對方棋子
            Draw_map(map);   // 重畫棋盤
            Go_on(map);     // 繼續遊戲
            Red_move(map);  // 由紅方繼續移動
        }
    }
    
}

// 判斷藍棋移動是否合法
void Blue_rule(int map[19][18], int y_1, int x_1, int y_2, int x_2) {
    //y_1 和 x_1:起始位置
    //y_2 和 x_2 :棋子的目標位置，也就是棋子移動後的位置
    PlaySound(TEXT("effect_sound/piece_place_down.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效

    // 檢查起始位置是否為特殊棋盤標記(0~7前面有打特殊標記分別代表的意思)
    if(map[y_1][x_1] == 0 || map[y_1][x_1] == 1 || map[y_1][x_1] == 2 || map[y_1][x_1] == 3) {
        Gap_hint();         // 提示不可移動
        Draw_map(map);      // 重畫棋盤
        Go_on(map);         // 繼續遊戲
        Blue_move(map);     // 藍方繼續移動
    } else if(map[y_1][x_1] == 4 || map[y_1][x_1] == 5 || map[y_1][x_1] == 6 || map[y_1][x_1] == 7) {//如果目標位置也是藍方棋子
        Gap_hint(); Draw_map(map);  Go_on(map); Blue_move(map);
    } else if(map[y_1][x_1] == map[y_2][x_2]) {//檢查起始位置和目標位置是否相同,相同就表示不能移動到同樣的位置
        Gap_hint(); Draw_map(map); Go_on(map); Blue_move(map);
    } else {
        if(map[y_1][x_1] >= 'A' && map[y_1][x_1] <= 'Z') {
            
            // 檢查目標位置是否為藍方棋子(大寫字母))
            if((map[y_2][x_2] >= 'A' && map[y_2][x_2] <= 'Z') && (map[y_1][x_1] >= 'A' && map[y_1][x_1] <= 'Z')) {//如果目標位置也是藍方棋子
                Self_hint();    // 提示不能吃自己
                Draw_map(map);  // 重畫棋盤
                Go_on(map);     // 繼續遊戲
                Blue_move(map); // 藍方繼續移動
            } else {//如果目標位置不是藍方棋子(可通)
                Move_rule(map, y_1, x_1, y_2, x_2); // 移動棋子
                Draw_map(map);  // 重畫棋盤
                Go_on(map);     // 繼續遊戲
                Red_move(map);  // 由紅方移動
            }
        } 
        // 檢查起始位置是否為紅方棋子
        else if(map[y_1][x_1] >= 'a' && map[y_1][x_1] <= 'z') {//如果是
            Object_hint();  // 提示不能移動對方棋子
            Draw_map(map);  // 重畫棋盤
            Go_on(map);     // 繼續遊戲
            Blue_move(map); // 藍方繼續移動
        }
    }
}
/*
map[y_1][x_1] == 0：表示該位置是特殊標記，不能移動。
map[y_1][x_1] >= 'A' && map[y_1][x_1] <= 'Z'：表示該位置有藍方的棋子
map[y_1][x_1] >= 'a' && map[y_1][x_1] <= 'z'：表示該位置有紅方的棋子
*/

// 遊戲部分拼裝+棋盤初始化
void Start_game() { 
    int map[19][18]=
    // 初始化棋盤。map是一個19x18的數組，代表棋盤上的位置和棋子。
    // 0-9 為紅方的棋子，10-19 為藍方的棋子，'a'-'z' 和 'A'-'Z' 代表不同的棋子。

    /*數字 101 到 110 代表棋盤上的某些特定位置*/
    /* 1 代表棋盤上的空格或障礙物*/
    /*0*/{{101,'C',1,'D',1,'E',1,'F',1,'G',1,'F',1,'E',1,'D',1,'C'},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*2*/{103,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*4*/{104,0,1,'B',1,0,1,0,1,0,1,0,1,0,1,'B',1,0},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*6*/{105,'A',1,0,1,'A',1,0,1,'A',1,0,1,'A',1,0,1,'A'},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*8*/{106,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    { 102,7,6,6,2,6,3,6,6,6,6,6,4,6,5,6,6,7 },
    /*10*/{107,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*12*/{108,'a',1,0,1,'a',1,0,1,'a',1,0,1,'a',1,0,1,'a'},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*14*/{109,0,1,'b',1,0,1,0,1,0,1,0,1,0,1,'b',1,0},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*16*/{110,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {102,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    /*18*/{102,'c',1,'d',1,'p',1,'s',1,'z',1,'s',1,'p',1,'d',1,'c'}};
    while(1)
    { 
        Draw_map(map); // 畫出當前的棋盤
        Red_move(map); // 紅方移動(每次紅方移動後，棋盤會重新畫出來，然後等待紅方下一步移動)
    }
    /*每次紅方移動之後，都會呼叫 Blue_move(map) 函數進行藍方的移動,只要一方下完就會叫另一方移動並且重新顯示畫面*/
}
/*
- 101-110: 棋盤邊框。
- 0: 可以放棋子的地方。
- 1: 棋盤的邊界。
- 2: 表示「楚」字，用於楚河漢界的位置，區分兩個陣營的區域。
- 3: 表示「河」字，與「楚」字一起組成「楚河」。
- 4: 表示「漢」字，用於楚河漢界的位置，區分兩個陣營的區域。
- 5: 表示「界」字，與「漢」字一起組成「漢界」。
- 6: 空白區域。
- 7: 星星。
*/