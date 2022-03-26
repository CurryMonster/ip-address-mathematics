# ip-address-mathematics
Currently, I am enrolled in "Networking Concepts with Socket Programming - Academic Level" (Udemy course) created by Abhishek CSEPracticals, Shiwani Nigam, and Ekta Ekta. This repository is a custom solution to the Section 3 (IP Subnet) coding exercise, written in C/C++.  Given the IP Address and Mask, users of this module can calculate the Network ID, Broadcast Address, and Subnet Cardinality.  

After cloning/downloading this repository, in the terminal/command prompt, enter the following (while in the project's root directory): 

```
mkdir build 
cd build  
```
Then, in the terminal/command prompt, enter: 
```
cmake .. 
cmake --build . 
```

For Windows (MinGW-w64 compiler), enter:
```
cmake .. -G "MinGW Makefiles"
cmake --build .
```
Run the executable "prog" (method of running the executable is dependent on the user's operating system). Make sure both a C/C++ compiler and CMake are installed and configured as PATH variables. Here's how to apply the module:
```
#include "header.h"

int main() {
  std::cout << "Network ID: " << get_network_id("192.168.2.10", "20") << std::endl;
  return 0;
}
```

Program output:
```
Network ID: 192.168.0.0
```

Refer to "main.cpp" on how to calculate other computer networking parameters.
