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

struct keys key[4] = { 0, 0, 0, 0 };

/*初始化按键*/
void KEY_Init()
{
    rt_pin_mode(KEY1, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_mode(KEY2, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_mode(KEY3, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_mode(KEY4, PIN_MODE_INPUT_PULLUP);
}
/*按键读取*/
void KEY_Read()
{
    key[0].key_sta = rt_pin_read(KEY1);
    key[1].key_sta = rt_pin_read(KEY2);
    key[2].key_sta = rt_pin_read(KEY3);
    key[3].key_sta = !rt_pin_read(KEY4);
    for (int i = 0; i < 3; i++)
    {
        switch (key[i].judge_sta)
        {
        case 0:
        {
            if (key[i].key_sta == 0)
            {
                key[i].judge_sta = 1;
            }
        }
            break;
        case 1:
        {
            if (key[i].key_sta == 0)
            {
                key[i].judge_sta = 2;
            }
            else
                key[i].judge_sta = 0;
        }
            break;
        case 2:
        {
            if (key[i].key_sta == 1)
            {
                key[i].judge_sta = 0;
                if (key[i].key_time < 70)
                {
                    key[i].single_flage = 1;
                    key[i].key_time = 0;
                }
            }
            else
            {
                key[i].key_time++;
                if (key[i].key_time > 70)
                {
                    key[i].long_sta = 1;
                    key[i].key_time = 0;
                }
            }
        }
            break;
        }
    }
}

