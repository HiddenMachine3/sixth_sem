import socket
import time

# Server address (replace with the server's IP)
HOST = '127.0.0.1'  # WSL: IP address assigned on Ubuntu
PORT = 65432        # Same port as the server


def getNetworkDetails():
    hostname = socket.gethostname()
    IP_addr = socket.gethostbyname(hostname)
    fqdn = socket.getfqdn()
    
    print("Host name: ", hostname)
    print("IP address: ", IP_addr)
    print("FQDN: ", fqdn)


print("Lab1: Exp2: Client running on Windows: Welcome !!!")
getNetworkDetails()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    try:
        while True:
            message = "Hello, server!"
            s.sendall(message.encode())
            print(f"Sent: {message}")
            data = s.recv(1024)
            print(f"Received: {data.decode()} from server")
            time.sleep(2)  # Wait for 2 seconds before sending the next message
    except KeyboardInterrupt:
        print("Client terminated.")
