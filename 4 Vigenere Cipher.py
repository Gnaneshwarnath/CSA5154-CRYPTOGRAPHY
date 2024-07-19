def generate_key(text, key):
    key = list(key)
    if len(text) == len(key):
        return key
    else:
        for i in range(len(text) - len(key)):
            key.append(key[i % len(key)])
    return "".join(key)

def vigenere_encrypt(text, key):
    encrypted_text = []
    key = generate_key(text, key)
    for i in range(len(text)):
        if text[i].isalpha():
            shift = (ord(text[i].upper()) + ord(key[i].upper())) % 26
            encrypted_char = chr(shift + ord('A'))
            if text[i].islower():
                encrypted_text.append(encrypted_char.lower())
            else:
                encrypted_text.append(encrypted_char)
        else:
            encrypted_text.append(text[i])
    return "".join(encrypted_text)

def vigenere_decrypt(cipher_text, key):
    decrypted_text = []
    key = generate_key(cipher_text, key)
    for i in range(len(cipher_text)):
        if cipher_text[i].isalpha():
            shift = (ord(cipher_text[i].upper()) - ord(key[i].upper()) + 26) % 26
            decrypted_char = chr(shift + ord('A'))
            if cipher_text[i].islower():
                decrypted_text.append(decrypted_char.lower())
            else:
                decrypted_text.append(decrypted_char)
        else:
            decrypted_text.append(cipher_text[i])
    return "".join(decrypted_text)

# Example usage:
text = "HELLO WORLD"
key = "KEY"
cipher_text = vigenere_encrypt(text, key)
print("Encrypted:", cipher_text)
decrypted_text = vigenere_decrypt(cipher_text, key)
print("Decrypted:", decrypted_text)
print("192210248")