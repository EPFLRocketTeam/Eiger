#include "Sensors/GPS_board.h"
#include "Sensors/GPS/minmea.h"

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "led.h"
#include "CAN_communication.h"
#include "usart.h"
#include <inttypes.h>

UART_HandleTypeDef* gps_huart;
int led_gps_id;

void gps_init(UART_HandleTypeDef *gpsHuart) {
	gps_huart = gpsHuart;
	led_gps_id = led_register_TK();
}

HAL_StatusTypeDef INFO(char* msg)
{
	return HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
}

void TK_GPS_board(void const * argument)
{
	uint8_t rx;
	char tx[300];
	char line[MINMEA_MAX_LENGTH+10];
	struct minmea_sentence_gga gga;

	uint8_t idx = 0;
	uint32_t cntr = 0;

	float latitude = 0.0f;
	float longitude = 0.0f;
	float altitude = 0.0f;
	float hdop = 0.0f;
	int   sats = 0;

	int overrun = 0;

	led_set_TK_rgb(led_gps_id, 150, 150, 150);
	osDelay(1000);

	for (;;)
	{
		overrun = 0;
		while (1)
		{
			HAL_UART_Receive(gps_huart, &rx, 1, 100);
			if (rx == '$')
			{
				idx = 0;
				line[idx] = rx;
				break;
			}
		}
		while (1)
		{
			HAL_UART_Receive(gps_huart, &rx, 1, 100);
			if (rx == '\n' || rx == '\r' || rx == '$')
			{
				line[++idx] = '\0';
				break;
			}
			line[++idx] = rx;
			if (idx>MINMEA_MAX_LENGTH) {
				line[++idx] = '\0';
				overrun = 1;
				break;
			}
		}
		//INFO(line);
		//INFO("\n");
		if (!overrun && minmea_sentence_id(line, false) == MINMEA_SENTENCE_GGA)
		{
			if (minmea_parse_gga(&gga, line)) {

			latitude  = minmea_tocoord(&(gga.latitude));
			longitude = minmea_tocoord(&(gga.longitude));
			altitude  = minmea_tofloat(&(gga.altitude));
			hdop      = minmea_tofloat(&(gga.hdop));
			sats      = gga.satellites_tracked;

			if (gga.fix_quality)
			{
				can_setFrame((int32_t)(1e3)*hdop, DATA_ID_GPS_HDOP, HAL_GetTick());
				can_setFrame((int32_t)(1e6)*latitude, DATA_ID_GPS_LAT, HAL_GetTick());
				can_setFrame((int32_t)(1e6)*longitude, DATA_ID_GPS_LONG, HAL_GetTick());
				can_setFrame((int32_t)altitude, DATA_ID_GPS_ALTITUDE, HAL_GetTick());
				can_setFrame((int32_t)sats, DATA_ID_GPS_SATS, HAL_GetTick());

				led_set_TK_rgb(led_gps_id, 0, 150, 0);
			}
			else
			{
				can_setFrame((int32_t)sats, DATA_ID_GPS_SATS, HAL_GetTick());
				led_set_TK_rgb(led_gps_id, 0, 0, 150);
			}
			}
			//INFO(tx);
		}
	}
}
