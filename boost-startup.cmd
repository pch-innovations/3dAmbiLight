@ECHO OFF

ECHO ____________________________________

ECHO

ECHO        Grand Holo - VW Boost

ECHO

ECHO       (c)2015 PCH INNOVATIONS

ECHO ____________________________________

ECHO

TIMEOUT 10

ECHO Starting ambient light ... 
START "" /b C:\Users\UE\Desktop\3dAmbiLight\3dAmbiLight.exe

TIMEOUT 5

ECHO Starting video player ...

START "" /b "C:\Program Files (x86)\UDP\io player\ioplayer.exe" -fss -file:"C:\Users\UE\Desktop\PERFORMANCE TEST\Sequenz 1_5view.mp4"

PAUSE