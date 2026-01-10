// time_manager.h
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include "ntp_client.h"

// 时间同步回调函数类型
typedef void (*time_sync_cb_t)(const char* time_str, time_t timestamp);

// 初始化时间管理器
void time_manager_init(void);

// 同步NTP时间
int sync_ntp_time(const char* ntp_server, time_sync_cb_t callback);

// 获取当前时间字符串
const char* get_current_time_str(void);

// 获取当前时间戳
time_t get_current_timestamp(void);

// 更新本地时间（每秒调用）
void update_local_time(void);

// 设置时区
void tzset(void);

#ifdef __cplusplus
}
#endif

#endif
