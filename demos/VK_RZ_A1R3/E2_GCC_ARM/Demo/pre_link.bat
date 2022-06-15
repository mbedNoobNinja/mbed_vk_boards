:: bat USAGE: C:/xxx> pre_link.bat <build_cfg_folder>
:: This file produce obj_collector.bat in the specified build_cfg_folder

@ECHO OFF

IF NOT EXIST "%~dp0%1\obj_collector.bat" ECHO ::This .bat file generates list of all (*.???) files ^& their locations (relative to .bat's parent directory).^

::The search area is all files in bat's parent directory ^& it's subdirectories.^

::The list is stored in a bat's parent directory as file with name ^<?.txt^>.^

^

@ECHO OFF^

^

IF "%%1"=="" (^

    SET EXT=o^

) ELSE (^

    SET EXT=%%1^

)^

^

SET HERE=%%~dp0^

SET HERE=%%HERE:~0,-1%%^

SET LOG=%%~dp0%%EXT%%.txt^

SET CALLED_FROM=%%CD%%^

^

IF EXIST "%%LOG%%" BREAK ^> "%%LOG%%"^

^

IF NOT "%%CALLED_FROM%%"=="%%HERE%%" CD /D %%HERE%%^

^

CALL :treeProcess^

IF NOT "%%CALLED_FROM%%"=="%%HERE%%" CD /D %%CALLED_FROM%%^

GOTO :EOF^

^

^:treeProcess^

IF "%%CD%%"=="%%HERE%%" (^

    FOR %%%%f IN (*.%%EXT%%) DO CALL ^:doubleSlash "%%%%f"^

) ELSE (^

    FOR %%%%f IN (*.%%EXT%%) DO CALL ^:doubleSlash "%%%%CD:%%~dp0=%%%%\%%%%f"^

)^

FOR /D %%%%d IN (*) DO (^

    CD %%%%d^

    CALL :treeProcess^

    CD ..^

)^

^

^:doubleSlash^

IF NOT "%%~1"=="" (^

    SET OBJ=%%~1^

    CALL ECHO "%%%%OBJ:\=\\%%%%" ^>^> %%LOG%%^

)> %~dp0%1\obj_collector.bat