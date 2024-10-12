/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-25     wuliwr       the first version
 */
#ifndef APPLICATIONS_DEFINE_H_
#define APPLICATIONS_DEFINE_H_

#include <stdlib.h>
#include "board.h"
// #include <u8g2_port.h>

/*KEY*/
/*获取按键位号*/
#define KEY1 GET_PIN(E,4)
#define KEY2 GET_PIN(E,3)
#define KEY3 GET_PIN(E,2)
#define KEY4 GET_PIN(A,0)
/*键值变量存储结构体初始化*/
struct keys
{
    uint16_t judge_sta;
    char key_sta;
    char single_flage;
    char long_sta;
    uint16_t key_time;
    uint16_t key_double_time;
};
struct syscounts
{
    uint16_t led_flash;
    uint16_t key_time;
    uint16_t v_count_time;
};
/*初始化按键*/
extern void KEY_Init(void);
/*按键读取*/
extern void KEY_Read(void);
/*KEY*/

/*OLED*/
/*获取OLED引脚的位号*/
#define U8G2_CLK_PIN GET_PIN(B, 11)//选择CLK引脚
#define U8G2_SDA_PIN GET_PIN(B, 10)//选择SDA引脚
/*初始化并启动OLED屏幕*/
extern void OLED_Init(void);
/*显示初始界面*/
extern void GUI_Start(void);
/*OLED*/

/*TIMER*/
/* 定时器初始化并开启定时器 */
extern int hwtimer_init(void);
/*TIMER*/

/*ESP8266*/
/*定义ESP8266的设备各项参数*/
#define ESP8266_DEIVCE_NAME "esp8266"
#define ESP8266_CLIENT_NAME "uart1"
#define ESP8266_WIFI_SSID   "S6406_2.4G"
#define ESP8266_WIFI_PASSWORD   "s6406s6406"
#define ESP8266_RECV_BUFF_LEN 512
/*定义用于存储配置信息的结构体*/
//struct at_device_esp8266
//{
//    char *device_name;
//    char *client_name;
//
//    char *wifi_ssid;
//    char *wifi_password;
//    size_t recv_line_num;
//    struct at_device device;
//
//    void *user_data;
//};
/*注册设备esp8266*/
extern void esp8266_device_init(void);
/*连接服务器，每三小时获取天气情况和同步时间*/
extern void esp8266_get_information(void);
/*ESP8266*/

/*时间同步*/
struct timeval {
    time_t tv_sec;
    suseconds_t tv_usec;
};
extern void time_sync(void);
/*时间同步*/

#endif /* APPLICATIONS_DEFINE_H_ */
