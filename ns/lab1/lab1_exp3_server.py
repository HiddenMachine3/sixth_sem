import socket
import threading
import time

# Server settings
HOST = '0.0.0.0'  # Listen on all interfaces
PORTS = [65431, 65432, 65433, 65434, 65435]  # Ports for 5 connections


def handle_client(conn, addr, port, connection_id):
    print(f"Thread-{connection_id}: Handling connection from {addr} on port {port}")
    serial_number = 1
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(f"Thread-{connection_id}: Received {data.decode()} from {addr}")
            response = f"Hello, client! (Message {serial_number})"
            conn.sendall(response.encode())
            print(f"Thread-{connection_id}: Sent {response} to {addr}")
            serial_number += 1
            time.sleep(2)  # Wait 2 seconds
    except ConnectionResetError:
        print(f"Thread-{connection_id}: Connection reset by client.")
    finally:
        print(f"Thread-{connection_id}: Closing connection with {addr}")
        conn.close()


def start_server(port, connection_id):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, port))
        s.listen()
        print(f"Thread-{connection_id}: Server listening on {HOST}:{port}")
        while True:
            conn, addr = s.accept()
            client_thread = threading.Thread(target=handle_client, args=(conn, addr, port, connection_id))
            client_thread.start()


def getNetworkDetails():
    hostname = socket.gethostname()
    IP_addr = socket.gethostbyname(hostname)
    fqdn = socket.getfqdn()
    
    print("Host name: ", hostname)
    print("IP address: ", IP_addr)
    print("FQDN: ", fqdn)


print("Lab1: Exp3: Server running on Windows: Welcome !!!")
getNetworkDetails()

# Start threads for each port
for i, port in enumerate(PORTS):
    server_thread = threading.Thread(target=start_server, args=(port, i + 1))
    server_thread.daemon = True  # Daemonize threads to exit gracefully
    server_thread.start()

# Keep the main thread alive
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("Server shutting down.")
