#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "Grbl.h"
#include "UserBoard.h"
#include "Wire.h"
#include <stdatomic.h>

static BoardCtrl board;
static atomic_uint_least32_t limit_ext_io = ATOMIC_VAR_INIT(0xff);

extern xQueueHandle limit_sw_queue;

static void limitUpdateTasK(void *arg) {
    uint8_t limit_status_last = 0xff;
    uint8_t limit_status = 0xff;

    for (;;) {
        board.getExtIOStatus(&limit_status);
        if ((limit_status & 0x0f) != 0x0f && limit_status != limit_status_last) {
            int evt;
            xQueueSendFromISR(limit_sw_queue, &evt, NULL);
        }

        limit_status_last = limit_status;
        atomic_store(&limit_ext_io, limit_status);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

uint8_t getExtIOStatus(uint8_t pin_in) {
    uint32_t limit_status;
    limit_status = atomic_load(&limit_ext_io);
    return ((0x01 << (pin_in - EXT_IN_PIN_BASE)) & limit_status) > 0 ? 1 : 0;
}

void userBoardInit() {
    Wire.begin(21, 22, 400000);
    board.init(Wire);
    board.enableMotor(1);
    board.setMicrostepResolution(BoardCtrl::kMicrosteps16);
    xTaskCreatePinnedToCore(limitUpdateTasK, "limitUpdateTasK", 2 * 1024, NULL, 2, NULL, 1);
}


