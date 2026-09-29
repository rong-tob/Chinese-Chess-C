void Show_menu();//繪製菜單
void Get_command();//得到主菜單命令
void Out_game();//退出遊戲界面
void Instruction(); //顯示遊戲說明 
void Start_game(); //遊戲部分拼裝 
void HighlightOption(int option);

void Gap_hint();//該座標沒有棋子提醒
void Error_hint();//操作錯誤時返回提示 
void Object_hint();//擅動對方棋子警告 
void Self_hint();//吃自己的子警告 
void Rule_hint();//棋子的移動不符合棋法警告 

void Draw_map(int map[19][18]);//繪製棋盤和棋子 
void Go_on(int map[19][18]);//判斷遊戲是否結束
void Red_move(int map[19][18]);//實現紅方玩家對棋子的移動
void Blue_move(int map[19][18]);//實現藍方玩家對棋子的移動
void Red_rule(int map[19][18], int y_1, int x_1, int y_2, int x_2);//判斷紅棋移動是否合法
void Blue_rule(int map[19][18], int y_1, int x_1, int y_2, int x_2);//判斷藍棋移動是否合法
