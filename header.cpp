#include "header.h"

std::array<std::string, TOKENS> split(std::string str, char delim) {
    std::array<std::string, TOKENS> tokens;
    std::stringstream ss {str};
    std::string token;
    for (int i {0}; getline(ss, token, delim); i++)
        tokens.at(i) = token;
    return tokens;
}

int str_to_int(std::string str) {
    int num;
    std::stringstream ss {str};
    ss >> num;
    return num;
}

std::array<int, DIGITS> dec_to_bin(const int& num) {
    std::array<int, DIGITS> bin {};
    int q {num};
    for (int i {0}; q > 0; i++) {
        bin.at(i) = q % 2;
        q /= 2;
    }
    std::reverse(bin.begin(), bin.end());
    return bin;
}

matrix_4x8 get_addr_bins(const std::string& address) {
    matrix_4x8 bins {};

    std::array<std::string, TOKENS> tokens = split(address, '.');

    int i {0};
    std::for_each(tokens.begin(), tokens.end(), [&](const auto& x){
        bins.at(i) = dec_to_bin(str_to_int(x));
        i += 1;
    });

    return bins;
}

matrix_4x8 get_mask_bins(const std::string& mask, bool compliment) {
    matrix_4x8 bins {};
    int counter {0};

    if (!compliment) {
        for (auto& i: bins) {
            for (auto& j: i) {
                if (counter < str_to_int(mask)) {
                    j = 1;
                    counter += 1;
                } 
                else 
                    j = 0;
            }
        }
    }

    if (compliment) {
        for (auto& i: bins) {
            for (auto& j: i) {
                if (counter < str_to_int(mask)) {
                    j = 0;
                    counter += 1;
                } 
                else 
                    j = 1;
            }
        }
    }

    return bins;
}

std::array<int, DIGITS> comp_bins(std::array<int, DIGITS> bin_1, std::array<int, DIGITS> bin_2, char op) {
    std::array<int, DIGITS> res;
    switch(op) {
        case '&':
            for (size_t i {0}; i < DIGITS; i++)
                res.at(i) = bin_1.at(i) & bin_2.at(i);
            break;
        case '|':
            for (size_t i {0}; i < DIGITS; i++)
                res.at(i) = bin_1.at(i) | bin_2.at(i);
            break;
        default:
            std::cout << "Error comparing binary numbers...\n";
    }
    return res;
}

int bin_to_dec(const std::array<int, DIGITS>& bin) {
    int num {0};
    size_t exp {bin.size() - 1};
    std::for_each(bin.begin(), bin.end(), [&](const auto& x) {
        num += x * std::pow(2, exp);
        exp -= 1;
    });
    return num;
}

std::string int_to_str(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

std::string get_network_id(const std::string& ip_address, const std::string& mask) {
    std::string network_id;

    matrix_4x8 ip_addr_bins = get_addr_bins(ip_address);
    matrix_4x8 mask_bins = get_mask_bins(mask, false);

    matrix_4x8 res;
    size_t i {0};
    std::for_each(res.begin(), res.end(), [&](auto& x){
        x = comp_bins(ip_addr_bins.at(i), mask_bins.at(i), '&');
        i += 1;
    });

    size_t count {0};
    std::for_each(res.begin(), res.end(), [&](const auto& x){
        if (count == res.size() - 1)
            network_id += int_to_str(bin_to_dec(x));
        else {
            network_id += int_to_str(bin_to_dec(x)) + ".";
            count += 1;
        }
    });

    return network_id;
}

std::string get_broadcast_address(const std::string& ip_address, const std::string& mask) {

    std::string network_id = get_network_id(ip_address, mask);
    matrix_4x8 network_id_bins = get_addr_bins(network_id);

    matrix_4x8 mask_bins = get_mask_bins(mask, true);

    matrix_4x8 res;
    for (size_t i {0}; i < TOKENS; i++)
        res.at(i) = comp_bins(network_id_bins.at(i), mask_bins.at(i), '|'); 

    std::string broadcast_id;
    for (size_t i {0}; i < res.size(); i++) {
        if (i == res.size() - 1)
            broadcast_id += int_to_str(bin_to_dec(res.at(i)));
        else 
            broadcast_id += int_to_str(bin_to_dec(res.at(i))) + ".";
    }
    return broadcast_id;
}

size_t get_ip_integral_equivalent(const std::string& ip_address) {
    size_t sum {0};
    auto tokens = split(ip_address, '.');
    int exp {tokens.size() - 1};
    std::for_each(tokens.begin(), tokens.end(), [&](const auto& x){
        sum += str_to_int(x) * std::pow(256, exp);
        exp--;
    });
    return sum;
}

size_t get_subnet_cardinality(std::string mask) {
    return std::pow(2, 32 - str_to_int(mask)) - 2;
}

bool check_ip_subnet_membership(const std::string& network_id, const std::string& mask, const std::string& check_ip) {
    auto check_network_id = get_network_id(check_ip, mask);
    return (network_id == check_network_id) ? true : false;
}