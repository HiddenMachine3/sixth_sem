import socket
import time


def getNetworkDetails():
    hostname = socket.gethostname()
    IP_addr = socket.gethostbyname(hostname)
    fqdn = socket.getfqdn()
    
    print("Host name: ", hostname)
    print("IP address: ", IP_addr)
    print("FQDN: ", fqdn)


print("Lab1: Exp3: Client running on WSL: Welcome !!!")
getNetworkDetails()

# Server details
HOST = input("Enter the server IP address: ").strip()  # Input the server's IP address
PORT = int(input("Enter the port number (65431-65435): ").strip())  # Input the port number

if PORT not in [65431, 65432, 65433, 65434, 65435]:
    print("Invalid port number! Please enter a port between 65431 and 65435.")
    exit(1)
 
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
        print(f"Connected to server on {HOST}:{PORT}")
        serial_number = 1
        while True:
            message = f"Hello, server! (Message {serial_number})"
            s.sendall(message.encode())
            print(f"Sent: {message}")
            data = s.recv(1024)
            print(f"Received: {data.decode()} from server")
            serial_number += 1
            time.sleep(2)  # Wait for 2 seconds before the next message
    except KeyboardInterrupt:
        print("Client terminated.")
    except ConnectionRefusedError:
        print(f"Connection to {HOST}:{PORT} failed. Is the server running?")
