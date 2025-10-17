# 1. Check __name__ in the current file (utility.py)

# When main.py imports this file, Python sets __name__ to the file's name ("utility").
print(f"Inside utility.py, __name__ is: {__name__}")

def greet(name):
    """A function defined in the utility module."""
    print(f"Hello, {name}! (from utility.py)")

# 2. The gatekeeper block: This code will NOT run when imported.
if __name__ == "__main__":
    print("\n--- WARNING: This block should NOT run when imported! ---")
    print("This is code intended ONLY for direct execution.")
    greet("Direct Runner")
