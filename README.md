# Uint8CurveRandom
Simple set of functions that picks numbers following a distribution curve

## Weighted random function:
```c
/**
  Curve driven random generator
*/
uint8_t rand_curve(uint8_t (*w_func)(uint8_t, uint8_t), uint8_t max) {
    uint16_t total = 0;

    for (uint8_t i = 0; i < max; i++)
        total += w_func(i, max);

    uint16_t rd = rand() % total;
    uint16_t cumul = 0;

    for (uint8_t i = 0; i < max; i++) {
        cumul += w_func(i, max);
        if (rd < cumul) return i;
    }

    return 0;
}
```

## Distributions:

### distrib_lin_inc

```
value + 1
```
```
▁▁▂▂▃▃▃▄▄▅▅▅▆▆▇
```
### distrib_lin_dec

```
max - value
```
```
▇▆▆▅▅▅▄▄▃▃▃▂▂▁▁
```
### distrib_sym_bell

```
value <= max / 2 ? value + 1 : max - value
```
```
▁▁▂▂▃▃▃▄▃▃▃▂▂▁▁
```
### distrib_exp_inc

```
1 + (value * value) / (max - 1)
```
```
▁▁▁▁▁▁▂▂▃▃▄▄▅▆▇
```
### distrib_exp_dec

```
1 + ((max - 1 - value) * (max - 1 - value)) / (max - 1)
```
```
▇▆▅▄▄▃▃▂▂▁▁▁▁▁▁
```
### distrib_flat

```
1
```
```
▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁
```
### distrib_tri

```
value <= max / 2 ? 2 * value + 1 : 2 * (max - value - 1) + 1
```
```
▁▂▃▃▄▅▆▇▆▅▄▃▃▂▁
```
