#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "serial/wincomsend/serial.h"

#define screen1 lv_scr_act()

static lv_timer_t *timer_txtrecive;
static lv_obj_t *kb1;
static lv_obj_t *txtsend;
static lv_obj_t *txtrecive;
static lv_obj_t *send_btn;
static lv_obj_t *botton_exit;
static lv_obj_t *comm_switch;
static lv_obj_t *COM_SELECT_DROP;
static lv_obj_t *COM_bitbound_DROP;
static lv_obj_t *cs1;
static lv_obj_t *cs2;
// static lv_obj_t * screen1;
static void send_btn_cb(lv_event_t *e);
static void txtrecive_cb(lv_timer_t *t);
static void clear_btn_cb(lv_event_t *e);

static lv_obj_t *clear_lable;
HANDLE hComm;
PORT COM5              = 0;
char send_buff[1024]   = {0}; // 缓冲区
char recive_buff[1024] = {0};
int rcv_len            = 0; // 接受长度
int ensend             = 0; // 已发送标志
volatile int isread;        // 已读取标志
char *sendpt;
char comname_buff[10] = {0};
char bitrato_buff[10] = {0};
HANDLE rs_handle; // 接收线程句柄
HANDLE se_handle; // 发送线程句柄
int readcount;
volatile int NoBytesRead;
volatile int i;

const char *btn_txts[] = {
    "ok",
    "",
};

WINAPI *WaitComm(LPVOID lpThreadParameter) // 接收线程函数
{

    while (1) {

        NoBytesRead = 0;
        i           = 0;
        do {
            ReadFile(hComm, &recive_buff[i], 1, &NoBytesRead, NULL);
            if (NoBytesRead > 0) { i += NoBytesRead; }

        } while (NoBytesRead);

        isread = i;

        if (isread > 0) { SuspendThread(GetCurrentThread()); } // 接收到数据以后挂起自身
    }
    return 0;
}

WINAPI *Waitsend(LPVOID lpThreadParameter) // 发送线程函数
{
    static i;

    while (1) {
        memset(send_buff, 0, 1024);
        i = 0;
        while (*(sendpt + i)) {
            send_buff[i] = *(sendpt + i);
            i++;
        }
        if (lv_obj_has_state(cs1, LV_STATE_CHECKED)) {
            send_buff[i]     = 0x0d;
            send_buff[i + 1] = 0x0a;
            if (lv_obj_has_state(cs2, LV_STATE_CHECKED)) {
                Serial_SendData(hComm, send_buff, i + 3);
            } else {
                Serial_SendData(hComm, send_buff, i + 2);
            }
        } else {
            Serial_SendData(hComm, send_buff, i);
        }

        SuspendThread(GetCurrentThread());
    }

    return 0;
}

void comm_switch_cb(lv_event_t *e)
{

    COMMTIMEOUTS timeouts = {0};

    lv_obj_t *xxx = (lv_obj_t *)e->target;

    if (lv_obj_has_state(xxx, LV_STATE_CHECKED)) {
        printf("on ");
        lv_obj_add_state(COM_SELECT_DROP, LV_STATE_DISABLED);
        lv_obj_add_state(COM_bitbound_DROP, LV_STATE_DISABLED);

        lv_dropdown_get_selected_str(COM_SELECT_DROP, comname_buff, 10);
        lv_dropdown_get_selected_str(COM_bitbound_DROP, bitrato_buff, 10);

        printf("%s ", comname_buff);
        printf("%s ", bitrato_buff);

        hComm = serial_init(comname_buff, atoi(bitrato_buff), 8, 1, 0);

        if (hComm == 0) {
            lv_obj_t *msg1 = lv_msgbox_create(screen1, "ERROR", "CAN NOT OPEN THIS COM", 0, 1);
            lv_obj_align(msg1, LV_ALIGN_TOP_MID, 50, 0);
            lv_obj_clear_state(xxx, LV_STATE_CHECKED);
            ClosePort(hComm);
            lv_obj_clear_state(COM_SELECT_DROP, LV_STATE_DISABLED);
            lv_obj_clear_state(COM_bitbound_DROP, LV_STATE_DISABLED);
            return;
        }
        ResumeThread(rs_handle);

        lv_obj_clear_state(send_btn, LV_STATE_DISABLED);

    } else {
        SuspendThread(rs_handle);
        ClosePort(hComm);
        lv_obj_clear_state(COM_SELECT_DROP, LV_STATE_DISABLED);
        lv_obj_clear_state(COM_bitbound_DROP, LV_STATE_DISABLED);
        printf("off ");
        lv_obj_add_state(send_btn, LV_STATE_DISABLED);
    }
}

void txtsend_test() // lvgl主任务入口
{

    int j = 0;

    // hComm = serial_init(1, 115200, 8, 1, 0);//初始化串口5

    // rs_handle = CreateThread(0, 0, WaitComm, 0, CREATE_SUSPENDED, 0); // 创建接收线程
    // se_handle = CreateThread(0, 0, Waitsend, 0, CREATE_SUSPENDED, 0); // 创建发送线程

    lv_obj_set_style_bg_color(screen1, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_clear_flag(screen1, LV_OBJ_FLAG_SCROLLABLE);

    comm_switch = lv_switch_create(screen1);
    lv_obj_set_size(comm_switch, 100, 50);
    lv_obj_align(comm_switch, LV_ALIGN_TOP_RIGHT, -380, 50);
    lv_obj_add_event_cb(comm_switch, comm_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);

    kb1 = lv_keyboard_create(screen1);
    lv_obj_set_size(kb1, 500, 200);
    lv_obj_set_align(kb1, LV_ALIGN_BOTTOM_RIGHT);

    txtsend = lv_textarea_create(screen1);
    lv_obj_set_size(txtsend, 500, 200);
    lv_obj_align_to(txtsend, kb1, LV_ALIGN_OUT_TOP_MID, 0, 0);

    txtrecive = lv_textarea_create(screen1);
    lv_obj_set_size(txtrecive, 500, 550);
    lv_obj_set_align(txtrecive, LV_ALIGN_TOP_LEFT);

    lv_keyboard_set_textarea(kb1, txtsend);

    send_btn = lv_btn_create(txtsend);
    lv_obj_set_size(send_btn, 80, 40);
    lv_obj_set_align(send_btn, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_t *send_lable = lv_label_create(send_btn);
    lv_label_set_text_fmt(send_lable, "SEND");
    // lv_obj_add_event_cb(send_btn, send_btn_cb, LV_EVENT_CLICKED, 0); // 发送按钮回调
    lv_obj_add_state(send_btn, LV_STATE_DISABLED);

    lv_obj_t *clear_btn = lv_btn_create(screen1);
    lv_obj_set_size(clear_btn, 80, 40);
    lv_obj_align(clear_btn, LV_ALIGN_BOTTOM_LEFT, 405, -9);
    clear_lable = lv_label_create(clear_btn);
    lv_label_set_text_fmt(clear_lable, "CLEAR");
    lv_obj_add_event_cb(clear_btn, clear_btn_cb, LV_EVENT_CLICKED, 0); // 清除按钮回调

    lv_group_t *group1 = lv_group_create();
    lv_group_set_default(group1);
    lv_win32_add_all_input_devices_to_group(group1);
    lv_group_add_obj(group1, kb1);

    COM_SELECT_DROP = lv_dropdown_create(screen1);
    lv_dropdown_clear_options(COM_SELECT_DROP);
    lv_obj_align(COM_SELECT_DROP, LV_ALIGN_TOP_MID, 100, 0);
    lv_dropdown_add_option(COM_SELECT_DROP, "", 0);

    COM_bitbound_DROP = lv_dropdown_create(screen1);
    lv_dropdown_clear_options(COM_bitbound_DROP);
    lv_obj_align(COM_bitbound_DROP, LV_ALIGN_TOP_MID, 250, 0);

    lv_dropdown_set_options(COM_bitbound_DROP, "115200\n128000\n57600\n56000\n19200\n9600\n\0");

    for (int i = 0; i < 100; i++)

    {
        TCHAR comname[10];
        sprintf(comname, "COM%d", i);
        hComm = CreateFile(comname,                      // port name
                           GENERIC_READ | GENERIC_WRITE, // Read/Write
                           0,                            // No Sharing
                           NULL,                         // No Security
                           OPEN_EXISTING,                // Open existing port only
                           0,                            // Non Overlapped I/O
                           NULL);                        // Null for Comm Devices

        if (hComm != INVALID_HANDLE_VALUE) {
            lv_dropdown_add_option(COM_SELECT_DROP, comname, j);
            CloseHandle(hComm);
            j++;
        }
    }

    cs1 = lv_checkbox_create(txtsend);
    lv_obj_set_align(cs1, LV_ALIGN_BOTTOM_LEFT);
    lv_checkbox_set_text_static(cs1, "END ADD \\r\\n");
    lv_obj_add_state(cs1, LV_STATE_CHECKED);

    cs2 = lv_checkbox_create(txtsend);
    lv_obj_align(cs2, LV_ALIGN_BOTTOM_LEFT, 170, 0);
    lv_checkbox_set_text_static(cs2, "END ADD \\0");
    lv_obj_add_state(cs2, LV_STATE_CHECKED);

    // timer_txtrecive = lv_timer_create(txtrecive_cb, 10, 0); // 每隔10ms检查串口接收
}

void txtrecive_cb(lv_timer_t *t) // 这里每过10ms检查串口接收数据
{

    if (isread > 0) // 假如串口接收到
    {
        lv_textarea_add_text(txtrecive, recive_buff); // 文字添加到接收区

        isread = 0; // 接收标志清0
        memset(recive_buff, 0, 1024);
        ResumeThread(rs_handle); // 恢复接收线程
    }
}

void clear_btn_cb(lv_event_t *e) // 清空接收区显示文字
{
    lv_textarea_set_text(txtrecive, "");
}

void send_btn_cb(lv_event_t *e) // 发送按钮回调
{
    int i;
    i = 0;

    printf("sending\r\n");
    sendpt = lv_textarea_get_text(txtsend);

    ResumeThread(se_handle); // 恢复发送线程
}
