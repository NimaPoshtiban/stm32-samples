constexpr auto PERIPHERAL_BASE = 0x40000000U;
constexpr auto AHB1_BASE = PERIPHERAL_BASE + 0x20000U;
constexpr auto GPIOA_BASE =  AHB1_BASE + 0x0U;
constexpr auto RCC_BASE = AHB1_BASE + 0x3800U;
#include <cstdint>
constexpr auto RCC_AHB1ENR_OFFSET = 0x30U;

#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET))
constexpr auto RCC_AHB1ENR_GPIOAEN = 0x00U;

constexpr auto GPIO_MODER_OFFSET = 0x00U;
#define GPIOA_MODER  ((volatile uint32_t*)(GPIOA_BASE + GPIO_MODER_OFFSET))
constexpr auto GPIO_MODER_MODER5 = 10U;
constexpr auto GPIO_ODR_OFFSET = 0x14U;
#define GPIOA_ODR ((volatile uint32_t*) (GPIOA_BASE + GPIO_ODR_OFFSET))

constexpr auto LED_PIN = 5U;

int main(){
	*RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN);
	
//do two dummy reads after enabling the peripheral clock, as per the errata
	volatile uint32_t dummy;
	dummy = *(RCC_AHB1ENR);
	dummy = *(RCC_AHB1ENR);
	
	*GPIOA_MODER |=  (1 << GPIO_MODER_MODER5);
	while(1){
		*GPIOA_ODR ^= (1<< LED_PIN);
		for(uint32_t i = 0; i<1000000;i++);
	}

	return 0;
}
