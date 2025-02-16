import socket

# Replace with the IP address from 'ifconfig' in WSL
HOST = '172.18.31.55'  # WSL IP address
PORT = 65431             # Must match the server's port

def getNetworkDetails():
    """Displays the hostname, IP address, and FQDN of the Windows client."""
    hostname = socket.gethostname()
    IP_addr  = socket.gethostbyname(hostname)
    fqdn     = socket.getfqdn()

    print("Host name:", hostname)
    print("IP address:", IP_addr)
    print("FQDN:", fqdn)

print("Lab2: Exp2: Client running on Windows: Welcome!!!")
getNetworkDetails()

# Create a TCP socket and connect to the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    # Send message to server
    message = "Hello, server!"
    s.sendall(message.encode())  # Convert string to bytes before sending
    
    # Receive and print response
    data = s.recv(1024)  # Buffer size: 1024 bytes
    print(f"Received '{data.decode()}' from server")  # Decode bytes to string