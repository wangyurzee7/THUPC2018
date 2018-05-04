{{ self.title() }}

## {{ _('Description') }}

我们称一个数 $X$ 是回文数，如果将 $X$ 按照数位从左往右和从右往左写是完全相同的。若 $X$ 同时还是完全平方数，则称其为回文平方数，若 $X$ 的平方根还是回文数，则称 $X$ 为回文平方回文数，例如 $X=14641$ 就是一个回文平方回文数。

对于一个给定的数 $N$，试计算位数不超过 $N$ 的回文平方回文数共有多少个。

## {{ _('Input Format') }}

{{ self.input_file() }}

输入第一行包含两个正整数 $N$，含义如题意所示，数据保证 $N\leq 10^{25}$。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出由一行组成，包含一个正整数，表示位数不超过 $N$ 的回文平方回文数个数。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{%- do vars.__setitem__('sample_id', 2) -%}
{{ self.sample_text() }}
