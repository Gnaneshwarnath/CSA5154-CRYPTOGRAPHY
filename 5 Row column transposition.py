
import math

def create_grid(text, key, fill_char='x'):
    # Calculate number of rows
    num_rows = math.ceil(len(text) / len(key))
    grid = []
    
    # Fill the grid row by row
    for i in range(num_rows):
        start_index = i * len(key)
        row = list(text[start_index:start_index + len(key)])
        
        # If the row is shorter than the key length, pad it with the fill_char
        while len(row) < len(key):
            row.append(fill_char)
        
        grid.append(row)
    
    return grid

def row_column_encrypt(text, key):
    grid = create_grid(text, key)
    sorted_key = sorted(list(key))
    
    encrypted_text = ''
    for char in sorted_key:
        col_index = key.index(char)
        for row in grid:
            encrypted_text += row[col_index]
    
    return encrypted_text

def row_column_decrypt(cipher_text, key):
    num_rows = math.ceil(len(cipher_text) / len(key))
    num_cols = len(key)
    
    # Calculate the number of full columns and partial columns
    full_cols = len(cipher_text) % num_cols
    partial_col_len = num_rows if full_cols == 0 else num_rows - 1
    
    # Create an empty grid
    grid = [['' for _ in range(num_cols)] for _ in range(num_rows)]
    
    sorted_key = sorted(list(key))
    index = 0
    
    for char in sorted_key:
        col_index = key.index(char)
        for row in range(num_rows):
            if (row == num_rows - 1) and (col_index >= full_cols):
                break
            grid[row][col_index] = cipher_text[index]
            index += 1
    
    decrypted_text = ''.join([''.join(row) for row in grid]).rstrip('x')
    
    return decrypted_text

# Example usage:
text = "HELLO WORLD"
key = "SECRET"
cipher_text = row_column_encrypt(text, key)
print("Encrypted:", cipher_text)
decrypted_text = row_column_decrypt(cipher_text, key)
print("Decrypted:", decrypted_text)
print("192210248")
