#include "include.h"

void get_frequent_token(struct PairCount *frequent_pair, const struct PairCount *pairs, const int num_pairs)
{
    if (frequent_pair == NULL || pairs == NULL || num_pairs <= 0)
    {
        return;
    }

    int i, max_frequency = 0;
    for (i = 0; i < num_pairs; i += 1)
    {
        if (pairs[i].count > max_frequency)
        {
            *frequent_pair = pairs[i];
            max_frequency = pairs[i].count;
        }
    }
}
