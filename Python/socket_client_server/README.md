# Socket Client-Server Tutorial (TCP)

Learn the basics of network communication using Python's built-in `socket` module.

## 📝 Description
This tutorial demonstrates a simple TCP/IP connection between a **Server** and a **Client**. The server waits for a connection and sends data, while the client connects and receives the data. It uses the `socket.gethostname()` to automatically find your computer's local IP address for testing.

## 🛠 Installation
This tutorial uses the standard Python `socket` module. No external `pip` installations are required.

## 🚀 Execution
### 1. Start the Server
Open a terminal and run:
```bash
python Server.py
```
The server will now wait for a connection.

### 2. Start the Client
Open a **second** terminal and run:
```bash
python Client.py
```
You should see the message from the server appeared in the client terminal.

## 📖 Step-by-Step Instructions
1. **Socket Creation**: Both scripts create a socket object using `socket.AF_INET` (IPv4) and `socket.SOCK_STREAM` (TCP).
2. **Setup**:
   - The **Server** binds to a port (e.g., 1234) and listens for incoming connections.
   - The **Client** connects to the server's IP and port.
3. **Communication**:
   - The server accepts the connection and sends a byte-encoded message.
   - The client receives the bytes, decodes them to a string, and prints them.
4. **Header Size**: Notice the `HEADER_SIZE = 10` implementation. This is a common pattern to inform the receiver exactly how many bytes of data to expect.

---
**💡 Discussion**: TCP is a reliable protocol used for web browsing (HTTP), email (SMTP), and file transfers (FTP).
