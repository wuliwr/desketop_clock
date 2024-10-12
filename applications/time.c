/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-25     wuliwr       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "define.h"

#define HWTIMER_DEV_NAME   "timer3"     /* 定时器名称 */
rt_device_t hw_dev = RT_NULL; /* 定时器设备句柄 */
rt_hwtimerval_t timeout_s; /* 定时器超时值 */

/*超时回调函数*/
extern struct keys key[4];
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
//    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
//    rt_kprintf("tick is :%d !\n", rt_tick_get());
    KEY_Read();
    if((key[0].single_flage) == 1)
    {
        rt_kprintf("KEY1 is down !\n");
        key[0].single_flage = 0;
    }
    if((key[0].long_sta) == 1)
    {
        rt_kprintf("KEY1 is long press !\n");
        key[0].long_sta = 0;
    }
    if((key[1].single_flage) == 1)
        {
            rt_kprintf("KEY2 is down !\n");
            key[1].single_flage = 0;
        }
    if((key[2].single_flage) == 1)
        {
            rt_kprintf("KEY3 is down !\n");
            key[2].single_flage = 0;
        }
    if((key[3].single_flage) == 1)
        {
            rt_kprintf("KEY4 is down !\n");
            key[3].single_flage = 0;
        }
    return 0;
}

/*定时器初始化*/
int hwtimer_init()
{
    rt_err_t ret = RT_EOK;
    rt_hwtimer_mode_t mode;
    rt_uint32_t freq = 10000; /* 计数频率 */

    /*查找定时器设备*/
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
        return RT_ERROR;

    /*以读写方式打开设备*/
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /*设置超时回调函数*/
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /*设置周期性定时，频率为100Hz*/
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    mode = HWTIMER_MODE_PERIOD; //周期性定时
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        rt_device_close(hw_dev);
        hw_dev = RT_NULL;
        return ret;
    }

    rt_kprintf("set mode success!\n");
    /* 设置定时器超时值为10ms并启动定时器 */
    timeout_s.sec = 0; /* 秒 */
    timeout_s.usec = 10000; /* 微秒 */
    rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));

    return 0;
}
//msh命令注册
MSH_CMD_EXPORT(hwtimer_init, hwtimer device sample);
