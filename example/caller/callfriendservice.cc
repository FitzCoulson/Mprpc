#include <iostream>
#include "mprpcapplication.h"
#include "friend.pb.h"

int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mprpc框架享受rpc服务调用，一定需要要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法getfriendslist
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法启动请求参数
    fixbug::GetFriendsListRequest request;
    request.set_userid(2000);
    // rpc方法的响应
    fixbug::GetFriendsListResponse response;
    // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送
    //  发起rpc方法的调用 同步的rpc调用过程 MprpcChannel::callmethod
    MprpcController controller;
    stub.GetFriendsList(&controller, &request, &response, nullptr);
    // 一次rpc调用完成，读调用的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (response.result().errcode() == 0)
        {
            std::cout << "rpc get friends list response success!" << std::endl;
            for (int i = 0; i < response.friends_size(); ++i)
            {
                std::cout << "index:" << (i + 1) << " name:" << response.friends(i) << std::endl;
            }
        }
        else
        {
            std::cout << "rpc get friends list response error:" << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}