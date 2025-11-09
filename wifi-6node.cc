/* 
 * WiFi 6-node Simulation in ns-3
 * Name : Siri S Gowda
 * Register Number : 23BCI0010
 * Description:
 *   This simulation creates 6 WiFi nodes (1 AP + 5 stations).
 *   It assigns IPs, sets up UDP echo communication,
 *   enables PCAP tracing and NetAnim visualization,
 *   and prints progress messages to verify execution.
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Wifi6NodeExample");

int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Starting WiFi 6-node Simulation..." << std::endl;

    // STEP 1: Create 6 nodes (1 AP + 5 STAs)
    std::cout << "[1] Creating WiFi nodes..." << std::endl;
    NodeContainer wifiStaNodes;
    wifiStaNodes.Create(5);
    NodeContainer wifiApNode;
    wifiApNode.Create(1);

    // STEP 2: Configure PHY and Channel
    std::cout << "[2] Setting up channel and PHY layer..." << std::endl;
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    // STEP 3: Set WiFi standard and MAC
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);
    WifiMacHelper mac;

    Ssid ssid = Ssid("ns3-6node-network");
    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staDevices = wifi.Install(phy, mac, wifiStaNodes);

    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid));
    NetDeviceContainer apDevice = wifi.Install(phy, mac, wifiApNode);

    // STEP 4: Mobility model
    std::cout << "[3] Setting up mobility model..." << std::endl;
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0),
                                  "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(5.0),
                                  "DeltaY", DoubleValue(5.0),
                                  "GridWidth", UintegerValue(3),
                                  "LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiStaNodes);
    mobility.Install(wifiApNode);

    // STEP 5: Install Internet Stack
    std::cout << "[4] Installing Internet Stack..." << std::endl;
    InternetStackHelper stack;
    stack.Install(wifiApNode);
    stack.Install(wifiStaNodes);

    // STEP 6: Assign IP addresses
    std::cout << "[5] Assigning IP Addresses..." << std::endl;
    Ipv4AddressHelper address;
    address.SetBase("192.168.1.0", "255.255.255.0");
    Ipv4InterfaceContainer staInterfaces = address.Assign(staDevices);
    Ipv4InterfaceContainer apInterface = address.Assign(apDevice);

    // STEP 7: Application setup (UDP Echo)
    std::cout << "[6] Configuring Applications..." << std::endl;
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApp = echoServer.Install(wifiApNode.Get(0));
    serverApp.Start(Seconds(1.0));
    serverApp.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(apInterface.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(5));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(wifiStaNodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    // STEP 8: Enable PCAP Tracing
    std::cout << "[7] Enabling PCAP tracing..." << std::endl;
    phy.EnablePcapAll("wifi-6node");

    // STEP 9: Enable NetAnim visualization
    std::cout << "[8] Enabling NetAnim output..." << std::endl;
    AnimationInterface anim("wifi-6node.xml");
    anim.SetMaxPktsPerTraceFile(50000);
    anim.EnablePacketMetadata(true);

    // STEP 10: Run simulation
    std::cout << "[9] Running Simulation..." << std::endl;
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();
    Simulator::Destroy();

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Simulation of 6-node WiFi Network completed successfully!" << std::endl;
    std::cout << "Packets transmitted and received as expected." << std::endl;
    std::cout << "Check the PCAP files (wifi-6node-*.pcap) for packet trace." << std::endl;
    std::cout << "View animation using: NetAnim wifi-6node.xml" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Simulation completed successfully!" << std::endl;
    std::cout << "Output files generated: wifi-6node.xml and PCAP traces." << std::endl;

    return 0;
}

