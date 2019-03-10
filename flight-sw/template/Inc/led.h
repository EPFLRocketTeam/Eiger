/**
  ******************************************************************************
  * File Name          : led.h
  * Description        :
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __led_H
#define __led_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void led_set_rgb(uint16_t r, uint16_t g, uint16_t b);
void led_set_r(uint16_t r);
void led_set_g(uint16_t g);
void led_set_b(uint16_t b);

void led_init();

#ifdef __cplusplus
}
#endif
#endif /*__ led_H */
