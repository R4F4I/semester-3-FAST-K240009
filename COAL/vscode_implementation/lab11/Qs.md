
1. Create a procedure named Scan_String to find the index of the first occurrence of the character '#' in the given string.
Str1 BYTE '1278j-3#^&*#*#45^,0
2. Modify the above procedure to take offset of string1 and the character to be searched as argument.
3. Create IsCompare procedure to compare two strings.
4. Create a Str_Reverse procedure to reverse strings.
5. Create a procedure that Loads an array of integer by multiplying it with Load(offset array, byte no)
6. Write the procedure to get_frequency Find the frequency of characters:
.data
target BYTE "AAEBDCFBBC",0
freqTable DWORD 256 DUP(0)
.code
INVOKE Get_frequencies, ADDR target, ADDR freqTable
