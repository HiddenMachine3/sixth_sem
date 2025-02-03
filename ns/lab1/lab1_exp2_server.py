import socket
import time

# Server settings
HOST = '0.0.0.0'  # Listen on all interfaces
PORT = 65432      # Port to listen on


def getNetworkDetails():
    hostname = socket.gethostname()
    IP_addr = socket.gethostbyname(hostname)
    fqdn = socket.getfqdn()
    
    print("Host name: ", hostname)
    print("IP address: ", IP_addr)
    print("FQDN: ", fqdn)


print("Lab1: Exp2: Server running on WSL: Welcome !!!")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    getNetworkDetails()
    s.bind((HOST, PORT))
    s.listen()
    print(f"Server listening on {HOST}:{PORT}")
    
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        try:
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received: {data.decode()}")
                response = "Hello, client!"
                conn.sendall(response.encode())
                print(f"Sent: {response}")
                time.sleep(2)  # Wait for 2 seconds before the next interaction
        except KeyboardInterrupt:
            print("Server terminated.")
