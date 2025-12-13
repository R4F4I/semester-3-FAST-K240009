def decrypt_caesar(ciphertext, key=3):
    """Decrypts a message using the Caesar Cipher (shift k=3)."""
    
    # Decryption key is the negative of the encryption key
    decryption_key = -key 
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    
    decrypted_text = ""
    table_data = []

    for char in ciphertext:
        if char.isalpha():
            # C_val: Ciphertext index (C)
            C_val = alphabet.find(char.upper())
            
            # P_val: Decryption function P = (C - k) mod 26
            P_val = (C_val + decryption_key) % 26 
            
            # P_char: Plaintext character (P)
            P_char = alphabet[P_val]
            
            table_data.append([char.upper(), C_val, P_val, P_char])
            decrypted_text += P_char
        else:
            # Handle spaces
            table_data.append([char, '—', '—', char])
            decrypted_text += char

    return decrypted_text, table_data

# --- Execution ---
# Input data derived from Q13(b)(i): "PLG WZR"
cipher_input = "IDVW QXFHV XQLYHUVLWB"
plain_text, table = decrypt_caesar(cipher_input)

# --- Print Table ---
print("## 🔐 Caesar Cipher Decryption (Shift k=-3)")
print(f"Ciphertext: {cipher_input}")
print(f"Plaintext: {plain_text}")
print("\n" + "="*40)
print("C-Letter | C-Value | P-Value | P-Letter")
print("="*40)

for row in table:
    # f-string formatting for alignment
    print(f"{row[0]:^8} | {row[1]:^7} | {row[2]:^7} | {row[3]:^8}")

print("="*40)