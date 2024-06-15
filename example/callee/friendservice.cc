#include <iostream>
#include <string>
#include <vector>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "logger.h"

class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        std::cout << "do GetFriendList service!" << std::endl;
        std::vector<std::string> friend_list;
        friend_list.push_back("fitz");
        friend_list.push_back("coulson");
        return friend_list;
    }
    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController *controller,
                        const ::fixbug::GetFriendsListRequest *request,
                        ::fixbug::GetFriendsListResponse *response,
                        ::google::protobuf::Closure *done)
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friend_list = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (std::string &name : friend_list)
        {
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
};

int main(int argc, char **argv)
{
    LOG_INFO("first log message!");
    LOG_ERROR("%s:%s%d", __FILE__, __FUNCTION__, __LINE__);

    // 调用框架初始化操作
    MprpcApplication::Init(argc, argv);
    // 把UserService对象发布到rpc节点
    RpcProvider provider;
    provider.NotifyService(new FriendService());
    // 启动一个rpc服务发布节点。Run以后，进程进入阻塞，等待远程的rpc调用请求
    provider.Run();
    return 0;
}