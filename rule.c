#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rule.h"
#include "core.h"

// 通用移動規則
void Move_rule(int map[19][18], int y_1, int x_1, int y_2, int x_2) {
  //x_1,y_1代表原先的座標，x_2,y_2代表移動後的座標
	switch (map[y_1][x_1]) {
		case 'a': Red_pawn(map, y_1, x_1, y_2, x_2); break;  // 紅兵
		case 'A': Blue_pawn(map, y_1, x_1, y_2, x_2); break; // 藍卒
		case 'c': Red_car(map, y_1, x_1, y_2, x_2); break;   // 紅車
		case 'C': Blue_car(map, y_1, x_1, y_2, x_2); break;  // 黑車
		case 'd': Red_horse(map, y_1, x_1, y_2, x_2); break; // 紅馬
		case 'D': Blue_horse(map, y_1, x_1, y_2, x_2); break; // 黑馬
		case 'p': Red_elephant(map, y_1, x_1, y_2, x_2); break; // 紅象
		case 'E': Blue_elephant(map, y_1, x_1, y_2, x_2); break; // 黑象
		case 's': Red_man(map, y_1, x_1, y_2, x_2); break;   // 紅士
		case 'F': Blue_man(map, y_1, x_1, y_2, x_2); break;  // 黑士
		case 'z': Red_boss(map, y_1, x_1, y_2, x_2); break;  // 紅帥
		case 'G': Blue_boss(map, y_1, x_1, y_2, x_2); break; // 黑將
		case 'b': Red_gun(map, y_1, x_1, y_2, x_2); break;   // 紅炮
		case 'B': Blue_gun(map, y_1, x_1, y_2, x_2); break;  // 黑炮
	}
}

//紅方 兵 的規則 
void Red_pawn(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  if (y_1 == 10 || y_1 == 12) { // 在己方棋盤時的情況
    if (x_1 == x_2 && y_2 == (y_1 - 2)) { //只能前進一格 不能後退
      map[y_2][x_2] = map[y_1][x_1]; //原本在位置 (y_1, x_1) 的棋子移動到位置 (y_2, x_2)
      map[y_1][x_1] = 0; //棋子移走了所以將原座標 (y_1, x_1) 設為 0，表該位置現在是空的
      Draw_map(map); Go_on(map); Blue_move(map); //先繪製新地圖，再檢查遊戲是否繼續，若無錯誤再換藍棋移動
    } else {//不符合規則
      Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);// 棋法警告/繪製新的棋盤和棋子/判斷結束沒/再一次紅棋移動
    }
  } else { // 進入對方棋盤後的情況
    if ((y_2 == (y_1 - 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 - 2)) || (y_2 == y_1 && x_2 == (x_1 + 2))) { //可以往前或左右移動一格
      map[y_2][x_2] = map[y_1][x_1];
      map[y_1][x_1] = 0;
      Draw_map(map); Go_on(map); Blue_move(map);
    } else { //不符合規則
      Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
    if ((y_2 == (y_1 - 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 - 2))) { //可以往前或左右移動一格
      map[y_2][x_2] = map[y_1][x_1];
    }
  }
}
}

//藍方 卒 的規則
void Blue_pawn(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  if (y_1 == 6 || y_1 == 8) { // 在己方棋盤時的情況
    if (x_1 == x_2 && y_2 == (y_1 + 2)) { // 只能前進一格 不能後退
      map[y_2][x_2] = map[y_1][x_1]; //原本在位置 (y_1, x_1) 的棋子移動到位置 (y_2, x_2)
      map[y_1][x_1] = 0; //棋子移走了所以將原座標 (y_1, x_1) 設為 0，表該位置現在是空的
      Draw_map(map); Go_on(map); Red_move(map); //先繪製新地圖，再檢查遊戲是否繼續，若無錯誤再換紅棋移動
    } else { //不符合規則
      Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 棋法警告/繪製新的棋盤和棋子/判斷結束沒/再一次藍棋移動
    }
  } else { // 進入對方棋盤後的情況
    if ((y_2 == (y_1 + 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 - 2)) || (y_2 == y_1 && x_2 == (x_1 + 2))) { // 可以往前或左右移動一格
      map[y_2][x_2] = map[y_1][x_1]; //原本在位置 (y_1, x_1) 的棋子移動到位置 (y_2, x_2)
      map[y_1][x_1] = 0; //棋子移走了所以將原座標 (y_1, x_1) 設為 0，表該位置現在是空的
      Draw_map(map); Go_on(map); Red_move(map); //先繪製新地圖，再檢查遊戲是否繼續，若無錯誤再換紅棋移動
    } else {
      Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 棋法警告/繪製新的棋盤和棋子/判斷結束沒/再一次藍棋移動
    }
  }
}

//紅方 炮 的規則
void Red_gun(int map[19][18], int y_1, int x_1, int y_2, int x_2) {
    int i, j, flag = 0, n = 0;

    if (y_1 == y_2) { // 左右移動的情況
        if (x_2 > x_1) { // 向右移動
            for (j = x_1 + 1; j < x_2; j++) { // 檢查砲的移動路徑
                if (map[y_1][j] == 0 || map[y_1][j] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Blue_move(map); // 繪製棋盤並進行藍方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Red_move(map); // 提示規則錯誤並再次進行紅方移動
            }
        } else { // 向左移動
            for (j = x_1 - 1; j > x_2; j--) { // 檢查砲的移動路徑
                if (map[y_1][j] == 0 || map[y_1][j] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Blue_move(map); // 繪製棋盤並進行藍方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Red_move(map); // 提示規則錯誤並再進行紅方移動
            }
        }
    } else if (x_1 == x_2) { // 上下移動的情況
        if (y_2 > y_1) { // 向下移動
            for (i = y_1 + 1; i < y_2; i++) { // 檢查砲的移動路徑
                if (map[i][x_1] == 0 || map[i][x_1] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Blue_move(map); // 繪製棋盤並進行藍方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Red_move(map); // 提示規則錯誤並再進行紅方移動
            }
        } else { // 向上移動
            for (i = y_1 - 1; i > y_2; i--) { // 檢查砲的移動路徑
                if (map[i][x_1] == 0 || map[i][x_1] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Blue_move(map); // 繪製棋盤並進行藍方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Red_move(map); // 提示規則錯誤並進行紅方移動
            }
        }
    } else {
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map); // 提示規則錯誤並進行紅方移動
    }
}

//藍方 砲 的規則 
void Blue_gun(int map[19][18], int y_1, int x_1, int y_2, int x_2) {
    int i, j, flag = 0, n = 0;

    if (y_1 == y_2) { // 左右移動的情況
        if (x_2 > x_1) { // 向右移動
            for (j = x_1 + 1; j < x_2; j++) { // 檢查砲的移動路徑
                if (map[y_1][j] == 0 || map[y_1][j] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Red_move(map); // 繪製棋盤並進行紅方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 提示規則錯誤並再次進行藍方移動
            }
        } else { // 向左移動
            for (j = x_1 - 1; j > x_2; j--) { // 檢查砲的移動路徑
                if (map[y_1][j] == 0 || map[y_1][j] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Red_move(map); // 繪製棋盤並進行紅方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 提示規則錯誤並進行藍方移動
            }
        }
    } else if (x_1 == x_2) { // 上下移動的情況
        if (y_2 > y_1) { // 向下移動
            for (i = y_1 + 1; i < y_2; i++) { // 檢查砲的移動路徑
                if (map[i][x_1] == 0 || map[i][x_1] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Red_move(map); // 繪製棋盤並進行紅方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 提示規則錯誤並進行藍方移動
            }
        } else { // 向上移動
            for (i = y_1 - 1; i > y_2; i--) { // 檢查砲的移動路徑
                if (map[i][x_1] == 0 || map[i][x_1] == 1) continue; // 空白或邊界，繼續
                else { flag = 1; n++; } // 碰到棋子，設置flag，計數增加
            }
            if ((n == 1 && map[y_2][x_2] != 0 && map[y_2][x_2] != 1) || (n == 0 && (map[y_2][x_2] == 0 || map[y_2][x_2] == 1))) {
                // 如果路徑中有一個棋子，且目標是另一個棋子；或路徑中沒有棋子，且目標是空白
                map[y_2][x_2] = map[y_1][x_1]; // 砲移動到目標位置
                map[y_1][x_1] = 0; // 清空原位置
                Draw_map(map); Go_on(map); Red_move(map); // 繪製棋盤並進行紅方移動
            } else {
                Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 提示規則錯誤並進行藍方移動
            }
        }
    } else {
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map); // 提示規則錯誤並進行藍方移動
    }
}

//紅方 車 的規則
void Red_car(int map[19][18],int y_1,int x_1,int y_2,int x_2)
{
	int i,j,flag=0;//判斷有無障礙物

	if(y_1==y_2)//左右移動的情況
	{
		if(x_2>x_1)//向右移
		{
			for(j=x_1+1;j<x_2;j++)//限制車的走位（不能隔子打子）
			{
				if((map[y_1][j])==0||(map[y_1][j])==1)// 空白或邊界，繼續
				{continue;}
				else //有障礙物
				{flag=1;}
			}
			if(flag==0) { //正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Blue_move(map);
			}
			else { //錯誤(中間經過障礙物了)
				Rule_hint();Draw_map(map);Go_on(map);Red_move(map);
			}
		}
		else//向左移
		{
			for(j=x_1-1;j>x_2;j--)//限制車的走位（不能隔子打子）
			{
				if((map[y_1][j])==0||(map[y_1][j])==1)//空白或邊界，繼續
				{continue;}
				else//有障礙物
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Blue_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint();Draw_map(map);Go_on(map);Red_move(map);
			}
		}
	} 
	else if(x_1==x_2)//前後移動的情況
	{
		if(y_2>y_1)//向下移
		{
			for(i=y_1+1;i<y_2;i++)//限制車的走位（不能隔子打子）
			{
			if((map[i][x_1])==0||(map[i][x_1])==1||(map[i][x_1])==2||(map[i][x_1])==3||(map[i][x_1])==4||(map[i][x_1])==5||(map[i][x_1])==6||(map[i][x_1])==7)
				{continue;}//沒有經過棋子(楚河漢界略過)
			else
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Blue_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint(); Draw_map(map);Go_on(map);Red_move(map);
			}
		} 
		else//向上移
		{
			for(i=y_1-1;i>y_2;i--)//限制車的走位（不能隔子打子）
			{
			if((map[i][x_1])==0||(map[i][x_1])==1||(map[i][x_1])==2||(map[i][x_1])==3||(map[i][x_1])==4||(map[i][x_1])==5||(map[i][x_1])==6||(map[i][x_1])==7)
				{continue;}//沒有經過棋子(楚河漢界略過)
				else
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Blue_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint(); Draw_map(map);Go_on(map);Red_move(map);
			}
		}
	}
	else {//其他狀況為錯誤
		Rule_hint();Draw_map(map);Go_on(map);Red_move(map);
	}	
}

//藍方 車 的規則
void Blue_car(int map[19][18],int y_1,int x_1,int y_2,int x_2)
{

	int i,j,flag=0;

	if(y_1==y_2)//左右移動的情况
	{
		if(x_2>x_1)//向右移
		{
			for(j=x_1+1;j<x_2;j++)//限制車的走位（不能隔子打子）
			{
				if((map[y_1][j])==0||(map[y_1][j])==1)//空白或邊界，繼續
				{continue;}
				else//有障礙物
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Red_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint(); Draw_map(map);Go_on(map);Blue_move(map);
			}
		}
		else//左
		{
			for(j=x_1-1;j>x_2;j--)//限制車的走位（不能隔子打子）
			{
				if((map[y_1][j])==0||(map[y_1][j])==1)//空白或邊界，繼續
				{continue;}
				else//有障礙物
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Red_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint(); Draw_map(map);Go_on(map);Blue_move(map);
			}
		}
	} 
	else if(x_1==x_2)//上下移動的情况
	{
		if(y_2>y_1)//向下移
		{
			for(i=y_1+1;i<y_2;i++)//限制車的走位（不能隔子打子）
			{
				if((map[i][x_1])==0||(map[i][x_1])==1||(map[i][x_1])==2||(map[i][x_1])==3||(map[i][x_1])==4||(map[i][x_1])==5||(map[i][x_1])==6||(map[i][x_1])==7)
					{continue;}//沒有經過棋子(楚河漢界略過)
				else
					{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Red_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint();Draw_map(map);Go_on(map);Blue_move(map);
			}
		} 
		else//向上移
		{
			for(i=y_1-1;i>y_2;i--)//限制車的走位（不能隔子打子）
			{
			if((map[i][x_1])==0||(map[i][x_1])==1||(map[i][x_1])==2||(map[i][x_1])==3||(map[i][x_1])==4||(map[i][x_1])==5||(map[i][x_1])==6||(map[i][x_1])==7)
				{continue;}//沒有經過棋子(楚河漢界略過)
				else
				{flag=1;}
			}
			if(flag==0) {//正確
				map[y_2][x_2]=map[y_1][x_1];  map[y_1][x_1]=0;
				Draw_map(map);Go_on(map);Red_move(map);
			}
			else {//錯誤(中間經過障礙物了)
				Rule_hint(); Draw_map(map);Go_on(map);Blue_move(map);
			}
		}
	}
	else {//其他狀況為錯誤
		Rule_hint(); Draw_map(map);Go_on(map);Blue_move(map);
	} 
}

//紅方 馬 的規則
void Red_horse(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(20.0);
  double distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); // 馬的移動長度的平方
//馬走日字型 可過河
  if (sqrt(distance) == move_long) { // 計算並判斷馬的移動長度
    if (x_2 > x_1) { // 向右方移動的情況
      if (((x_2 - x_1) * (x_2 - x_1)) > ((y_2 - y_1) * (y_2 - y_1))) { // 右
        if (map[y_1][x_1 + 2] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else if ((y_2 < y_1) && ((x_2 - x_1) * (x_2 - x_1)) < ((y_2 - y_1) * (y_2 - y_1))) { // 往右上方移
        if (map[y_1 - 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else { // 往右下方移
        if (map[y_1 + 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      }
    } else { // 向左方移動的情況
      if (((x_2 - x_1) * (x_2 - x_1)) > ((y_2 - y_1) * (y_2 - y_1))) { // 左
        if (map[y_1][x_1 - 2] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else if ((y_2 < y_1) && ((x_2 - x_1) * (x_2 - x_1)) < ((y_2 - y_1) * (y_2 - y_1))) { // 向左上方移
        if (map[y_1 - 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else { // 向左下方移
        if (map[y_1 + 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      }
    }
  } else {//沒有走日字型
    Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
  }
}

//藍方 馬 的規則
void Blue_horse(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(20.0);
  double distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); // 馬的移動長度的平方

  if (sqrt(distance) == move_long) { // 計算並判斷馬的移動長度
    if (x_2 > x_1) { // 向右方移動的情況
      if (((x_2 - x_1) * (x_2 - x_1)) > ((y_2 - y_1) * (y_2 - y_1))) { // 向正右方移
        if (map[y_1][x_1 + 2] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else if ((y_2 < y_1) && ((x_2 - x_1) * (x_2 - x_1)) < ((y_2 - y_1) * (y_2 - y_1))) { // 向右上方移
        if (map[y_1 - 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else { // 向右下方移
        if (map[y_1 + 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      }
    } else { // 向左方移動的情況
      if (((x_2 - x_1) * (x_2 - x_1)) > ((y_2 - y_1) * (y_2 - y_1))) { // 向正左方移
        if (map[y_1][x_1 - 2] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else if ((y_2 < y_1) && ((x_2 - x_1) * (x_2 - x_1)) < ((y_2 - y_1) * (y_2 - y_1))) { // 向左上方移
        if (map[y_1 - 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else { // 左下方
        if (map[y_1 + 2][x_1] == 0) { // 判斷馬腳 0表示沒障礙物
          map[y_2][x_2] = map[y_1][x_1]; map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 拐馬腳
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      }
    }
  } else { //沒有走日字型
    Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
  }
}

//紅方 相 的規則
void Red_elephant(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(32.0);//走田字型
  double distance;

  if (y_2 >= 10) { // 限制相不能過河
    if (y_2 > y_1 && x_2 > x_1) { // 向右下方移動
      distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); // 相移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷相的移動長度
        if (map[y_1 + 2][x_1 + 2] == 0) { // 判斷相心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else {// 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else if (y_2 < y_1 && x_2 > x_1) { // 向右上方移動
      distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_1 - y_2) * (y_1 - y_2)); // 相移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷相的移動長度
        if (map[y_1 - 2][x_1 + 2] == 0) { // 判斷相心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
       } 
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else if (y_1 > y_2 && x_1 > x_2) { // 向左下方移動
      distance = ((x_1 - x_2) * (x_1 - x_2)) + ((y_1 - y_2) * (y_1 - y_2)); // 相移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷相的移動長度
        if (map[y_1 - 2][x_1 - 2] == 0) { // 判斷相心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else { // 不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else { // 向左上方移動
      distance = ((x_1 - x_2) * (x_1 - x_2)) + ((y_2 - y_1) * (y_2 - y_1)); // 相移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷相的移動長度
        if (map[y_1 + 2][x_1 - 2] == 0) { // 判斷相心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Blue_move(map);
        } else { // 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    }
  } else {
    Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
  }
}

//藍方 象 的規則
void Blue_elephant(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(32.0);//走田字型
  double distance;

  if (y_2 <= 8) { // 限制象不能過河
    if (y_2 > y_1 && x_2 > x_1) { // 向右下方移動
      distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); // 象移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷象的移動長度
        if (map[y_1 + 2][x_1 + 2] == 0) { // 判斷象心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else if (y_2 < y_1 && x_2 > x_1) { // 向右上方移動
      distance = ((x_2 - x_1) * (x_2 - x_1)) + ((y_1 - y_2) * (y_1 - y_2)); // 象移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷象的移動長度
        if (map[y_1 - 2][x_1 + 2] == 0) { // 判斷象心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else if (y_1 > y_2 && x_1 > x_2) { // 向左下方移動
      distance = ((x_1 - x_2) * (x_1 - x_2)) + ((y_1 - y_2) * (y_1 - y_2)); // 象移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷象的移動長度
        if (map[y_1 - 2][x_1 - 2] == 0) { // 判斷象心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else { // 向左上方移動
      distance = ((x_1 - x_2) * (x_1 - x_2)) + ((y_2 - y_1) * (y_2 - y_1)); // 象移動長度的平方
      if (sqrt(distance) == move_long) { // 計算並判斷象的移動長度
        if (map[y_1 + 2][x_1 - 2] == 0) { // 判斷象心(路上都沒障礙物)
          map[y_2][x_2] = map[y_1][x_1];
          map[y_1][x_1] = 0;
          Draw_map(map); Go_on(map); Red_move(map);
        } else {// 路上卡障礙物
          Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
        }
      } else {//不符合走在田字型內
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    }
  } else {
    Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
  }
}

//紅方 士 的規則
void Red_man(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(8.0);
  double flag;
  //九宮格內斜線行走
  if ((x_2 >= 7 && x_2 <= 11) && (y_2 >= 14 && y_2 <= 18)) { // 限制士不能出九宮
    if (y_2 > y_1 && x_2 > x_1) { // 向右下方移
      flag = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Blue_move(map);
      } else {//不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else if (y_2 < y_1 && x_2 > x_1) { // 向右上方移
      flag = ((x_2 - x_1) * (x_2 - x_1)) + ((y_1 - y_2) * (y_1 - y_2));//行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Blue_move(map);
      } else {//不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else if (y_1 > y_2 && x_1 > x_2) { // 向左下方移
      flag = ((x_1 - x_2) * (x_1 - x_2)) + ((y_1 - y_2) * (y_1 - y_2)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Blue_move(map);
      } else {//不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    } else { // 向左上方移
      flag = ((x_1 - x_2) * (x_1 - x_2)) + ((y_2 - y_1) * (y_2 - y_1)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Blue_move(map);
      } else {//不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
      }
    }
  } else {
    Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
  }
}

//藍方 仕 的規則
void Blue_man(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  double move_long = sqrt(8.0);
  double flag;
  //九宮格內斜線行走
  if ((x_2 >= 7 && x_2 <= 11) && (y_2 >= 0 && y_2 <= 4)) { // 限制仕不能出九宮
    if (y_2 > y_1 && x_2 > x_1) { // 右上方
      flag = ((x_2 - x_1) * (x_2 - x_1)) + ((y_2 - y_1) * (y_2 - y_1)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Red_move(map);
      } else { //不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else if (y_2 < y_1 && x_2 > x_1) { // 右下方
      flag = ((x_2 - x_1) * (x_2 - x_1)) + ((y_1 - y_2) * (y_1 - y_2)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Red_move(map);
      } else { //不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else if (y_1 > y_2 && x_1 > x_2) { // 左下方
      flag = ((x_1 - x_2) * (x_1 - x_2)) + ((y_1 - y_2) * (y_1 - y_2)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Red_move(map);
      } else { //不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    } else { // 左上方
      flag = ((x_1 - x_2) * (x_1 - x_2)) + ((y_2 - y_1) * (y_2 - y_1)); //行走距離
      if (sqrt(flag) == move_long) {
        map[y_2][x_2] = map[y_1][x_1]; //順利移動
        map[y_1][x_1] = 0;
        Draw_map(map); Go_on(map); Red_move(map);
      } else { //不符合規則
        Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
      }
    }
  } else {
    Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
  }
}

//紅方 帥 的規則
void Red_boss(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  if ((x_2 <= 11 && x_2 >= 7) && (y_2 <= 18 && y_2 >= 14)) { // 限制帥不能出九宮
  //帥可以挑前後左右走一步
    if ((y_2 == (y_1 + 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 + 2)) || (y_2 == (y_1 - 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 - 2))) {
      map[y_2][x_2] = map[y_1][x_1];
      map[y_1][x_1] = 0;
      Draw_map(map); Go_on(map); Blue_move(map);
    } else {//不符合規則
      Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
    }
  } else { //走出九宮格
    Rule_hint(); Draw_map(map); Go_on(map); Red_move(map);
  }
}

//藍方 將 的規則
void Blue_boss(int map[19][18], int y_1, int x_1, int y_2, int x_2) 
{
  if ((x_2 <= 11 && x_2 >= 7) && (y_2 <= 4 && y_2 >= 0)) { // 限制將不能出九宮
  //將可以挑前後左右走一步
    if ((y_2 == (y_1 + 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 + 2)) || (y_2 == (y_1 - 2) && x_1 == x_2) || (y_2 == y_1 && x_2 == (x_1 - 2))) {
      map[y_2][x_2] = map[y_1][x_1];
      map[y_1][x_1] = 0;
      Draw_map(map); Go_on(map); Red_move(map);
    } else {//不符合規則
      Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
    }
  } else {//走出九宮格
    Rule_hint(); Draw_map(map); Go_on(map); Blue_move(map);
  }
}
