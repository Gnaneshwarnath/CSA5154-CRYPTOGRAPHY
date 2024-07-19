def generate_table(key):
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    table = []
    for char in key:
        if char not in table and char in alphabet:
            table.append(char)
    for char in alphabet:
        if char not in table:
            table.append(char)
    table = [table[i:i + 5] for i in range(0, len(table), 5)]
    return table

def prepare_text(text):
    text = text.upper()
    text = text.replace(" ", "")
    text = text.replace("J", "I")
    text = ''.join([char for char in text if char.isalpha()])
    if len(text) % 2 != 0:
        text += "X"
    return text

def playfair_cipher_encrypt(table, text):
    cipher_text = ""
    for i in range(0, len(text), 2):
        char1 = text[i]
        char2 = text[i + 1]
        row1, col1 = [(index, row.index(char1)) for index, row in enumerate(table) if char1 in row][0]
        row2, col2 = [(index, row.index(char2)) for index, row in enumerate(table) if char2 in row][0]
        if row1 == row2:
            cipher_text += table[row1][(col1 + 1) % 5] + table[row2][(col2 + 1) % 5]
        elif col1 == col2:
            cipher_text += table[(row1 + 1) % 5][col1] + table[(row2 + 1) % 5][col2]
        else:
            cipher_text += table[row1][col2] + table[row2][col1]
    return cipher_text

def playfair_cipher_decrypt(table, text):
    plain_text = ""
    for i in range(0, len(text), 2):
        char1 = text[i]
        char2 = text[i + 1]
        row1, col1 = [(index, row.index(char1)) for index, row in enumerate(table) if char1 in row][0]
        row2, col2 = [(index, row.index(char2)) for index, row in enumerate(table) if char2 in row][0]
        if row1 == row2:
            plain_text += table[row1][(col1 - 1) % 5] + table[row2][(col2 - 1) % 5]
        elif col1 == col2:
            plain_text += table[(row1 - 1) % 5][col1] + table[(row2 - 1) % 5][col2]
        else:
            plain_text += table[row1][col2] + table[row2][col1]
    return plain_text

key = "PLAYFAIR"
text = "HELLO"

table = generate_table(key)
text = prepare_text(text)
print("192210248:")
cipher_text = playfair_cipher_encrypt(table, text)
print("Cipher Text: ", cipher_text)

plain_text = playfair_cipher_decrypt(table, cipher_text)
print("Plain Text: ", plain_text)