@ECHO OFF

ECHO ____________________________________

ECHO -

ECHO        Grand Holo - VW Boost

ECHO -

ECHO       (c)2015 PCH INNOVATIONS

ECHO ____________________________________

ECHO -

TIMEOUT 10

ECHO Starting ambient light ... 
START "" /b %UserProfile%\Desktop\3dAmbiLight\3dAmbiLight.exe

TIMEOUT 5

ECHO Starting video player ...

START "" /b "C:\Program Files (x86)\UDP\io player\ioplayer.exe" -fss -file:"%UserProfile%\Desktop\VWHolo_Final.mp4"

PAUSE