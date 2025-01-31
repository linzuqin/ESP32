#ifndef  _NTP_TIME_H_
#define  _NTP_TIME_H_

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"
#include "lvgl.h"
#include "../generated/gui_guider.h"
#include "../generated/events_init.h"
#include "esp_log.h"
#include "lvgl.h"
#include "../generated/gui_guider.h"
#include "../generated/events_init.h"
void esp_initialize_sntp(void);

void ntp_task_start(void);


#endif
