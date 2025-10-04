@echo off
setlocal

:: =========================================================================
:: COMMAND-LINE IRVINE32 COMPILER SCRIPT (.bat)
:: USAGE: compile_and_run <filename_without_extension>
:: E.g., compile_and_run my_program
:: NOTE: This version is configured using the user's specific VS 2022 paths.
:: =========================================================================

:: --- CONFIGURATION (CRITICAL: DO NOT CHANGE THESE IF YOUR PATHS ARE CORRECT) ---
:: 1. Path to your MASM executables (ml.exe, link.exe) from VS 2022
set MASM_BIN_DIR=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x86

:: Define the path to the Visual Studio LIB files (REQUIRED for Windows APIs like MessageBoxA)
set VS_MSVC_ROOT=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207
set VS_LIB_DIR=%VS_MSVC_ROOT%\lib\x86

:: 2. Path to the Irvine32.lib and Irvine32.inc files
set LIB_DIR=C:\irvine
set INC_DIR=C:\irvine

set LIB_FILE=Irvine32.lib
set KERNEL_LIB=Kernel32.Lib
set USER_LIB=User32.Lib
:: --------------------------------------------------------------------------------


:: Check for input filename
if "%~1"=="" (
    echo Error: Missing assembly filename.
    echo Usage: %~n0 ^<assembly_file_name_without_extension^>
    goto :eof
)

set ASMFILENAME=%~n1
set ASMSOURCE=%ASMFILENAME%.asm
set OBJFILENAME=%ASMFILENAME%.obj
set EXEFILENAME=%ASMFILENAME%.exe
set PWD=%CD%

:: --- Pre-check environment ---
if not exist "%MASM_BIN_DIR%\ml.exe" (
    echo Error: ml.exe not found.
    echo Script is currently checking the path: "%MASM_BIN_DIR%\ml.exe"
    echo Please check and update the MASM_BIN_DIR variable in this script.
    goto :eof
)

if not exist "%LIB_DIR%\%LIB_FILE%" (
    echo Error: %LIB_FILE% not found in %LIB_DIR%.
    echo Please check and update the LIB_DIR variable.
    goto :eof
)

if not exist "%INC_DIR%\Irvine32.inc" (
    echo Error: Irvine32.inc not found in %INC_DIR%.
    echo Please check and update the INC_DIR variable.
    goto :eof
)

if not exist "%ASMSOURCE%" (
    echo Error: Source file "%ASMSOURCE%" not found in the current directory.
    goto :eof
)

echo ----------------------------------------------------------------------
echo ASsembling: %ASMSOURCE%
echo ----------------------------------------------------------------------

:: Step 1: Assemble (Create .OBJ file)
:: Use the full path for ml.exe
:: /c: Compile only (do not link)
:: /coff: Produce Common Object File Format
:: /I: Specify include directory for Irvine32.inc
"%MASM_BIN_DIR%\ml" /c /coff /I"%INC_DIR%" %ASMSOURCE%

if errorlevel 1 goto error_assembly

echo.
echo ----------------------------------------------------------------------
echo LINking: %OBJFILENAME%
echo ----------------------------------------------------------------------

:: Step 2: Link (Create .EXE file)
:: Use the full path for link.exe
:: IMPORTANT: Use two LIBPATH directives: one for Irvine, one for VS system libs.
"%MASM_BIN_DIR%\link" /SUBSYSTEM:CONSOLE /LIBPATH:"%LIB_DIR%" /LIBPATH:"%VS_LIB_DIR%" /OUT:"%EXEFILENAME%" %OBJFILENAME% %LIB_FILE% %KERNEL_LIB% %USER_LIB%

if errorlevel 1 goto error_linking

echo.
echo ----------------------------------------------------------------------
echo COMpleted: %EXEFILENAME%
echo ----------------------------------------------------------------------
echo.

:: Step 3: Run the executable
echo Running: %EXEFILENAME%
echo ----------------------------------------------------------------------
%EXEFILENAME%

goto :end

:error_assembly
echo.
echo *** ASSEMBLY FAILED - CHECK YOUR SYNTAX ***
goto :end

:error_linking
echo.
echo *** LINKING FAILED - CHECK LIBRARY PATHS or MISSING EXPORTED SYMBOLS ***
goto :end

:end
:: Clean up the intermediate .OBJ file
del /Q %OBJFILENAME% > nul
endlocal
