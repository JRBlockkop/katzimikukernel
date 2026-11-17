
all:
	set -euo pipefail

	mkdir -p build

	arm-none-eabi-gcc \
	    -mcpu=cortex-m4 \
	    -mthumb \
	    -mfloat-abi=soft \
	    -Os \
	    -g \
	    -ffreestanding \
	    -fno-builtin \
	    -fdata-sections \
	    -ffunction-sections \
	    -Wall -Wextra \
	    -nostdlib \
	    -Wl,--gc-sections \
	    -Wl,--build-id=none \
	    -T linker.ld \
	    -Wl,-Map=build/kernel.map \
	    startup.c main.c src/systick.c\
	    -o build/kernel.elf

	arm-none-eabi-objcopy \
	    -O binary \
	    build/kernel.elf \
	    build/kernel.bin

	arm-none-eabi-objcopy \
	    -O ihex \
	    build/kernel.elf \
	    build/kernel.hex

	echo "Build successful!"
	echo "ELF: build/kernel.elf"
	echo "BIN: build/kernel.bin"
	echo "HEX: build/kernel.hex"
	st-flash --format ihex write build/kernel.hex
	echo "FLASHED"
