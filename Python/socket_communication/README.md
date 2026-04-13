# Advanced Socket Communication

This folder contains advanced networking examples using Python's `socket` module, covering data transmission, object serialisation, and a multi-client chat system.

## 🚀 Tutorials

### 1. Data Transmission (`1.DATA_TRANS_SEND`)
Similar to the basic Client-Server tutorial, but focuses on the logic of sending larger data chunks with headers to ensure reliable transmission.

### 2. Socket Pickle (`2.SOCKET_PICKLE`)
Learn how to send entire Python objects (lists, dictionaries, classes) over a network using the `pickle` module.
- **Server**: Serialises an object using `pickle.dumps()` and sends it.
- **Client**: Receives the data and de-serialises it back into a Python object using `pickle.loads()`.

### 3. Socket Chat (`3.SOCKET_CHAT`)
A real-time chat application.
- **Server**: Acts as a hub, receiving messages and broadcasting them to all connected clients.
- **Client**: Connects to the hub to send and receive messages from other users.

## 🛠 Installation
These tutorials use standard Python libraries (`socket`, `pickle`, `select`). No external `pip` installations are required.

## 🚀 Execution
For any of these tutorials:
1. Navigate to the specific subfolder (e.g., `cd 3.SOCKET_CHAT`).
2. Run the **Server** first: `python server.py`.
3. Run one or more **Clients** in separate terminals: `python client.py`.

## 📖 Key Concepts
- **Serialisation**: Converting a Python object into a stream of bytes.
- **Non-blocking I/O**: Using the `select` module in the chat server to handle multiple client connections simultaneously without the program getting "stuck" waiting for one user to type.

---
**💡 Discussion**: Socket programming is the foundation of almost all internet communication. Understanding these low-level concepts helps you better understand higher-level protocols like REST APIs and WebSockets.
