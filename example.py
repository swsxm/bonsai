import bonsai as bs
import random
import string

NUM_ROWS = 100_000

print(f"--- Generating {NUM_ROWS} rows of test data ---")

bool_col = [random.choice([True, False]) for _ in range(NUM_ROWS)]
char_col = [random.choice(string.ascii_letters) for _ in range(NUM_ROWS)]
int_col = [random.randint(-10**9, 10**9) for _ in range(NUM_ROWS)]
float_col = [random.uniform(-1000.0, 1000.0) for _ in range(NUM_ROWS)]
string_col = [
    ''.join(random.choices(string.ascii_lowercase + " ", k=random.randint(5, 15))) 
    for _ in range(NUM_ROWS)
]

try:
    print("Initializing Bonsai DataFrame...")
    df = bs.DataFrame({
        "bool_test": bool_col,
        "char_test": char_col,
        "int_test": int_col,
        "float_test": float_col,
        "string_test": string_col
    })
    print(df)
    print(df.get_shape())
    print(df.head(10))
    print(df.tail(3))
    
    
except Exception as e:
    print(f"An error occurred during testing: {e}")