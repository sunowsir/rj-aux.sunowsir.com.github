# 锐捷有线认证，Linux图形界面客户端

> 使用qt平台，部分采用Dtk框架，构建图形界面。
> 通过QProcess直接调用原生程序。
> 未对锐捷官方linux客户端程序进行任何实质性修改。


## 展示
![showPic](./showPic.png)


## 开发计划 

- [x] 登录界面
- [x] dock支持
- [x] 认证主逻辑
- [x] 状态信息显示
- [x] 信息记忆
- [x] 拦截重复启动
- [x] 认证成功信息界面
- [x] 软件启动自动登陆选项
- [ ] 使用Dtk框架构建Deepin风格UI

# 依赖环境

* g++
* gdb
* qt
* dtk

```bash

sudo apt install -y g++ gdb make qtchooser qt5-qmake qt5-default gdb cmake 

```


## 编译

```bash
sudo apt-get install git
git clone https://github.com/sunowsir/rj-aux.git
cd rj-aux/
mkdir build
cd build/
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../
make 
```

*  手动用开发环境构建后无法直接使用，需要将构建生成的可执行程序、`script/`下的脚本以及policy文件一同放到锐捷官方程序目录下。

## 打包
> 打包的deb安装包中集成了锐捷官方程序、增加了缺少的必要的动态链接库，安装后可以直接使用。
 1. 按照上述编译流程进行编译
 2. `mkdir rj-aux.sunowsir.com.github`，# 创建构建目录
 3. `cp -r ./build/rj-aux ./opt/rjsupplicant-aux/` # 将编译生成的二进制文件拷贝到软件目录
 4. 插上学校校园网网线打开浏览器会弹出下载界面，下载锐捷linux客户端(或通过其他下载渠道)，解压到当前项目目录中
 5. `cp -r ./RG_SU_For_Linux_4_90/rjsupplicant/x64/* ./opt/rjsupplicant-aux/` # 将锐捷程序以及其他配置文件拷贝到软件目录
 6. `cp -r ./build/rj-aux ./opt/rjsupplicant-aux/`
 7. `cp -r ./lib ./opt ./usr ./DEBIAN ./rj-aux.sunowsir.com.github/` # 将软件各个文件拷贝到打包目录
 8. `dpkg-deb -b ./rj-aux.sunowsir.com.github/` # 打包



## 下载

详情见: [releases](https://github.com/sunowsir/rj-aux/releases)

## 声明

*  该项目采用GPLv3协议开源。
*  源码仓库中不包含任何锐捷官方程序。


