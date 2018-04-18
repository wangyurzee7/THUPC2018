{{ self.title() }}

## {{ _('Background') }}

1977年，罗纳德·李维斯特（Ron Rivest）、阿迪·萨莫尔（Adi Shamir）和伦纳德·阿德曼（Leonard Adleman）提出了RSA 加密算法。RSA 加密算法是一种非对称加密算法，其可靠性由极大整数因数分解的难度决定。换言之，对一极大整数做因数分解愈困难，RSA 算法愈可靠。假如有人找到一种快速因数分解的算法的话，那么用 RSA 加密的信息的可靠性就肯定会极度下降。

RSA 的基本原理如下：

- 公钥与私钥的产生
  1. 随机选择两个不同大质数 $p$ 和 $q$，计算 $N=p\times q$
  2. 根据欧拉函数，求得 $r=\varphi (N)=\varphi (p)\varphi (q)=(p-1)(q-1)$
  3. 选择一个小于 $r$ 的整数 $e$，使 $e$ 和 $r$ 互质。并求得 $e$ 关于 $r$ 的模反元素，命名为 $d$，有 $ed\equiv 1 \pmod r$
  4. 将 $p$ 和 $q$ 的记录销毁。此时，$(N,e)$ 是公钥，$(N,d)$ 是私钥。
- 消息加密
  - 首先需要将消息 $m$ 以一个双方约定好的格式转化为一个小于 $N$，且与 $N$ 互质的整数 $n$。如果消息太长，可以将消息分为几段，这也就是我们所说的块加密，后对于每一部分利用如下公式加密：

$$
n^{e}\equiv c\pmod N
$$

- 消息解密
  - 利用密钥 $d$ 进行解密。

$$
c^{d}\equiv n\pmod N
$$

## {{ _('Description') }}

现在有两个用户由于巧合，拥有了相同的模数 $N$，但是私钥不同。设两个用户的公钥分别为 $e_1$ 和 $e_2$，且两者互质。明文消息为 $m$，密文分别为：
$$
c_1=m^{e_1}\bmod N
$$

$$
c_2=m^{e_2}\bmod N
$$

现在，一个攻击者截获了 $c_1$，$c_2$，$e_1$，$e_2$，$N$，请恢复出明文$m$。

## {{ _('Input Format') }}

{{ self.input_file() }}

上面会根据具体的评测环境说明输入是文件还是标准输入等。

输入第一行包含一个正整数 $n$，保证 $n \le {{ tools.hn(prob.args['n']) }}$。←这是引用 `conf.json` 中的 `args` 的 `n` 项，然后用“好看”的格式输出。“好看”的格式如 `10^9`，`1,000,000,007`。

`prob.args['n']` 还可以写成 `prob['args']['n']`。引用 `args` 项、 `data` 项、`samples` 项和 `pre` 项现在可以简写成例如 `args['n']` 或 `args.n`。表格中也一样。

`tools` 可以简写成 `tl`，除 `hn` 外，还包括内建函数如 `tl.int`，`math` 中的对象或函数如 `tl.sin`，`datetime` 中的对象或函数如 `tl.time` 类，`num2chinese` 函数（可以把数字转化成中文）。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出一个字符串 `Yes`。注意不要写成 `“Yes”（不包含引号）`。

下面是自动读入样例 `1.in/ans`（存储在 `down` 文件夹内） 然后渲染到题面中；如果只有一组样例，则去掉前两行，样例仍然保存成 `1.in/ans`。其中 `1` 可以是字符串。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是第一组数据的样例说明。

下面是只提示存在第二组样例，但不渲染到题面中。

{% do vars.__setitem__('sample_id', 2) -%}
{{ self.sample_file() }}

## {{ _('Subtasks') }}

不要使用markdown原生的表格，使用下列方式渲染一个表格，其中表格存放在试题目录的 `tables` 子目录下。

{{ tbl('data') }}

{{ tbl('table', width = [1, 6]) }}

表格的例子见 `oi_tools/sample/tables`。原理上用一个二维的 json 表格存储，`null` 表示和上一行合并，不支持横向合并。建议用 python 的格式写，如例子中的 `data.pyinc`，这样可以根据数据生成；跟数据无关的表格则可以像 `table.json` 那样存储。

## {{ _('Scoring') }}

这是评分方法，如果有必要的话。

## {{ _('Hint') }}

这里是一个非常温馨的提示。