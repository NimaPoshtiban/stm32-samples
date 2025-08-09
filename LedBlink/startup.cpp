#define SRAM_START (0x20000000U)
#define SRAM_SIZE  (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

#include <cstdint>

constexpr uint32_t ISR_VECTOR_SIZE_WORDS = 114U;

extern "C" void reset_handler() noexcept;
extern "C" void default_handler() noexcept ;

extern "C" [[gnu::alias("default_handler"),gnu::weak]] void nmi_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void hard_fault_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void bus_fault_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void usage_fault_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void svcall_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void debug_monitor_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void pendsv_handler();
extern "C" [[gnu::alias("default_handler"),gnu::weak]] void systick_handler();
// implement other handlers
extern "C" [[gnu::section(".isr_vector")]] uint32_t  isr_vector[ISR_VECTOR_SIZE_WORDS] = {
	STACK_POINTER_INIT_ADDRESS,
	reinterpret_cast<uint32_t>(&reset_handler),
	reinterpret_cast<uint32_t>(&nmi_handler),
	reinterpret_cast<uint32_t>(&hard_fault_handler),
	reinterpret_cast<uint32_t>(&bus_fault_handler),
	reinterpret_cast<uint32_t>(&usage_fault_handler),
	0,0,0,0,0,
	reinterpret_cast<uint32_t>(&svcall_handler),
	reinterpret_cast<uint32_t>(&debug_monitor_handler),
	0,
	reinterpret_cast<uint32_t>(&pendsv_handler),
	reinterpret_cast<uint32_t>(&systick_handler),
};

extern "C" void default_handler() noexcept {
	while(1);
}


extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
int main();

extern "C" void reset_handler() noexcept{
	uint32_t data_size = reinterpret_cast<uint32_t>(&_edata) - reinterpret_cast<uint32_t>(&_sdata);
	uint16_t *flash_data  = reinterpret_cast<uint16_t*>(&_etext);
	uint8_t *sram_data = reinterpret_cast<uint8_t*>(&_sdata);
	for(uint32_t i = 0; i < data_size;i++){
		sram_data[i] = flash_data[i];
	}
	//Zero-fill .bss section in SRAM
	uint32_t bss_size = reinterpret_cast<uint32_t>(&_ebss) - reinterpret_cast<uint32_t>(&_sbss);
	uint8_t *bss = reinterpret_cast<uint8_t*>(_sbss);
	for(uint32_t i = 0;i < bss_size;i++){
		bss[i]=0;
	}

	main();
}

