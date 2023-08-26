# Ping Implementation
<img src="ping.jpg" />
This is a custom implementation of the `ping` utility based on inetutils-2.0. It provides basic functionality for sending ICMP echo request packets to a target host and measuring the round-trip time for the responses.

## Features

- **-n**: Specifies the number of ICMP echo requests to send.
- **-c**: Specifies the number of ICMP echo requests to send.
- **-w**: Specifies the timeout for each ICMP echo request, in milliseconds.
- **-v**: Enables verbose mode, displaying additional output.
- **-q**: Enables quiet mode, displaying minimal output.
- **--ttl**: Sets the Time-to-Live (TTL) value for the ICMP packets.
- **-?**: Displays help and usage information.

## ICMP Packets

ICMP (Internet Control Message Protocol) is a network protocol used for sending error messages and operational information about network conditions. It's commonly used for diagnostic and control purposes within IP networks.

### How ICMP Packets Work

1. **Sending ICMP Request:**
   - A device, often referred to as a "sender," wants to check the reachability of another device (often a host) on the network.
   - The sender encapsulates the data it wants to send within an ICMP echo request packet.
   - The sender attaches an ICMP header to the packet, specifying the type of request (echo request) and other relevant information.
   - The sender then sends this ICMP packet to the target host.

2. **Receiving ICMP Request:**
   - The target host receives the ICMP echo request packet.
   - The host's network stack examines the packet and recognizes it as an ICMP packet.
   - The ICMP layer processes the request, generates an appropriate response, and encapsulates the data within an ICMP echo reply packet.
   - An ICMP header is attached to the reply packet, specifying that it's a reply to the earlier echo request.

3. **Sending ICMP Reply:**
   - The target host sends the ICMP echo reply packet back to the sender.
   - The sender receives the ICMP echo reply and can measure the round-trip time between sending the request and receiving the reply.
   - The sender's ICMP layer analyzes the reply to ensure it matches the original request.

4. **Round-Trip Time Calculation:**
   - The sender calculates the time taken for the echo request to travel to the target host and back as the round-trip time.
   - This round-trip time is often used to estimate network latency.

### Diagram of an ICMP Packet Header
```bash
0                     1                     2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Type      |     Code      |           Checksum            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           Identifier          |        Sequence Number        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|      Data ...                                                 |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
- **Type:** Specifies the type of ICMP message (e.g., Echo Request, Echo Reply, Destination Unreachable, etc.).
- **Code:** Provides more specific information about the ICMP message type.
- **Checksum:** A checksum for error-checking of the ICMP packet.
- **Identifier:** Used to match Echo Requests with corresponding Echo Replies.
- **Sequence Number:** Used to match multiple Echo Requests and Replies.
- **Data:** Additional data carried within the ICMP packet (e.g., original data for Echo Request).

## IP Packets and Headers

IP (Internet Protocol) packets are fundamental units of data in computer networks. Each IP packet consists of two main parts: the IP header and the payload (data). The IP header contains essential information for routing and delivering the packet to its destination.

### IP Header Structure

- **Version:** Indicates the IP protocol version (IPv4 or IPv6).
- **IHL (Internet Header Length):** Specifies the length of the IP header in 32-bit words.
- **Type of Service:** Contains information about the quality of service requested for the packet.
- **Total Length:** Indicates the total length of the IP packet (header + data).
- **Identification:** A unique identifier for the packet (used for reassembly).
- **Flags:** Control fragmentation and reassembly.
- **Fragment Offset:** Position of the fragment in the original datagram.
- **Time to Live (TTL):** Specifies the maximum number of hops the packet can traverse.
- **Protocol:** Identifies the protocol used in the data portion (e.g., ICMP, TCP, UDP).
- **Header Checksum:** Provides error-checking for the header.
- **Source IP Address:** IP address of the sender.
```bash
0                     1                     2                    3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service|          Total Length         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|     Fragment Offset     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Time to Live |    Protocol   |        Header Checksum        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source IP Address                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination IP Address                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                  Options ... (if IHL > 5)                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
- **Version:** Indicates the IP protocol version (IPv4 or IPv6).
- **IHL (Internet Header Length):** Specifies the length of the IP header in 32-bit words.
- **Type of Service:** Contains information about the quality of service requested for the packet.
- **Total Length:** Indicates the total length of the IP packet (header + data).
- **Identification:** A unique identifier for the packet (used for reassembly).
- **Flags:** Control fragmentation and reassembly.
- **Fragment Offset:** Position of the fragment in the original datagram.
- **Time to Live (TTL):** Specifies the maximum number of hops the packet can traverse.
- **Protocol:** Identifies the protocol used in the data portion (e.g., ICMP, TCP, UDP).
- **Header Checksum:** Provides error-checking for the header.
- **Source IP Address:** IP address of the sender.
- **Destination IP Address:** IP address of the intended recipient.
- **Options:** Additional options (if IHL > 5).

</details>

## Prerequisites

- A C compiler (e.g., gcc)
- make

## Building

To build the custom ping utility, follow these steps:

1. Open a terminal window.
2. Navigate to the root directory of the project.
3. Run the following command to compile the code:

   ```bash
   make
   ```

## Usage

To run the custom ping utility, use the following syntax:
```basg
./ping [OPTIONS] [Address]
```
Replace [OPTIONS] with the desired command-line options and [Address] with the target host's IP address or domain name.

### Example
```bash
./ping -c 5 -w 1000 google.com
```
This command will send 5 ICMP echo requests to google.com with a timeout of 1000 milliseconds for each request.

## Options

- **-n**: Specifies the number of ICMP echo requests to send. For example:
   ```bash
  ./ping -n 10 google.co
   ```
- **-c**: Specifies the number of ICMP echo requests to send. For example:
   ```bash
  ./ping -c 3 google.com
    ```
- **-w**: Specifies the timeout for each ICMP echo request, in milliseconds. For example:
   ```bash
  ./ping -w 500 google.com
  ```
- **-v**: Enables verbose mode, displaying additional output. For example:
   ```bash
  ./ping -v google.com
  ```
- **-q**: Enables quiet mode, displaying minimal output. For example:
   ```bash
  ./ping -q google.com
  ```
- **--ttl**: Sets the Time-to-Live (TTL) value for the ICMP packets. For example:
   ```bash
  ./ping --ttl 64 google.com
  ```
- **-?**: Displays help and usage information. For example:
  ```bash
  ./ping -?
  ```
## License
This project is licensed under the MIT License.
