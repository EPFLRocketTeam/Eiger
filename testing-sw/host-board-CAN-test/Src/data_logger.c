/*
 * data_logger.c
 */

#include "fatfs.h"
#include "data_logger.h"


FATFS SDFatFs;  /* File system object for SD disk logical drive */
FIL MyFile;     /* File object */
char SDPath[4]; /* SD disk logical drive path */
static uint8_t buffer[_MAX_SS]; /* a work buffer for the f_mkfs() */
FRESULT res;                               /* FatFs function common result code */
uint32_t byteswritten;                     /* File write counts */
uint8_t message[10];

/**
  * Test function
  */
int do_something_SD() {
  uint8_t wtext[] = "Yolo, let's see if this works";    /* File write buffer */

  /*##-1- Link the SD disk I/O driver ########################################*/
  if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
    /*##-2- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      Error_Handler();
    }
    else
    {
      /*##-3- Create a FAT file system (format) on the logical drive #########*/
      if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, buffer, sizeof(buffer)) != FR_OK)
      {
        Error_Handler();
      }
      else
      {
        /*##-4- Create and Open a new text file object with write access #####*/
        if(f_open(&MyFile, "LOG.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          Error_Handler();
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          res = f_write(&MyFile, wtext, sizeof(wtext), (void *)&byteswritten);

          if((byteswritten == 0) || (res != FR_OK))
          {
            /* 'LOG.TXT' file Write or EOF Error */
            Error_Handler();
          }
          else
          {
            /*##-6- Close the open text file #################################*/
            f_close(&MyFile);
            FATFS_UnLinkDriver(SDPath);
            return 0;
          }
        }
      }
    }
  }

  /*##-11- Unlink the SD disk I/O driver ####################################*/
  FATFS_UnLinkDriver(SDPath);
  return 1;
}


int init_SD() {
	/*##-1- Link the SD disk I/O driver ########################################*/
	if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0) {
		/*##-2- Register the file system object to the FatFs module ##############*/
		if (f_mount(&SDFatFs, (TCHAR const*) SDPath, 0) != FR_OK) {
			/* FatFs Initialization Error */
			return 1;
			Error_Handler();
		} else {
			/*##-3- Create a FAT file system (format) on the logical drive #########*/
			if (f_mkfs((TCHAR const*) SDPath, FM_ANY, 0, buffer, sizeof(buffer))
					!= FR_OK) {
				return 1;
				Error_Handler();
			} else {
				/*##-4- Create and Open a new text file object with write access #####*/
				if (f_open(&MyFile, "LOG.TXT", FA_OPEN_APPEND | FA_CREATE_ALWAYS | FA_WRITE)
						!= FR_OK) {
					return 1;
					/* 'LOG.TXT' file Open for write Error */
					Error_Handler();
				}
			}
		}
	}

	// good initialization
	return 0;
}

/*
 * Log the content of a CAN frame to the file
 */
int log_SD(uint8_t payload[], uint32_t id) {
	message[0] = (uint8_t) (id >> 8);
	message[1] = (uint8_t) (id >> 0);
	message[2] = payload[0];
	message[3] = payload[1];
	message[4] = payload[2];
	message[5] = payload[3];
	message[6] = payload[4];
	message[7] = payload[5];
	message[8] = payload[6];
	message[9] = payload[7];
	// maybe add newline later one if needed
	res = f_write(&MyFile, message, sizeof(message), (void *)&byteswritten);
    if (res != FR_OK) {
    	return 1;
    }
    // For now on, only try to log 30 sec
    if (HAL_GetTick() > 30 * 1000) {
    	f_close(&MyFile);
    	FATFS_UnLinkDriver(SDPath);
    }
    // no error
    return 0;
}
