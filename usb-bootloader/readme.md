# Burn USB Bootloader and Fuses
```
avrdude.exe -c usbasp -B4 -p t85 -v -U flash:w:t85_fastexit.hex
avrdude.exe -c usbasp -B4 -p t85 -v -U lfuse:w:0xe1:m -U hfuse:w:0xde:m -U efuse:w:0xfe:m
```