# Initialize first two Fibonacci numbers
MOV R0 0x0  # Initialize F(0) = 0
MOV R1 0x1  # Initialize F(1) = 1

# Store initial values in memory
STR R0 0x0040  # Store F(0) at memory location 0x0040
STR R1 0x0042  # Store F(1) at memory location 0x0042

# Compute and store next 23 Fibonacci numbers
MOV R2 0x2      # Initialize counter R2 = 2 (for loop)
MOV R3 0x0044   # Initialize memory location for storing next Fibonacci number

LOOP:
    # Calculate F(R2) = F(R2-1) + F(R2-2)
    ADD R4 R0 R1  # F(R2-1) in R4
    MOV R0 R1     # R0 = F(R2-1)
    MOV R1 R4     # R1 = F(R2-2)

    # Store F(R2) at memory location R3
    STR R1 R3

    # Increment counter and memory location
    ADD R2 R2 0x1  # R2++
    ADD R3 R3 0x2  # R3 += 2 (since each word is 2 bytes)

    # Check loop condition (if counter < 25)
    CMP R2 0x19   # Compare R2 with 25 (0x19 in hex)
    JEQ DONE      # Jump to DONE if counter equals 25
    JMP LOOP      # Otherwise, repeat loop

DONE:
    NOP           # No operation (end of program)
