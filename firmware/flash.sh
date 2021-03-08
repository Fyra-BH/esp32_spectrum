# !/bin/bash
esptool -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 4MB 0x8000 partition-table.bin 0x1000 bootloader.bin 0x10000 micropython.bin