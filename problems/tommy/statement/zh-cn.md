{{ self.title() }}

## {{ _('Description') }}

可爱的 Tommy 有一棵树。这棵树上只有两个点 $a$ 和 $b$ 是黑色，其它的点都是白色。

每次，Tommy 可以将一个黑色 $p$ 的点染成红色，然后把和 $p$ 相邻的所有白色的点染成黑色。最后，所有的点都会被染成红色。

设第 $i$ 个点是第 $t_i$ 个被染成红色的，那么 $t_i$ 是一个 $1$ 到 $n$ 的排列。Tommy 希望你帮他求出，有多少种不同的 $t_i$。

## {{ _('Input Format') }}

{{ self.input_file() }}

第一行三个数 $n,a,b$，表示树的点数和初始的两个黑色点的编号；

接下来 $n-1$ 行，每行 $x,y$ 描述树上的一条边。

点从 $1$ 开始编号。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出不同的排列 $t_i$ 的个数除以 $998,244,353$ 的余数。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}


## {{ _('Subtasks') }}

$n\le 234,567$
