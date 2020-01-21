::echo off

if exist temp rd /s /q temp
rem if not exist temp md temp
if exist *.mcs del *.mcs
if exist *.tagsrc del *.tagsrc
if exist *.mptags del *.mptags

::if exist *.x (cd *.x ) else (goto end )

copy .\nbproject\*.xml .\
if exist .\debug del .\debug /S /Q
if exist .\build del .\build /S /Q
if exist .\dist  del .\dist /S /Q
if exist .\disassembly del .\disassembly /S /Q
if exist .\nbproject del .\nbproject /S /Q
    REM del .\nbproject\private /S /Q

rd /s /Q .\build
rd /s /Q .\dist
rd /s /Q .\debug
rd /s /Q .\nbproject\private

copy .\*.xml .\nbproject\
del .\*.xml
del .\*.o
del .\MPLABXLog*.*
del .\*.bak
del .\log*.*
cd ..

:end

::echo on
