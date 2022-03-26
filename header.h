#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cmath>
#include <algorithm>

const int TOKENS {4};
const int DIGITS {8};

typedef std::array<std::array<int, DIGITS>, TOKENS> matrix_4x8;

std::array<std::string, TOKENS> split(std::string str, char delim);
int str_to_int(std::string str);
std::string int_to_str(int num);
std::array<int, DIGITS> dec_to_bin(const int& num);
int bin_to_dec(const std::array<int, DIGITS>& bin);
matrix_4x8 get_addr_bins(const std::string& address);
matrix_4x8 get_mask_bins(const std::string& mask, bool compliment);
std::array<int, DIGITS> comp_bins(std::array<int, DIGITS> bin_1, std::array<int, DIGITS> bin_2, char op);

std::string get_network_id(const std::string& ip_address, const std::string& mask);
std::string get_broadcast_address(const std::string& ip_address, const std::string& mask);
size_t get_ip_integral_equivalent(const std::string& ip_address);
size_t get_subnet_cardinality(std::string mask);
bool check_ip_subnet_membership(const std::string& network_id, const std::string& mask, const std::string& check_ip);

#endif