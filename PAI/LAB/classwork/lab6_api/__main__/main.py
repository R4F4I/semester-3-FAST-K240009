# 1. Start of Execution
print(f"--- Running main.py ---")

# 2. Check __name__ in the current file (main.py)
# Since we are running this file directly, Python sets __name__ to "__main__".
if __name__ == "__main__":
    print(f"Inside main.py, __name__ is: {__name__}")
    print("This code block runs because main.py is the primary script.")

# 3. Import the secondary script
print("\n--- Importing utility.py ---")
import utility 

# 4. Use a function from the imported file
print(f"Calling a function from utility.py...")
utility.greet("Alice")

# 5. End of Execution
print("\n--- Execution Finished ---")
