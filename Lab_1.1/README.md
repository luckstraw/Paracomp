# Laboratory Activity # 1.1: Parallel and Distributed Computing Example

## Running the Program
Running the Prallel:

1. **Make the code executable then run the program**:
```bash
chmod +x run.sh
```
```bash
./run_Cpp.sh
```

Running the Distributed (Client-Server Model)

1. **Run the server_code.py**
```bash
python3 server_code.py
```

2. **Open another Terminal then run the client_code.py**
```bash
python3 client_code.py
```

## Output

### Parallel Computing Example (Using OpenMP in C++)
After running you will see something like this in terminal: 

```bash
Hello from thread 4
Hello from thread 1
Hello from thread 6
Hello from thread 7
Hello from thread 2
Hello from thread 0
Hello from thread 3
Hello from thread 5
```

### Distributed Computing Example (Client-Server Model in Python)
After running you will see something like this in terminal: 

Server's Terminal:
```bash
Server is waiting for connection...
Connected to ('127.0.0.1', 42451)
```

Client's Terminal:
```bash
Hello from server
```