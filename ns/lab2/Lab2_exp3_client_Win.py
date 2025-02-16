import socket
import time

HOST = '172.18.31.55'
PORT = 65431

def getNetworkDetails():
    hostname = socket.gethostname()
    IP_addr  = socket.gethostbyname(hostname)
    fqdn     = socket.getfqdn()

    print("Host name:", hostname)
    print("IP address:", IP_addr)
    print("FQDN:", fqdn)

print("Lab2: Exp3: Client running on Windows: Welcome!!!")
getNetworkDetails()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    for i in range(5):
        message = f"Hello, server! {i+1}"
        s.sendall(message.encode())
        data = s.recv(1024)
        print(f"Received '{data.decode()}' from server")
        time.sleep(2)