/*
 * Description: 
 *     History: yang@haipo.me, 2017/03/16, create
 */

# ifndef _ME_MARKET_H_
# define _ME_MARKET_H_

# include "me_config.h"

extern uint64_t order_id_start;
extern uint64_t deals_id_start;
/**
 * @brief order的结构,包含
 * 1.   id: 订单的id
 * 2.   type: 订单的类型(e.g. 市价单,限价单)
 * 3.   side: 订单的方向(e.g. 买or卖)
 * 4.   create_time: 订单的创建时间
 * 5.   update_time: 订单的修改时间
 * 6.   user_id: 拥有着的id
 * 7.   market: 市场(e.g. "BTCUSDT")
 * 8.   source: 来源(e.g. "ios")
 * 9.   price: 订单的挂单价格
 * 10.  amount: 订单的量
 * 11.  taker_fee: taker的手续费
 * 12.  maker_fee: maker的手续费
 * 13.  left: 订单还有多少未完成(和amount有关)
 * 14.  freeze: 订单有多少量是冻住的
 * 15.  deal_stock: 成交了多少的量
 * 16.  deal_money: 成交了`deal_stock`这么多,花了多少钱
 * 17.  deal_fee: 成交了`deal_stock`这么多,花了多少手续费
 */
typedef struct order_t {
    uint64_t        id; 
    uint32_t        type;
    uint32_t        side;
    double          create_time;
    double          update_time;
    uint32_t        user_id;
    char            *market;
    char            *source;
    mpd_t           *price;
    mpd_t           *amount;
    mpd_t           *taker_fee;
    mpd_t           *maker_fee;
    mpd_t           *left;
    mpd_t           *freeze;
    mpd_t           *deal_stock;
    mpd_t           *deal_money;
    mpd_t           *deal_fee;
} order_t;

/**
 * @brief 市场资讯
 * 1.  name: 市场的名称(e.g. BTCUSDT)
 * 2.  stock: 交易物名字(e.g. BTC)
 * 3.  money: 结算币名字(e.g. USDT)
 * 4.  stock_prec: stock的精度
 * 5.  money_prec: money的精度
 * 6.  fee_prec: 手续费的精度
 * 7.  min_amount: 最小交易量
 * 8.  orders:
 * 9.  users:
 * 10. asks: 当前市场的挂单的买价
 * 11. bids: 当前市场的挂单的卖钱
 */
typedef struct market_t {
    char            *name;
    char            *stock;
    char            *money;

    int             stock_prec;
    int             money_prec;
    int             fee_prec;
    mpd_t           *min_amount;

    dict_t          *orders;
    dict_t          *users;

    skiplist_t      *asks;
    skiplist_t      *bids;
} market_t;

market_t *market_create(struct market *conf);
int market_get_status(market_t *m, size_t *ask_count, mpd_t *ask_amount, size_t *bid_count, mpd_t *bid_amount);

int market_put_limit_order(bool real, json_t **result, market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *price, mpd_t *taker_fee, mpd_t *maker_fee, const char *source);
int market_put_market_order(bool real, json_t **result, market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *taker_fee, const char *source);
int market_cancel_order(bool real, json_t **result, market_t *m, order_t *order);

int market_put_order(market_t *m, order_t *order);

json_t *get_order_info(order_t *order);
order_t *market_get_order(market_t *m, uint64_t id);
skiplist_t *market_get_order_list(market_t *m, uint32_t user_id);

sds market_status(sds reply);

# endif

