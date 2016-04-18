@ECHO OFF

WHERE /Q nuget >NUL
IF %ERRORLEVEL% NEQ 0 ( 
    ECHO nuget not found.
    ECHO.
    ECHO Run "%~pd0download-nuget.cmd" to download the latest version, or update PATH as appropriate.
    GOTO END
)

IF "%1"=="" (
	GOTO PackWithFileVersion
)
:PackWithCommandLineVersion
SET VERSION=%1
GOTO PACK

:PackWithFileVersion
SET /p VERSION=<NuGetPackageVersion.txt
GOTO PACK


:PACK
SET NUGET_ARGS=^
    -nopackageanalysis ^
    -version %VERSION% ^
    -Verbosity detailed ^
    -Symbols

nuget pack LogWRC.nuspec %NUGET_ARGS%

:END

EXIT /B