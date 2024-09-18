# Qt-Miku-Parkour
用qt写一个简单2D跑酷小游戏，实现行走，跑动，跳越，滚翻

## 使用方法
1. 下载本项目到本地(用git克隆或者直接下载压缩包)
2. 用Qt5打开ParkourProject.pro文件
3. 编译运行

ps: 可以在右侧的 Release 中下载编译打包好的exe文件

## 实现原理
1. 引用了状态机和动画机的概念，对应的类为 State, Animation
2. 自己设计了刚体 Rigidbody 检测碰撞，碰撞检测效率可能有点慢，是一个一个像素找的，没有进行优化。
3. 游戏贴图来自MMD，通过绿幕加抠图得到序列帧。

## 需要注意的地方
1. 像素和位移多用是绝对值，仅在windows上面开发，其它系统可能还要调位移单位像素。
2. 刷新率可以自行调整，动画为了衔接没有把spritesheet中的全部图用上，把定时器调快一点就能提高帧率了，不过移动速度（每步位移）也要相应调整

# 启动界面
![main](https://github.com/Movelocity/Qt-Miku-Parkour/blob/main/demo1.png)

# 游戏界面
![play](https://github.com/Movelocity/Qt-Miku-Parkour/blob/main/demo2.png)

本项目使用MIT协议，随便大家改，不用问我的。

遇到技术问题可以提 Issue
