# 服务端
## 构成
主要由<br>
- Server.class：服务类，接收socket连接，创建session实例，并分配到一个新的Game实例中<br>
- Game.class：游戏处理类，管理两个session实例，从客户端接收到消息，处理后向客户端发送消息<br>
- Session.class：会话类，管理socket的连接，接收，发送，断开，判断是否断开等<br>
- Godata.class：数据类，规定发送和接收的数据<br>
- Chess.class：棋盘类，服务端存储的棋盘数据，防止客户端发送异常棋子位置而无法判断该棋子位置是否合法<br>
## 预览为部分收发消息log
![](https://i.loli.net/2018/07/25/5b5829659464f.png "server simple log")