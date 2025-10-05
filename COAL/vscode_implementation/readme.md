## using any code editor to write asm

- no need to use visual studio
- but you need vs to get MASM
- in MASM you `ml.exe`
- so first get its path
- then get the irvine lib path

- for my example, they are at:
  - `C:\Irvine`
  - `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x86`
  - respectively
- copy these into the `compile.bat`
- now, to compile an `.asm` use:
  - `.\compile.bat .\file.asm`
  - they must in the same location