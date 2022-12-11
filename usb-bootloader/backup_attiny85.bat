@echo off
echo This will read the Chips flash and save it as t85_backup.hex!
echo Connect ICSP Programmer and continue...
pause
timeout 5

%userprofile%\.platformio\packages\tool-avrdude\avrdude.exe -c usbasp -p t85 -v -U flash:r:t85_backup.hex:i

pause