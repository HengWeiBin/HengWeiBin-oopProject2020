# Candy Crush Saga (OOP Project2020, by C++)

協作組員 [Stella](https://github.com/stelfalen)

## 動機
> 全球類似於寶石方塊的游戲可説是相當的多，但糖果傳奇(Candy Crush Saga) 這款游戲有種神奇的魔力，他用鮮艷的顔色、精緻的特效，剛推出一個月就吸引了超過一千萬名用戶下載。

> 考慮到我們兩位組員的生活情況，平時比較少時間接觸故事性、RPG或者是玩法複雜需要很多時間來玩的游戲。這款游戲比起很多流行的小游戲，這款游戲基本玩法的演算相較簡單，實作出來所需的時間較爲彈性，可以根據我們擁有的時間來決定擴充多少種游戲玩法和特效。

## 游戲介紹
### 游戲説明
1. 點擊兩個相鄰的糖果可以進行交換，當3顆相同顔色的糖果連成一綫時會被消除。
   > ![HowtoPlay1](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/3candy.gif)
3. 以不同的形式配對4~5顆糖果可以產生出特別（强化）的糖果。
   > ![HowtoPlay2](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/4candy.gif)
   > ![HowtoPlay3](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/5candy.gif)
   > ![HowtoPlay4](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/5candyL.gif)
4. 兩顆特別（强化）的糖果互相交換會有特別的爆炸效果。
   > ![SpecialEffect1](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/doublesuper.gif)
   > ![SpecialEffect2](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/superline.gif)
   > ![SpecialEffect3](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/line+pack.gif)
6. 進入游戲後，左邊的計分板(Score Board)上會顯示當前的游戲模式、剩餘步數、當前纍計分數
   1. Target 分數挑戰 ： 當纍計分數達到目標便會自動通關，第一次游戲的目標為第1顆星，≥第二次游戲的目標為2星/3星/歷史最高分。
      > ![HowtoPlayScoreBoard1](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/howtoplay_scoreboard1.png)
   3. 果凍挑戰：在指定位置消除糖果可以破壞該位置的果凍，消除場上所有果凍即可通關
      > ![HowtoPlayScoreBoard2](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/howtoplay_scoreboard2.png)
7. 秘技/作弊：
   1. 選關界面：長按鍵盤上的F1不放，點擊任何未解鎖關卡可以直接進入游戲
   2.	游戲界面：長安鍵盤上的F1不放，點擊場上任何糖果可以切換强化效果

### 程式架構
> ![Structure](https://github.com/HengWeiBin/HengWeiBin-oopProject2020/blob/master/readme/structure.png)

### 游戲運作方式
> 開啓游戲的時候程式會先讀取全部游戲檔案然後將其保存到Stage陣列中，正常關閉游戲的時候Stage會將所有游戲數據重新保存會檔案中。

> 進入游戲後游戲狀態細分為4個狀態：
  1. 初始化狀態：
     1. 進入游戲的時候糖果的呈現方式有兩種：
        1. 全部靜止：載入的時候程式會預先讓糖果掉落、消除且不算分數、不顯示動畫、不播放聲音，當全部糖果靜止後才算載入完成，顯示游戲畫面。
        2. 從指定生成區掉落：糖果會與生成區產生，然後優先直綫掉落，當當前的行陣列填滿後，如果左右的區域爲空，且其最頂端沒有生成區，當過會掉落到側邊。
  2. 可操作狀態：玩家可自由操作，交換、消除糖果、纍計分數直到達標/達到步數上限/退出游戲
  3. 結尾狀態：
     1. 玩家達到通關條件：剩餘步數將轉換爲獎勵點數，將場上的糖果隨機變成綫條糖果，引爆場上所有强化糖果直到沒有强化糖果且靜止後結束游戲。
     2. 未達到通關條件：延遲數秒後結束游戲
  4. 游戲結束狀態：切換到CGameStateOver

> 我們實作出的游戲模式有兩種：
  1. 目標分數挑戰 ： 當纍計分數達到目標便會自動通關，第一次游戲的目標為第1顆星，≥第二次游戲的目標為2星/3星/歷史最高分。
  2. 果凍挑戰：游戲初始化時會自動計算場上剩餘果凍的數量

> 游戲檢測可消除糖果的方式是依序從糖果陣列中將相鄰且形態相同的糖果收集到陣列中，將這些糖果分類成行與列，再進行分析，最後得出是否消除糖果，是否產生强化糖果。

> 游戲結束後，GameArea會將ScoreBoard的部分數據暫存到Stage以供CGameStateOver讀取。
