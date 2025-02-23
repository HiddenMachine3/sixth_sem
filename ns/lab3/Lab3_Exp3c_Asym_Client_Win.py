import socket
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import padding

HOST = '172.18.31.55'  # Change to WSL IP address
PORT = 65432

# Load the server's public key
with open("public.pem", "rb") as key_file:
    public_key = serialization.load_pem_public_key(key_file.read())

# Load the client's private key
with open("private.pem", "rb") as key_file:
    private_key = serialization.load_pem_private_key(key_file.read(), password=None)

# Encrypt the message with the server's public key
message = b"Hello from asymmetric client"
ciphertext = public_key.encrypt(
    message,
    padding.PKCS1v15()
)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(ciphertext)
    
    # Receive the first response message
    data = s.recv(512)
    server_response = private_key.decrypt(data, padding.PKCS1v15())
    print("Received encrypted data from server:", data.hex())
    print("Received decrypted data:", server_response.decode())

    additional_data = s.recv(512)
    additional_message = private_key.decrypt(additional_data, padding.PKCS1v15())
    print("\nAdditional message from server (Hex):", additional_data.hex())
    print("\nAdditional message from server (Decrypted):", additional_message.decode())
