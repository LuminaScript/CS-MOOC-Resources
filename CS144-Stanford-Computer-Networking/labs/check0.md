## 1. Set up GNU/Linux on your computer
- Download packages on Ubuntu:
  ```
  sudo apt update && sudo apt install git cmake gdb build-essential clang \
              clang-tidy clang-format gcc-doc pkg-config glibc-doc tcpdump tshark
  ```
## 2. Networking by Hand
### 2.1 Fetch a Web page
```
ubuntu@primary:~$ telnet cs144.keithw.org http
Trying 104.196.238.229...
Connected to cs144.keithw.org.
Escape character is '^]'.
GET /hello HTTP/1.1
Host: cs144.keithw.org
Connection: close

HTTP/1.1 200 OK
Date: Wed, 29 Nov 2023 22:30:12 GMT
Server: Apache
Last-Modified: Thu, 13 Dec 2018 15:45:29 GMT
ETag: "e-57ce93446cb64"
Accept-Ranges: bytes
Content-Length: 14
Connection: close
Content-Type: text/plain

Hello, CS144!
Connection closed by foreign host.
```
### 2.2 Send yourself an email
