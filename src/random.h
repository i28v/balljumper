#ifndef RANDOM_H
#define RANDOM_H

extern unsigned int random_seed;

inline void set_seed(unsigned int seed)
{
    random_seed = seed;
}

inline unsigned int randint()
{
    random_seed ^= random_seed << 13;
    random_seed ^= random_seed >> 17;
    random_seed ^= random_seed << 5;
    return random_seed;
}

inline unsigned int randint_range(unsigned int min, unsigned int max)
{
    return (randint() % (max + 1 - min) + min);
}

#endif
