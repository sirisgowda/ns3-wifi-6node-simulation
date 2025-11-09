
# WiFi 6-Node Simulation using NS-3

##  Name
**Siri S Gowda**

---

## Aim
To simulate a **6-node WiFi network** in NS-3 consisting of one Access Point (AP) and five Stations (STAs), visualize the topology in **NetAnim**, and capture packet traces using **PCAP**.

---

## Objectives
- To understand how WiFi communication works in NS-3.
- To configure PHY, MAC, and Internet layers in a wireless network.
- To simulate UDP communication between stations and the access point.
- To visualize node movement and packet exchange using **NetAnim**.
- To analyze packet transmission using **PCAP traces**.

---

## Procedure
1. **Set up NS-3** on your Linux system (`ns-3.45` used here).
2. Create a new simulation file:
   ```bash
   cd ~/ns3/ns-3.45/scratch
   nano wifi-6node.cc
   ```
3. Copy the simulation code below into the file.
4. Build and run:
   ```bash
   ./ns3 run "scratch/wifi-6node"
   ```
5. After successful execution, you’ll see:
   - **wifi-6node.xml** → for NetAnim visualization
   - **wifi-6node-*.pcap** → packet capture files
6. View animation in NetAnim:
   ```bash
   cd ~/netanim/build
   ./netanim ~/ns3/ns-3.45/wifi-6node.xml
   ```

---

## Code
The complete simulation code is available here:
 [wifi-6node.cc](./wifi-6node.cc)

---

## Simulation Details
| Component | Description |
|------------|-------------|
| Nodes | 6 (1 AP + 5 STAs) |
| WiFi Standard | IEEE 802.11b |
| Application | UDP Echo Client-Server |
| Duration | 10 seconds |
| Tracing | PCAP + NetAnim XML |
| Visualization Tool | NetAnim |

---

## Expected Output
- Simulation console messages confirming successful execution.
- **NetAnim GUI** showing all 6 nodes (1 AP + 5 STAs).
- Packet flow visualization between the nodes.

---

## Repository Contents
```
├── wifi-6node.cc       # Simulation code
├── wifi-6node.xml      # NetAnim trace file (generated after running)
├── wifi-6node-*.pcap   # Packet trace files (generated after running)
└── README.md           # Project documentation
```

---


## GitHub Repository
[https://github.com/sirisgowda/ns3-wifi-6node-simulation](https://github.com/sirisgowda/ns3-wifi-6node-simulation)
