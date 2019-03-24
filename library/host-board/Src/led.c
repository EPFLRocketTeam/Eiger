#include "tim.h"

#define TIM_LED (TIM8)

void led_set_rgb(uint16_t r, uint16_t g, uint16_t b) {
	LL_TIM_OC_SetCompareCH1(TIM_LED, r);
	LL_TIM_OC_SetCompareCH2(TIM_LED, g);
	LL_TIM_OC_SetCompareCH3(TIM_LED, b);
}

void led_set_r(uint16_t r) {
	LL_TIM_OC_SetCompareCH1(TIM_LED, r);
}

void led_set_g(uint16_t g) {
	LL_TIM_OC_SetCompareCH2(TIM_LED, g);
}

void led_set_b(uint16_t b) {
	LL_TIM_OC_SetCompareCH3(TIM_LED, b);
}

void led_init() {
	LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH1N);
	LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH2N);
	LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH3N);
	LL_TIM_EnableAutomaticOutput(TIM8);
	LL_TIM_EnableCounter(TIM8);

	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_14);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_15);

	led_set_rgb(0,0,0);
}
