# Find Previous Test Result for Subject

`get_prev_results()` identifies the previous test result for individual
subjects and timepoints in a longitudinal study.

`add_prev_result()` interpolates these previous test results into a data
frame for further analysis.

## Usage

``` r
add_prev_result(
  object,
  subject = "subject",
  timepoint = "timepoint",
  result = "result",
  prev_result = "prev_result"
)

get_prev_result(
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

- prev_result:

  `character`, name to be used for a new column to record previous
  result; default `"prev_result"`.

## Value

- `add_prev_result()`:

  A [`data.frame`](https://rdrr.io/r/base/data.frame.html) based on
  `object`, with an added column named as specified by argument
  `prev_result` and of type
  [`ordered factor`](https://rdrr.io/r/base/factor.html) or
  [`integer`](https://rdrr.io/r/base/integer.html) depending on whether
  the results are semi-quantitiative or binary.

- `get_prev_result()`:

  An [`ordered factor`](https://rdrr.io/r/base/factor.html) of length
  [`nrow`](https://rdrr.io/r/base/nrow.html)`(object)`, containing the
  values of the previous test results ordered in the exact sequence of
  the `subject` and `timepoint` in `object`.

## Details

See
[`Transitions`](https://mark-eis.github.io/Transition/reference/Transitions.md)
*details*.

## See also

[`data.frame`](https://rdrr.io/r/base/data.frame.html),
[`Dates`](https://rdrr.io/r/base/Dates.html),
[`ordered factor`](https://rdrr.io/r/base/factor.html).

Other transitions:
[`PreviousDate`](https://mark-eis.github.io/Transition/reference/PreviousDate.md),
[`Transitions`](https://mark-eis.github.io/Transition/reference/Transitions.md),
[`uniques()`](https://mark-eis.github.io/Transition/reference/uniques.md)

## Examples

``` r

 ## Continuing example from `add_transitions()`
  # subject, timepoint and result arguments all defaults and required types
Blackmore |> str()
#> 'data.frame':    945 obs. of  6 variables:
#>  $ subject  : Factor w/ 231 levels "100","101","102",..: 1 1 1 1 1 2 2 2 2 2 ...
#>  $ age      : num  8 10 12 14 15.9 ...
#>  $ exercise : num  2.71 1.94 2.36 1.54 8.63 0.14 0.14 0 0 5.08 ...
#>  $ group    : Factor w/ 2 levels "control","patient": 2 2 2 2 2 2 2 2 2 2 ...
#>  $ timepoint: Date, format: "2008-01-01" "2009-12-31" ...
#>  $ result   : Ord.factor w/ 15 levels "<=2"<"<=4"<"<=6"<..: 2 1 2 1 5 1 1 1 1 3 ...

  # Previous test results as ordered factor
get_prev_result(Blackmore)
#>   [1] <NA> <=4  <=2  <=4  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=6  <NA>
#>  [16] <=2  <=4  <=4  <NA> <=4  <=8  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2 
#>  [31] <=2  <=2  <NA> <=2  <=2  <=2  <=6  <NA> <=2  <=4  <=4  <=20 <NA> <=4  <=2 
#>  [46] <NA> <=2  <=2  <=2  <=14 <NA> <=2  <=2  <=6  <NA> <=2  <=2  <=2  <=2  <NA>
#>  [61] <=2  <=2  <=4  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=4  <NA> <=6  <=6  <=6 
#>  [76] <=8  <NA> <=2  <=2  <=2  <=4  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2 
#>  [91] <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=12 <NA> <=2  <=2  <=2  <=8  <NA>
#> [106] <=2  <=2  <=2  <NA> <=2  <=2  <=4  <NA> <=2  <=4  <=8  <NA> <=2  <=2  <=2 
#> [121] <NA> <=2  <=2  <=2  <=4  <NA> <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2 
#> [136] <=4  <=4  <NA> <=2  <=2  <NA> <=2  <=4  <=4  <=2  <NA> <=6  <=10 <=16 <=24
#> [151] <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=4  <=4  <NA> <=2  <=2  <=2  <NA>
#> [166] <=2  <=2  <=2  <NA> <=8  <=8  <=16 <=12 <NA> <=6  <=8  <=8  <=8  <NA> <=2 
#> [181] <=2  <=2  <=2  <NA> <=8  <=2  <=2  <NA> <=4  <=6  <=10 <=4  <NA> <=2  <=2 
#> [196] <=2  <=6  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2 
#> [211] <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=4  <=4  <=8  <NA> <=2  <=2  <=2 
#> [226] <=2  <NA> <=2  <=6  <=6  <=6  <NA> <=2  <=2  <=4  <NA> <=2  <=4  <=4  <NA>
#> [241] <=4  <=4  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=20 <NA> <=2  <=2  <NA>
#> [256] <=2  <=2  <=2  <NA> <=2  <=12 <=14 <=18 <NA> <=2  <=2  <=2  <=2  <NA> <=2 
#> [271] <=2  <NA> <=10 <=6  <=6  <NA> <=2  <=2  <=4  <=2  <NA> <=2  <=2  <=2  <NA>
#> [286] <=2  <=4  <=4  <=8  <NA> <=6  <=8  <=10 <NA> <=2  <NA> <=2  <=6  <NA> <=2 
#> [301] <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=6  <NA> <=2  <=2  <=2 
#> [316] <NA> <=2  <=2  <NA> <=2  <=2  <=4  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2 
#> [331] <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=4  <=6  <=6 
#> [346] <NA> <=2  <=2  <=2  <=2  <NA> <=4  <=4  <=2  <NA> <=2  <=2  <=2  <NA> <=2 
#> [361] <=4  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=4  <=8  <NA> <=2  <=4  <=4  <NA>
#> [376] <=4  <=2  <=12 <NA> <=2  <=2  <=4  <=4  <NA> <=2  <=2  <=4  <NA> <=2  <=2 
#> [391] <=2  <NA> <=4  <=6  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=4  <=6 
#> [406] <NA> <=2  <=2  <=4  <NA> <=4  <=4  <=6  <NA> <=2  <=2  <=2  <=2  <NA> <=2 
#> [421] <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=6  <NA> <=2  <=6  <=2  <=2  <NA> <=4 
#> [436] <=6  <=10 <=14 <NA> <=4  <=6  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2 
#> [451] <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=4  <=2 
#> [466] <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA>
#> [481] <=4  <=6  <=8  <NA> <=2  <=4  <NA> <=4  <=4  <NA> <=2  <=2  <=2  <NA> <=4 
#> [496] <=4  <=6  <=10 <NA> <=6  <=6  <=6  <NA> <=2  <=2  <=2  <=4  <NA> <=2  <=4 
#> [511] <NA> <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=4  <=6  <NA> <=2  <=2  <=2 
#> [526] <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=4  <=2  <NA> <=8  <=8  <=8  <=8  <NA>
#> [541] <=4  <=2  <NA> <=2  <=6  <=4  <NA> <=2  <=2  <=2  <NA> <=4  <=6  <=6  <NA>
#> [556] <=4  <=6  <=6  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=6  <NA> <=2  <=2 
#> [571] <=2  <NA> <=4  <=2  <NA> <=2  <=2  <=2  <NA> <=4  <=4  <=10 <=10 <NA> <=4 
#> [586] <=4  <NA> <=4  <=6  <=2  <=8  <NA> <=2  <=2  <NA> <=2  <=2  <NA> <=4  <=4 
#> [601] <=4  <NA> <=2  <=6  <=6  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2 
#> [616] <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <=2  <NA>
#> [631] <=2  <=4  <=4  <NA> <=2  <=2  <NA> <=2  <=4  <=2  <=8  <NA> <=4  <=4  <=4 
#> [646] <NA> <=4  <=4  <=4  <NA> <=4  <=6  <=6  <NA> <=2  <=4  <NA> <=2  <=2  <NA>
#> [661] <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2 
#> [676] <=6  <NA> <=2  <NA> <=2  <=6  <NA> <=2  <=4  <=4  <NA> <=2  <=4  <=2  <NA>
#> [691] <=2  <=2  <NA> <=6  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA>
#> [706] <=2  <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <=4  <NA> <=2  <=2  <=2 
#> [721] <=2  <NA> <=2  <=4  <=2  <=2  <NA> <=2  <=2  <NA> <=4  <=2  <NA> <=2  <=2 
#> [736] <=2  <=4  <NA> <=2  <=4  <=4  <=2  <NA> <=2  <=8  <=8  <=8  <NA> <=2  <=2 
#> [751] <NA> <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=4  <NA> <=8  <=12 <=8  <NA> <=2 
#> [766] <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2 
#> [781] <=2  <NA> <=8  <=4  <NA> <=4  <=4  <=4  <=6  <NA> <=2  <=4  <=4  <NA> <=2 
#> [796] <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <=2  <=4  <NA> <=2  <=2  <NA> <=2 
#> [811] <=2  <=2  <NA> <=4  <=2  <=4  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=4 
#> [826] <NA> <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <NA> <=2 
#> [841] <=2  <NA> <=2  <=2  <NA> <=2  <=2  <NA> <=4  <=4  <NA> <=2  <=2  <NA> <=2 
#> [856] <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=4  <=4  <NA> <=2 
#> [871] <=2  <=2  <NA> <=2  <=4  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA>
#> [886] <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2 
#> [901] <NA> <=6  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <=2  <NA> <=2  <=2  <=2  <NA>
#> [916] <=2  <=2  <=2  <=4  <NA> <=4  <=4  <=6  <=6  <NA> <=2  <=2  <=2  <=2  <NA>
#> [931] <=2  <=2  <NA> <=2  <=2  <=2  <=2  <NA> <=2  <=2  <NA> <=2  <=2  <=2  <=2 
#> 15 Levels: <=2 < <=4 < <=6 < <=8 < <=10 < <=12 < <=14 < <=16 < ... < <=30

  # Previous test result as column of data frame
(Blackmore <- add_prev_result(Blackmore)) |> head(32)
#>    subject   age exercise   group  timepoint result prev_result
#> 1      100  8.00     2.71 patient 2008-01-01    <=4        <NA>
#> 2      100 10.00     1.94 patient 2009-12-31    <=2         <=4
#> 3      100 12.00     2.36 patient 2012-01-01    <=4         <=2
#> 4      100 14.00     1.54 patient 2014-01-01    <=2         <=4
#> 5      100 15.92     8.63 patient 2015-12-03   <=10         <=2
#> 6      101  8.00     0.14 patient 2008-01-01    <=2        <NA>
#> 7      101 10.00     0.14 patient 2009-12-31    <=2         <=2
#> 8      101 12.00     0.00 patient 2012-01-01    <=2         <=2
#> 9      101 14.00     0.00 patient 2014-01-01    <=2         <=2
#> 10     101 16.67     5.08 patient 2016-09-02    <=6         <=2
#> 11     102  8.00     0.92 patient 2008-01-01    <=2        <NA>
#> 12     102 10.00     1.82 patient 2009-12-31    <=2         <=2
#> 13     102 12.00     4.75 patient 2012-01-01    <=6         <=2
#> 14     102 15.08    24.72 patient 2015-01-30   <=26         <=6
#> 15     103  8.00     1.04 patient 2008-01-01    <=2        <NA>
#> 16     103 10.00     2.90 patient 2009-12-31    <=4         <=2
#> 17     103 12.00     2.65 patient 2012-01-01    <=4         <=4
#> 18     103 14.08     6.86 patient 2014-01-30    <=8         <=4
#> 19     104  8.00     2.75 patient 2008-01-01    <=4        <NA>
#> 20     104 10.00     6.62 patient 2009-12-31    <=8         <=4
#> 21     104 12.00     0.29 patient 2012-01-01    <=2         <=8
#> 22     104 15.42    12.37 patient 2015-06-03   <=14         <=2
#> 23     105  8.00     0.05 patient 2008-01-01    <=2        <NA>
#> 24     105 10.00     0.00 patient 2009-12-31    <=2         <=2
#> 25     105 12.00     0.00 patient 2012-01-01    <=2         <=2
#> 26     105 14.00     0.25 patient 2014-01-01    <=2         <=2
#> 27     105 16.17     1.44 patient 2016-03-03    <=2         <=2
#> 28     106  8.00     0.00 patient 2008-01-01    <=2        <NA>
#> 29     106 10.00     0.46 patient 2009-12-31    <=2         <=2
#> 30     106 12.00     0.12 patient 2012-01-01    <=2         <=2
#> 31     106 14.00     1.34 patient 2014-01-01    <=2         <=2
#> 32     106 16.33     4.83 patient 2016-05-01    <=6         <=2

rm(Blackmore)
```
