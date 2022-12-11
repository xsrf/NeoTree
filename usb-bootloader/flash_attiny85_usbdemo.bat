@echo off
echo This will set the Fuses, write the USB Bootloader and a Rainbow Demo program to the chip!
echo Connect ICSP Programmer and continue...
pause
timeout 5

REM %userprofile%/.platformio/packages/tool-avrdude/avrdude.exe -c avrisp -P COM3 -b 19200 -p t13 -v -U flash:w:t85_usbdemo.hex
%userprofile%/.platformio/packages/tool-avrdude/avrdude.exe -c usbasp -B4 -p t85 -v -U flash:w:t85_usbdemo.hex
%userprofile%/.platformio/packages/tool-avrdude/avrdude.exe -c usbasp -B4 -p t85 -v -U lfuse:w:0xe1:m -U hfuse:w:0xde:m -U efuse:w:0xfe:m

REM bofore:
REM avrdude.exe: safemode: hfuse reads as DF
REM avrdude.exe: safemode: efuse reads as FF
REM avrdude.exe: safemode: Fuses OK (E:FF, H:DF, L:62)

REM after:
REM avrdude.exe: safemode: hfuse reads as DE
REM avrdude.exe: safemode: efuse reads as FE
REM avrdude.exe: safemode: Fuses OK (E:FE, H:DE, L:E1)

REM http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny85

pause