# Unique Values for Subject, Timepoint and Result

`uniques()` identifies unique values for subjects, timepoints and test
results in longitudinal study data.

## Usage

``` r
uniques(
  object,
  subject = "subject",
  timepoint = "timepoint",
  result = "result"
)
```

## Arguments

- object:

  a [`data.frame`](https://rdrr.io/r/base/data.frame.html) (or object
  coercible by
  [`as.data.frame()`](https://rdrr.io/r/base/as.data.frame.html) to a
  data frame) containing the data to be analysed.

- subject:

  [`character`](https://rdrr.io/r/base/character.html), name of the
  column (of type [`integer`](https://rdrr.io/r/base/integer.html) or
  [`factor`](https://rdrr.io/r/base/factor.html)) identifying individual
  study subjects; default `"subject"`.

- timepoint:

  `character`, name of the column recording time points (as
  [`Dates`](https://rdrr.io/r/base/Dates.html)) of testing of subjects;
  default `"timepoint"`.

- result:

  `character`, name of the column (of type
  [`ordered factor`](https://rdrr.io/r/base/factor.html), or binary, see
  *Details*) recording test results; default `"result"`.

## Value

A [`list`](https://rdrr.io/r/base/list.html) of three elements

- 1.:

  An [`integer vector`](https://rdrr.io/r/base/vector.html) or
  [`factor`](https://rdrr.io/r/base/factor.html) of unique subject
  identifications.

- 2.:

  A [`vector`](https://rdrr.io/r/base/vector.html) of class
  [`Date`](https://rdrr.io/r/base/Dates.html) of unique timepoints in
  the study.

- 3.:

  An [`ordered factor`](https://rdrr.io/r/base/factor.html) of unique
  values for results of the study.

## Details

See
[`Transitions`](https://mark-eis.github.io/Transition/reference/Transitions.md)
*details*.

Works for `subject` as either an
[`integer vector`](https://rdrr.io/r/base/vector.html) or a
[`factor`](https://rdrr.io/r/base/factor.html).

## See also

[`data.frame`](https://rdrr.io/r/base/data.frame.html),
[`Dates`](https://rdrr.io/r/base/Dates.html),
[`ordered factor`](https://rdrr.io/r/base/factor.html).

Other transitions:
[`PreviousDate`](https://mark-eis.github.io/Transition/reference/PreviousDate.md),
[`PreviousResult`](https://mark-eis.github.io/Transition/reference/PreviousResult.md),
[`Transitions`](https://mark-eis.github.io/Transition/reference/Transitions.md)

## Examples

``` r

 ## Continuing example from `add_transitions()`
  # subject, timepoint and result arguments all defaults and required types
  # (native subject is factor)
uniques(Blackmore)
#> $subject
#>   [1] 100  101  102  103  104  105  106  107  108  109  110  111  112  113  114 
#>  [16] 115  116  117  118  119  120  121  122  123  124  125  126  127  128  129 
#>  [31] 130  132  133  134  135  136  137  138  139  140  141  142  143  144  145 
#>  [46] 146  147  148  149  150  151  152  153  154  155  156  157  158  159  160 
#>  [61] 161  162  163  164  165  166  167  168  169  170  171  172  173  174  175 
#>  [76] 176  177  178  179  180  181  182  183  184  185  186  187  188  189  190 
#>  [91] 192  193  194  195  196  198  199  200  201  202  203  204  205  206  207a
#> [106] 207b 208  209  210  211  212  213  214  215  216  217  218  219  220  221 
#> [121] 222  223  224  225  226  227  228  229a 229b 230  231  232  233  234  235 
#> [136] 236  237  238  239  240  241  242  243  244  245  246  247  248  249  250 
#> [151] 251  252  253  254  255  255b 256  257  258  259  260  261  262  263  264 
#> [166] 265  266  267  268  269  270  271  272  273a 273b 274  275  276  277  278 
#> [181] 279a 279b 280a 280b 281  282  283  284  285  286  300  301  302  303  304 
#> [196] 305  306  307  308  309  310  311  312  313  314  315  316  317  318  319 
#> [211] 320  321  322  323  324  325  326  327  328  329  330  331  332  333  334 
#> [226] 335  336  337  338  340  341 
#> 231 Levels: 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 ... 341
#> 
#> $timepoint
#>  [1] "2008-01-01" "2009-12-31" "2011-08-01" "2011-10-31" "2012-01-01"
#>  [6] "2012-01-30" "2012-03-03" "2012-04-01" "2012-05-01" "2012-06-02"
#> [11] "2012-06-17" "2012-07-31" "2012-10-01" "2012-10-30" "2012-12-31"
#> [16] "2013-01-29" "2013-03-03" "2013-03-18" "2013-04-02" "2013-05-01"
#> [21] "2013-06-03" "2013-07-02" "2013-07-31" "2013-09-17" "2013-10-01"
#> [26] "2013-10-30" "2013-12-02" "2013-12-17" "2014-01-01" "2014-01-30"
#> [31] "2014-03-04" "2014-04-02" "2014-04-16" "2014-05-19" "2014-06-03"
#> [36] "2014-07-02" "2014-07-17" "2014-07-31" "2014-09-02" "2014-10-01"
#> [41] "2014-10-31" "2014-12-03" "2014-12-17" "2015-01-01" "2015-01-30"
#> [46] "2015-03-04" "2015-04-02" "2015-05-01" "2015-06-03" "2015-07-02"
#> [51] "2015-09-02" "2015-10-02" "2015-10-16" "2015-10-31" "2015-11-18"
#> [56] "2015-12-03" "2015-12-17" "2016-01-01" "2016-01-30" "2016-02-17"
#> [61] "2016-03-03" "2016-03-18" "2016-04-01" "2016-05-01" "2016-05-19"
#> [66] "2016-06-02" "2016-07-02" "2016-07-31" "2016-09-02" "2016-10-01"
#> [71] "2016-10-16" "2016-10-30" "2016-12-17" "2016-12-31" "2017-02-17"
#> [76] "2017-03-03" "2017-04-02" "2017-06-03" "2017-06-17" "2017-07-02"
#> [81] "2017-09-02" "2017-12-02"
#> 
#> $result
#>  [1] <=2  <=4  <=6  <=8  <=10 <=12 <=14 <=16 <=18 <=20 <=22 <=24 <=26 <=30
#> 15 Levels: <=2 < <=4 < <=6 < <=8 < <=10 < <=12 < <=14 < <=16 < ... < <=30
#> 
  #
Blackmore <- transform(Blackmore, subject = as.integer(subject))
  # subject now as integer
Blackmore |> str()
#> 'data.frame':    945 obs. of  6 variables:
#>  $ subject  : int  1 1 1 1 1 2 2 2 2 2 ...
#>  $ age      : num  8 10 12 14 15.9 ...
#>  $ exercise : num  2.71 1.94 2.36 1.54 8.63 0.14 0.14 0 0 5.08 ...
#>  $ group    : Factor w/ 2 levels "control","patient": 2 2 2 2 2 2 2 2 2 2 ...
#>  $ timepoint: Date, format: "2008-01-01" "2009-12-31" ...
#>  $ result   : Ord.factor w/ 15 levels "<=2"<"<=4"<"<=6"<..: 2 1 2 1 5 1 1 1 1 3 ...
uniques(Blackmore)
#> $subject
#>   [1]   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18
#>  [19]  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36
#>  [37]  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54
#>  [55]  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72
#>  [73]  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90
#>  [91]  91  92  93  94  95  96  97  98  99 100 101 102 103 104 105 106 107 108
#> [109] 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126
#> [127] 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144
#> [145] 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162
#> [163] 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180
#> [181] 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198
#> [199] 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216
#> [217] 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231
#> 
#> $timepoint
#>  [1] "2008-01-01" "2009-12-31" "2011-08-01" "2011-10-31" "2012-01-01"
#>  [6] "2012-01-30" "2012-03-03" "2012-04-01" "2012-05-01" "2012-06-02"
#> [11] "2012-06-17" "2012-07-31" "2012-10-01" "2012-10-30" "2012-12-31"
#> [16] "2013-01-29" "2013-03-03" "2013-03-18" "2013-04-02" "2013-05-01"
#> [21] "2013-06-03" "2013-07-02" "2013-07-31" "2013-09-17" "2013-10-01"
#> [26] "2013-10-30" "2013-12-02" "2013-12-17" "2014-01-01" "2014-01-30"
#> [31] "2014-03-04" "2014-04-02" "2014-04-16" "2014-05-19" "2014-06-03"
#> [36] "2014-07-02" "2014-07-17" "2014-07-31" "2014-09-02" "2014-10-01"
#> [41] "2014-10-31" "2014-12-03" "2014-12-17" "2015-01-01" "2015-01-30"
#> [46] "2015-03-04" "2015-04-02" "2015-05-01" "2015-06-03" "2015-07-02"
#> [51] "2015-09-02" "2015-10-02" "2015-10-16" "2015-10-31" "2015-11-18"
#> [56] "2015-12-03" "2015-12-17" "2016-01-01" "2016-01-30" "2016-02-17"
#> [61] "2016-03-03" "2016-03-18" "2016-04-01" "2016-05-01" "2016-05-19"
#> [66] "2016-06-02" "2016-07-02" "2016-07-31" "2016-09-02" "2016-10-01"
#> [71] "2016-10-16" "2016-10-30" "2016-12-17" "2016-12-31" "2017-02-17"
#> [76] "2017-03-03" "2017-04-02" "2017-06-03" "2017-06-17" "2017-07-02"
#> [81] "2017-09-02" "2017-12-02"
#> 
#> $result
#>  [1] <=2  <=4  <=6  <=8  <=10 <=12 <=14 <=16 <=18 <=20 <=22 <=24 <=26 <=30
#> 15 Levels: <=2 < <=4 < <=6 < <=8 < <=10 < <=12 < <=14 < <=16 < ... < <=30
#> 

rm(Blackmore)
```
