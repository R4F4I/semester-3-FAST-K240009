Command-Line Setup for Irvine32 Assembly

This guide details how to set up your Windows environment to compile and run Irvine32 assembly programs using MASM entirely from the command line, bypassing Visual Studio.

## 1. Prerequisites (Get the Tools)

You must obtain the following necessary tools and library files:

### A. MASM Tools (`ml.exe` and `link.exe`)

You need the Microsoft Macro Assembler (MASM) package. The easiest way to get the essential 32-bit tools (`ml.exe`, `link.exe`, and necessary `.lib` files like `kernel32.lib`) is to download a package like **MASM32 SDK**.

* **Action:** Download and install the MASM32 SDK.

* **Key Path:** Note the path to the executables, typically `C:\masm32\bin`. This path is required by the batch script.

### B. Irvine32 Library Files

You need the library and include files provided by the textbook author (Kip Irvine).

* **Action:** Locate the **`Irvine32.lib`** (the compiled library) and **`Irvine32.inc`** (the header file) from the textbook's source code downloads.

## 2. Configure Folder Structure

We will create a central directory for your assembly projects and configuration files.

| **Folder/File** | **Location** | **Purpose** | 
| **`C:\ASM_DEV\`** | Root of your assembly projects. |  | 
| **`C:\ASM_DEV\Lib\`** | Inside your project root. | Place your **`Irvine32.lib`** here. | 
| **`C:\ASM_DEV\Inc\`** | Inside your project root. | Place your **`Irvine32.inc`** here. | 
| **`C:\ASM_DEV\compile_and_run.bat`** | Inside your project root. | The automation script provided below. | 
| **`C:\ASM_DEV\hello_world.asm`** | Inside your project root. | Your assembly source code. | 

## 3. Configure the Batch Script

Copy the content of the `compile_and_run.bat` file (provided in the next step) into a new file named `compile_and_run.bat` inside your `C:\ASM_DEV\` folder.

**CRITICAL:** You must edit the paths inside the `.bat` file to match your system.

* `set MASM_BIN_DIR=C:\masm32\bin` (Path to where `ml.exe` and `link.exe` are)

* `set LIB_DIR=C:\ASM_DEV\Lib` (Path to where `Irvine32.lib` is)

* `set INC_DIR=C:\ASM_DEV\Inc` (Path to where `Irvine32.inc` is)

## 4. Usage

1. Open your command prompt (Terminal/CMD).

2. Navigate to your working directory (e.g., `cd C:\ASM_DEV`).

3. Use the script to compile, link, and run your code: