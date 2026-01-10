// time_manager.c
#include "time_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>  // 添加这个头文件

static char time_str_buffer[64];
static time_t current_time = 0;
static struct tm current_tm;
static time_sync_cb_t sync_callback = NULL;
static int ntp_synced = 0;

// 添加全局时区标志
static int timezone_set = 0;

void time_manager_init(void) {
    // 设置中国标准时区（使用正确的TZ格式）
    setenv("TZ", "CST-8", 1);  // 注意：这里使用 CST-8
    tzset();
    timezone_set = 1;
    
    // 初始化时间
    time(&current_time);
    localtime_r(&current_time, &current_tm);
    
    // 格式化初始时间字符串
    strftime(time_str_buffer, sizeof(time_str_buffer), 
             "%Y-%m-%d %H:%M:%S", &current_tm);
}

// 修改：添加时区转换函数
static time_t apply_timezone_offset(time_t utc_time, int hours) {
    return utc_time + (hours * 3600);
}

int sync_ntp_time(const char* ntp_server, time_sync_cb_t callback) {
    sync_callback = callback;
    
    // 确保时区设置已生效
    if (!timezone_set) {
        setenv("TZ", "CST-8", 1);
        tzset();
        timezone_set = 1;
    }
    
    // 从NTP服务器获取时间（UTC时间）
    time_t ntp_time = get_ntp_time(ntp_server);
    
    if(ntp_time == (time_t)-1) {
        fprintf(stderr, "Failed to get NTP time\n");
        return -1;
    }
    
    // 调试信息：打印NTP返回的UTC时间
    struct tm utc_tm;
    gmtime_r(&ntp_time, &utc_tm);
    char utc_buffer[64];
    strftime(utc_buffer, sizeof(utc_buffer), "%Y-%m-%d %H:%M:%S UTC", &utc_tm);
    printf("NTP UTC time: %s\n", utc_buffer);
    
    // 设置系统时间（UTC时间戳）
    struct timeval tv = {
        .tv_sec = ntp_time,
        .tv_usec = 0
    };
    
    if(settimeofday(&tv, NULL) < 0) {
        perror("Failed to set system time");
        // 即使没有权限，我们也继续处理，只更新程序内部时间
        printf("Note: Cannot set system time (need root). Using internal time only.\n");
    }
    
    // 关键修改：更新当前时间
    current_time = ntp_time;  // 存储UTC时间
    // 使用localtime_r自动应用时区转换
    localtime_r(&current_time, &current_tm);
    ntp_synced = 1;
    
    // 调试信息：打印转换后的本地时间
    char local_buffer[64];
    strftime(local_buffer, sizeof(local_buffer), "%Y-%m-%d %H:%M:%S", &current_tm);
    printf("NTP local time (after conversion): %s\n", local_buffer);
    
    // 生成时间字符串（使用本地时间）
    strftime(time_str_buffer, sizeof(time_str_buffer), 
             "%Y-%m-%d %H:%M:%S", &current_tm);
    
    // 如果有回调函数，调用它
    if(sync_callback) {
        sync_callback(time_str_buffer, current_time);
    }
    
    printf("NTP time synchronized (local): %s\n", time_str_buffer);
    return 0;
}

// update_local_time函数
void update_local_time(void) {
    // 获取当前系统时间（UTC）
    time(&current_time);
    
    // 转换为本地时间（自动应用时区）
    localtime_r(&current_time, &current_tm);
    
    // 格式化时间字符串 
    strftime(time_str_buffer, sizeof(time_str_buffer), 
             "%Y-%m-%d %H:%M:%S", &current_tm);
}

const char* get_current_time_str(void) {
    // 确保字符串是最新的
    // 如果时间字符串为空，更新一次
    if (time_str_buffer[0] == '\0') {
        update_local_time();
    }
    return time_str_buffer;
}

time_t get_current_timestamp(void) {
    return current_time;
}

void get_time_parts(int* hour, int* minute, int* second, 
                    int* year, int* month, int* day) {
    if(hour) *hour = current_tm.tm_hour;
    if(minute) *minute = current_tm.tm_min;
    if(second) *second = current_tm.tm_sec;
    if(year) *year = current_tm.tm_year + 1900;
    if(month) *month = current_tm.tm_mon + 1;
    if(day) *day = current_tm.tm_mday;
}
