# 客户端
## 构成
- Client：管理客户端与服务端的连接，socket通信以及消息解析<br>
- Main：多线程下控制unity线程中物体的显示与改变<br>
- Chess_set：控制客户端下棋，棋盘显示等，并把下棋动作产生的消息传递给Client管理<br>
- OnXXX：挂在各UI控件上的控制脚本，用于控制游戏流程<br>
## 预览
![](https://i.loli.net/2018/07/25/5b5829292cb4f.png "start")<br>
![](https://i.loli.net/2018/07/25/5b58293d784ed.png "connected")<br>
![](https://i.loli.net/2018/07/25/5b58294611024.png "janken")<br>
![](https://i.loli.net/2018/07/25/5b58294dd79e2.png "gaming")<br>
![](https://i.loli.net/2018/07/25/5b582956a32d5.png "game over")<br>
![](https://i.loli.net/2018/07/25/5b582960b3e29.png "restart")<br>
![](https://i.loli.net/2018/07/25/5b5829659464f.png "server simple log")<br>