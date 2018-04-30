{{ self.title() }}

## {{ _('Description') }}

咕咕咕

## {{ _('Input Format') }}

{{ self.input_file() }}

咕咕咕

## {{ _('Output Format') }}

{{ self.output_file() }}

咕咕咕

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{{ self.title_sample_description() }}

咕咕咕


## 数据规模

咕咕咕

## {{ _('Hint') }}

这里是一个非常温馨的提示。