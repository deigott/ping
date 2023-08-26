#include "ft_ping.h"

void update_rtt_stats() {
    if (g_ping->ping_data->packets_received == 1) {
        g_ping->ping_data->rtt_min = g_ping->rtt;
        g_ping->ping_data->rtt_max = g_ping->rtt;
    } else {
        if (g_ping->rtt < g_ping->ping_data->rtt_min) {
            g_ping->ping_data->rtt_min = g_ping->rtt;
        }
        if (g_ping->rtt > g_ping->ping_data->rtt_max) {
            g_ping->ping_data->rtt_max = g_ping->rtt;
        }
    }
    g_ping->ping_data->rtt_total += g_ping->rtt;
}

void    show_help()
{
    printf("Usage: ft_ping [options] [destination]\n\n"
       "Description:\n"
       "ft_ping is a command-line utility that sends Internet Control Message Protocol (ICMP) Echo Request packets to a specified destination host and measures the round-trip time for each packet. It can be used to test the connectivity and responsiveness of network hosts.\n\n"
       "Options:\n"
       "  -v, --verbose       Enable verbose mode, displaying detailed output during execution.\n"
       "  -q, --quiet         Run in quiet mode, suppressing most output except for essential information.\n"
       "  -c, --count <num>   Specify the number of ICMP packets to send before stopping the operation.\n"
       "  -w, --deadline <t>  Set a time limit for the execution, stopping after the specified time (in seconds).\n"
       "  -n, --numeric       Display numeric IP addresses instead of attempting to resolve hostnames.\n"
       "  --ttl <ttl>         Set the Time-to-Live (TTL) value for the sent packets.\n"
       "  -?, --help          Display this help message and exit.\n\n"
       "Note:\n"
       "- The utility may require administrative privileges to create raw sockets for ICMP communication.\n"
       "- Some options might be specific to certain implementations of 'ft_ping' and may not be available on all systems.\n"
       "- Care should be taken when using the '-c' and '-w' options together, as the utility will stop when either the packet count or the deadline is reached.\n"
    );
    return ;
}