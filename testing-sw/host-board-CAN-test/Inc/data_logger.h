
/*
 * data_logger.h
 */

#ifndef DATA_LOGGER_H_
#define DATA_LOGGER_H_

#include "ff_gen_drv.h"
#include "sd_diskio.h"

int do_something_SD(void);
int init_SD(void);
int log_SD(uint8_t payload[], uint32_t id);

#endif //DATA_LOGGER_H_
