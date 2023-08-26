#include "ft_ping.h"

/** @Brief Init Args
 * Initialize args struct
 *
 * @param none
 * @return t_args*
 */
t_args  *init_args( void )
{
    t_args *args;

    args = (t_args *) malloc(sizeof(t_args) * 1);
    if (args == NULL)
        return (args);
    args->invalid_option = 0;
    args->hostname = NULL;
    args->options = 0;
    args->ttl = DEFAULT_TTL;
    args->timeout = 1;
    args->quite = 0;
    args->count = 0;
    args->count_valid = 0;
    return (args);
}

void    check_args_validity()
{
    if (g_ping->args->options & OPT_COUNT)
    {
        if (g_ping->args->count > 0)
            g_ping->args->count_valid = 1;
    }
}

size_t
ping_cvt_number (const char *optarg, size_t maxval, int allow_zero)
{
  char *p;
  unsigned long int n;

  n = strtoul (optarg, &p, 0);
  if (*p)
    show_errors(concatenate_strings("ft_ping: invalid value (`%s' near `%s')\n", optarg, p),EXIT_FAILURE);

  if (n == 0 && !allow_zero)
    show_errors(concatenate_strings("ft_ping: option value too small: %s\n", optarg) ,EXIT_FAILURE);

  if (maxval && n > maxval)
    show_errors(concatenate_strings("ft_ping: option value too big: %s\n", optarg) ,EXIT_FAILURE);

  return n;
}

/**
 * @brief Parsing command line
 * parse command line argumments 
 * and store valid arguments in t_args struct
 */
void    parse_clo(int len, char *clo_args[]) {
    int i;
    
    i = 1;
    g_ping->args = init_args();
    if (g_ping->args == NULL)
        show_errors("ft_ping: can't allocate memory\n", EX_OSERR);
    // TO-DO: Parsing only valid options and break if any invalid_option appears
    while (i < len)
    {
        if (ft_strncmp(clo_args[i], "-?", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--help", ft_strlen(clo_args[i])) == 0)
            g_ping->args->options |= OPT_HELP;
        else if (ft_strncmp(clo_args[i], "-v", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--verbose", ft_strlen(clo_args[i])) == 0)
            g_ping->args->options |= OPT_VERBOSE;
        else if (ft_strncmp(clo_args[i], "-c", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--count", ft_strlen(clo_args[i])) == 0)
        {
            g_ping->args->options |= OPT_COUNT;
            if (!clo_args[i + 1])
                show_errors("ft_ping: option requires an argument -- 'c'\n", EX_USAGE);
            g_ping->args->count = ping_cvt_number (clo_args[i + 1], 0, 1);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-n", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--numeric", ft_strlen(clo_args[i])) == 0)
            g_ping->args->options |= OPT_NUMERIC;
        else if (ft_strncmp(clo_args[i], "--ttl", ft_strlen(clo_args[i])) == 0)
        {
            g_ping->args->options |= OPT_TTL;
            if (!clo_args[i + 1])
                show_errors("ft_ping: option '--ttl' requires an argument\n", EX_USAGE);
            g_ping->args->ttl = ping_cvt_number (clo_args[i + 1], 255, 0);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-w", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--deadline", ft_strlen(clo_args[i])) == 0)
        {
            g_ping->args->options |= OPT_TIMEOUT;
            if (!clo_args[i + 1])
                show_errors("ft_ping: option requires an argument -- 'w'\n", EX_USAGE);
            g_ping->args->timeout = ping_cvt_number (clo_args[i + 1], INT_MAX, 0);
            i++;
        }
        else if (ft_strncmp(clo_args[i], "-q", ft_strlen(clo_args[i])) == 0 || ft_strncmp(clo_args[i], "--quite", ft_strlen(clo_args[i])) == 0)
            g_ping->args->options |= OPT_QUIET;
        else if (clo_args[i][0] != '-' && !g_ping->args->hostname)
            g_ping->args->hostname = strdup(clo_args[i]);
        else if (clo_args[i][0] == '-')
            show_errors(concatenate_strings("ft_ping: invalid option -- %s\n", &clo_args[i][1]), EX_USAGE);
        i++;
    }
    if (g_ping->args->options & OPT_HELP)
        show_errors("", EX_HELP);
    if (!g_ping->args->hostname)
        show_errors("ft_ping: missing host operand\n", EX_USAGE);
}
