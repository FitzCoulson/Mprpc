# 小型RPC库，基于muduo和protobuf
## GetStart
克隆库
```sh
git clone https://github.com/FitzCoulson/Mprpc.git
```

编译库
```sh
cd Mprpc
./autobuild.sh
```

静态库和头文件存放在lib目录下

## Example
```sh
cd ./bin
./provider -i test.conf
./consumer -i test.conf
```