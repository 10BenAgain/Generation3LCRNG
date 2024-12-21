from math import ceil, floor


def calc_other_stat_iv(base_stat, ev, level, stat, nature):
    return ceil((ceil(stat / nature) - 5) / (level / 100) - floor(ev / 4) - 2 * base_stat)


# Attack Stat
base_stat = 85
ev = 0
level = 25
nature = 1  # Relaxed
stat = 47

min_iv = min(max(calc_other_stat_iv(base_stat, ev, level, stat, nature), 0), 31)
max_iv = min(max(calc_other_stat_iv(base_stat, ev, level, stat + 1, nature) - 1, 0), 31)
print(calc_other_stat_iv(base_stat, ev, level, stat, nature))
print(calc_other_stat_iv(base_stat, ev, level, stat + 1, nature) - 1)

print(max(calc_other_stat_iv(base_stat, ev, level, stat, nature), 0))
print(max(calc_other_stat_iv(base_stat, ev, level, stat + 1, nature) - 1, 0))
print(min_iv, max_iv)
