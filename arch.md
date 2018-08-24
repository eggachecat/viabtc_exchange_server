<!-- TOC -->

- [1. dict](#1-dict)
    - [1.1. skiplist](#11-skiplist)
        - [1.1.1. des](#111-des)
- [2. utils](#2-utils)
    - [2.1. ut_rpc_clt](#21-utrpcclt)
        - [2.1.1. [struct]rpc_clt_type](#211-structrpcclttype)
            - [des](#des)
        - [2.1.2. [struct]rpc_clt](#212-structrpcclt)
        - [2.1.3. [func]rpc_clt_create](#213-funcrpccltcreate)
            - [des](#des)
- [3. accesshttp](#3-accesshttp)
    - [3.1. ah_server](#31-ahserver)
    - [3.2. [func]init_server](#32-funcinitserver)
            - [des](#des)
        - [3.2.1. [func]rpc_clt_create](#321-funcrpccltcreate)
            - [des](#des)
        - [3.2.2. [func]on_http_request](#322-funconhttprequest)
            - [des](#des)
- [4. matchengine](#4-matchengine)
    - [4.1. me_server](#41-meserver)
        - [4.1.1. [func]init_server](#411-funcinitserver)
        - [4.1.2. [func]svr_on_recv_pkg](#412-funcsvronrecvpkg)
        - [4.1.3. [func]on_cmd_order_put_limit](#413-funconcmdorderputlimit)
            - [des](#des)
    - [4.2. me_market](#42-memarket)
        - [4.2.1. [struct] order_t](#421-struct-ordert)
            - [des](#des)
        - [4.2.2. [struct] market_t](#422-struct-markett)
            - [des](#des)
        - [4.2.3. [func]market_create](#423-funcmarketcreate)
            - [des](#des)
        - [4.2.4. [func]market_put_limit_order](#424-funcmarketputlimitorder)
            - [des](#des)
        - [4.2.5. [func]execute_limit_ask_order](#425-funcexecutelimitaskorder)
            - [des](#des)
        - [4.2.6. wtf](#426-wtf)
    - [4.3. me_balance](#43-mebalance)
        - [4.3.1. [func]balance_get](#431-funcbalanceget)
            - [des](#des)
        - [4.3.2. [func]balance_add](#432-funcbalanceadd)
            - [des](#des)
        - [4.3.3. [func]balance_set](#433-funcbalanceset)
            - [des](#des)
    - [4.4. me_config](#44-meconfig)
        - [4.4.1. [struct]asset](#441-structasset)
            - [des](#des)
        - [4.4.2. [struct]market](#442-structmarket)
            - [des](#des)
    - [4.5. me_load](#45-meload)
        - [4.5.1. [func]load_balance](#451-funcloadbalance)
            - [des](#des)
        - [4.5.2. [func]read_config_from_json](#452-funcreadconfigfromjson)
            - [des](#des)
    - [4.6. me_persist](#46-mepersist)
        - [4.6.1. [func]dump_to_db](#461-funcdumptodb)
            - [des](#des)
    - [4.7. me_history](#47-mehistory)
        - [4.7.1. [func]append_user_order](#471-funcappenduserorder)
            - [des](#des)
            - [[trick]](#trick)

<!-- /TOC -->

# 1. dict
## 1.1. skiplist
### 1.1.1. des
    优化结构(搜寻更快)
    order book的结构

# 2. utils
## 2.1. ut_rpc_clt
### 2.1.1. [struct]rpc_clt_type
#### des
    定义了所有的client所需要的函数
    `on_connect` - 连上了要做什么
    `on_recv_pkg`
    `on_recv_fd`

### 2.1.2. [struct]rpc_clt


### 2.1.3. [func]rpc_clt_create
#### des
    创建一个clt

# 3. accesshttp
## 3.1. ah_server
## 3.2. [func]init_server
#### des
    从`config.json`读取各个服务器的资讯(名称、地址等等)读取到`settings`中
    初始化服务器,调用`init_methods_handler`注册服务


### 3.2.1. [func]rpc_clt_create
#### des
    In charge of register router with handler

### 3.2.2. [func]on_http_request
#### des
    处理请求， 从`init_methods_handler`中所定义的map`methods`找到对应的方法来处理
    使用 `rpc_clt_send(req->clt, &pkg);` 真正的发送请求


# 4. matchengine
## 4.1. me_server
### 4.1.1. [func]init_server
    初始化服务器(会从accesshttp转发来)
```c
    type.on_recv_pkg = svr_on_recv_pkg;
    type.on_new_connection = svr_on_new_connection;
    type.on_connection_close = svr_on_connection_close;
```
    来定义处理收发

### 4.1.2. [func]svr_on_recv_pkg
    真正来的请求做什么

### 4.1.3. [func]on_cmd_order_put_limit
#### des
    收到`order.put_limit`请求做的事情啊
    先解析，都ok呼叫`market_put_limit_order`(#me)

## 4.2. me_market
    比较核心的一个文件,所有的指令在这边执行(各种`on_cmd_`)
### 4.2.1. [struct] order_t
#### des
    传说中`订单`的结构

### 4.2.2. [struct] market_t
#### des
    传说中`市场`的结构

### 4.2.3. [func]market_create
#### des
    注册`market`资讯

### 4.2.4. [func]market_put_limit_order
#### des
    一系列判断呼叫`execute_limit_ask_order`

### 4.2.5. [func]execute_limit_ask_order
#### des
    真正执行limit_ask的请求
    在skiplist的结构上
### 4.2.6. wtf
    为什么永远`return 0`???

## 4.3. me_balance
    控制`balance`
    `balance`的index是`user_id, type`
    初始化的可能参考`me_load`

### 4.3.1. [func]balance_get
#### des
    得到用户的某些资产可用余额

### 4.3.2. [func]balance_add
#### des
    心中用户的某些资产

### 4.3.3. [func]balance_set
#### des
    设定用户的某些资产可用余额

## 4.4. me_config
### 4.4.1. [struct]asset
#### des
    是`asset_t`的json的config

### 4.4.2. [struct]market
#### des
    是`market_t`的json的config

## 4.5. me_load
### 4.5.1. [func]load_balance
#### des
    从数据库中把各个的balance都load出来

### 4.5.2. [func]read_config_from_json
#### des
    读取json的函数,把结果读取到`settings`里(全局变量)
    其他的初始化依赖于`settings`

## 4.6. me_persist
### 4.6.1. [func]dump_to_db
#### des
    呼叫`dump_order_to_db`和`dump_balance_to_db`以及`update_slice_history`持久化

## 4.7. me_history
### 4.7.1. [func]append_user_order
#### des
    负责储存user的order
#### [trick]
    这边用hash将用户分到不同的table当中