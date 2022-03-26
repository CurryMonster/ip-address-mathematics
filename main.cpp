#include "header.h"

int main() {
    std::cout << "Network ID: " << get_network_id("192.168.2.10", "20") << std::endl;
    std::cout << "Broadcast Address: " << get_broadcast_address("192.168.2.10", "20") << std::endl;
    std::cout << "IP Integer Form: " << get_ip_integral_equivalent("192.168.2.10") << std::endl;
    std::cout << "Subnet Cardinality: " << get_subnet_cardinality("24") << std::endl;

    if (check_ip_subnet_membership("192.168.0.0", "24", "192.168.1.13")) 
        std::cout << "Chosen ip address is a member of subnet" << "\n";
    else
        std::cout << "Chosen ip address is not a member of subnet" << "\n";

    return 0;
}