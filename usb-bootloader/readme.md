# Burn USB Bootloader and Fuses
[Micronucleus](https://github.com/micronucleus/micronucleus) is a bootloader designed for AVR ATtiny microcontrollers with a minimal usb interface.
This needs to be flashed once via ICSP. After that, the NeoTree can be flashed with new firmware via USB.
You'll need an ICSP programmer for that.
```
avrdude.exe -c usbasp -B4 -p t85 -v -U flash:w:t85_usbdemo.hex
avrdude.exe -c usbasp -B4 -p t85 -v -U lfuse:w:0xe1:m -U hfuse:w:0xde:m -U efuse:w:0xfe:m
```
See [here](https://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny85&LOW=E1&HIGH=DE&EXTENDED=FE) for fuse description.

## Files
| File      | Description |
|-----------|-------------|
| backup_attiny85.bat | Reads and backups the contents of the flash |
| flash_attiny85_usbdemo.bat | Flash USB bootloader and Demo program (recommended) |
| flash_attiny85_usbonly.bat | Flash USB bootloader |
| t85_default.hex | Standard micronucelos bootloader |
| t85_fastexit.hex | Micronucelos bootloader which only waits few milliseconds |
| t85_usbdemo.hex | Fastexit micronucelos bootloader and NeoPixel Demo |
