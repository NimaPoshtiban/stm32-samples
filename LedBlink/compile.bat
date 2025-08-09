arm-none-eabi-gcc main.cpp startup.cpp -T linker_script.ld -o blink.elf -mcpu=cortex-m4 -mthumb -nostdlib -Wall -pedantic -Wextra -fno-exceptions -fno-rtti
