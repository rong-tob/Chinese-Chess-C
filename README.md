# Chinese Chess Game in C

以 **C 語言**開發的雙人中國象棋遊戲，將中國象棋的棋盤、棋子移動與吃子規則轉換為程式邏輯，並透過 Windows Console 建立可進行雙人對弈的互動式遊戲。

## Features

- 雙人中國象棋對弈
- 棋盤與棋子顯示
- 紅、藍雙方回合控制
- 各棋種移動與吃子規則判定
- 路徑障礙判斷
- 違規操作警告提示
- 遊戲勝負判定
- Windows Console 互動介面與音效

## Program Structure

- `main.c`：程式進入點與遊戲初始化
- `core.c`：主選單、棋盤顯示、玩家操作與遊戲流程
- `rule.c`：各棋種移動與吃子規則判定
- `core.h`：遊戲核心相關函式宣告
- `rule.h`：棋規相關函式宣告

## Rule Implementation

程式分別實作兵／卒、炮、車、馬、象、士、將／帥的移動規則，並針對不同棋種判斷移動方式、路徑障礙與吃子條件。

例如炮在吃子時，會計算起點與目標棋子之間的棋子數量；馬則除了判斷「日」字型移動外，也會檢查是否存在「拐馬腳」的情況。

## Development Environment

- **Language:** C
- **IDE:** Code::Blocks
- **Platform:** Windows
- **Interface:** Windows Console
