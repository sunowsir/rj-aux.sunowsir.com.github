# 锐捷有线认证，Linux图形界面客户端

> 使用qt平台，部分采用Dtk框架，构建图形界面。
> 通过QProcess直接调用原生程序。
> 未对锐捷源生linux客户端程序进行任何实质性修改。


## 展示
![showPic](http://yanxuan.nosdn.127.net/53fba482d8b043c0088f783924ec342b.png)


## 开发计划 

- [x] 登录界面
- [x] dock支持
- [x] 认证主逻辑
- [x] 状态信息显示
- [x] 信息记忆
- [x] 拦截重复启动
- [x] 认证成功信息界面


# 依赖环境

* g++
* gdb
* qt
* dtk


## 编译

```bash
sudo apt-get install git
git clone https://github.com/sunowsir/rj-aux.git
cd rj-aux/
mkdir build
cd build/
qmake ..
make 

```

*  手动用开发环境构建后是无法直接使用，需要将构建生成的可执行程序以及`script/`下的脚本一同放到锐捷源生程序目录下.
* 打包的deb安装包中集成了锐捷源程序，安装后可以直接使用。

## 声明

* 本软件采用GPLv3协议开源，不包括锐捷源生程序，并且本仓库中也不包含锐捷源生程序，
