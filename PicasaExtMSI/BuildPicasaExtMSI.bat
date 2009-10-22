set BIT=%1
if NOT "%BIT%"=="" goto :start
echo "Must specify 32 or 64 on the command line"
goto :error

:start
set PATH="%WIX%\bin";%PATH%

@echo candle.exe -nologo PicasaExt%BIT%.wxs -out "..\Release\PicasaExtMSI\PicasaExt%BIT%.wixobj" -ext WixUIExtension
candle.exe -nologo PicasaExt%BIT%.wxs -out "..\Release\PicasaExtMSI\PicasaExt%BIT%.wixobj" -ext WixUIExtension
@if ERRORLEVEL 1 goto :error


@echo light.exe -nologo "..\Release\PicasaExtMSI\PicasaExt%BIT%.wixobj" -out "..\Release\PicasaExtMSI\PicasaExt%BIT%.msi" -ext WixUIExtension
light.exe -nologo "..\Release\PicasaExtMSI\PicasaExt%BIT%.wixobj" -out "..\Release\PicasaExtMSI\PicasaExt%BIT%.msi" -ext WixUIExtension
@if ERRORLEVEL 1 goto :error

:end
exit 0

:error
exit 1
