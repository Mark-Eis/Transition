# Identify Temporal Transitions in Longitudinal Study Data

`get_transitions()` identifies temporal transitions in test results for
individual subjects in a longitudinal study.

`add_transitions()` interpolates these transitions into a data frame for
further analysis.

## Usage

``` r
add_transitions(
  object,
  subject = "subject",
  timepoint = "timepoint",
  result = "result",
  transition = "transition",
  cap = 0L,
  modulate = 0L
)

get_transitions(
  object,
  subject = "subject",
  timepoint = "timepoint",
  result = "result",
  cap = 0L,
  modulate = 0L
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

- transition:

  `character`, name to be used for a new column (of type
  [`integer`](https://rdrr.io/r/base/integer.html)) to record
  transitions; default `"transition"`.

- cap:

  [`integer`](https://rdrr.io/r/base/integer.html), required for
  calculating transitions; default `0L`.

- modulate:

  [`integer`](https://rdrr.io/r/base/integer.html), required for
  calculating transitions; default `0L`.

## Value

- `add_transitions()`:

  A [`data.frame`](https://rdrr.io/r/base/data.frame.html) based on
  `object`, with an added column of type
  [`integer`](https://rdrr.io/r/base/integer.html) containing the values
  of the test result transitions.

- `get_transitions()`:

  An [`integer vector`](https://rdrr.io/r/base/vector.html) of length
  [`nrow`](https://rdrr.io/r/base/nrow.html)`(object)`, containing the
  values of the test result transitions ordered in the exact sequence of
  the `subject` and `timepoint` in `object`.

## Details

The data can be presented in any order e.g., ordered by `subject`, by
`timepoint`, forwards or backwards in time, or entirely at random, and
may have unbalanced designs with different time points or numbers of
test results per subject. However, the *user* is responsible for
ensuring the data contain unique combinations of `subject`, `timepoint`
and `result`; if not, outputs will be undefined.

Time points should be formatted as
[`Dates`](https://rdrr.io/r/base/Dates.html) and included in data frame
`object` in the column named as specified by argument `timepoint` (see
*Note*).

Test results should either be semi-quantitiative, formatted as an
[`ordered factor`](https://rdrr.io/r/base/factor.html) (see *Note*), or
binary data formatted as an
[`integer`](https://rdrr.io/r/base/integer.html) (or
[`numeric`](https://rdrr.io/r/base/numeric.html)) vector with values of
either `1` or `0`, and included in `object` in the data frame column
specified by argument `result`.

Temporal transitions in the test `results` for each `subject` within the
`object` [`data.frame`](https://rdrr.io/r/base/data.frame.html) are
characterised using methods governed by options `cap` and `modulate`. If
these two parameters are both zero (their defaults), a simple arithmetic
difference between the levels of the present and previous result is
calculated. Otherwise, if the value of `modulate` is a positive,
non-zero integer, the arithmetic difference is subjected to integer
division by that value. Finally, if `cap` is a positive, non-zero
integer, the (possibly modulated) absolute arithmetic difference is
capped at that value.

## Note

Time points represented by
[`integer`](https://rdrr.io/r/base/integer.html) or
[`numeric`](https://rdrr.io/r/base/numeric.html) values can be converted
to R `Dates` conveniently using
[`as.Date()`](https://rdrr.io/r/base/as.Date.html). If only *year*
information is available, arbitrary values could be used consistently
for month and day e.g., 1st of January of each year; likewise, the first
day of each month could be used arbitrary, if only the *year* and
*month* were known.

Quantitive results available as
[`numeric`](https://rdrr.io/r/base/numeric.html) data can be converted
to a semi-quantitative
[`ordered factor`](https://rdrr.io/r/base/factor.html) conveniently
using [`cut()`](https://rdrr.io/r/base/cut.html) (see *examples*).

## See also

[`data.frame`](https://rdrr.io/r/base/data.frame.html),
[`Dates`](https://rdrr.io/r/base/Dates.html), and
[`ordered factor`](https://rdrr.io/r/base/factor.html).

Other transitions:
[`PreviousDate`](https://mark-eis.github.io/Transition/reference/PreviousDate.md),
[`PreviousResult`](https://mark-eis.github.io/Transition/reference/PreviousResult.md),
[`uniques()`](https://mark-eis.github.io/Transition/reference/uniques.md)

## Examples

``` r
  # Inspect Blackmore data frame using {base} str()
Blackmore |> str()
#> 'data.frame':    945 obs. of  4 variables:
#>  $ subject : Factor w/ 231 levels "100","101","102",..: 1 1 1 1 1 2 2 2 2 2 ...
#>  $ age     : num  8 10 12 14 15.9 ...
#>  $ exercise: num  2.71 1.94 2.36 1.54 8.63 0.14 0.14 0 0 5.08 ...
#>  $ group   : Factor w/ 2 levels "control","patient": 2 2 2 2 2 2 2 2 2 2 ...

  # {base} hist() gives insights into the "exercise" column,
  #   useful for choosing `breaks` and `labels` in cut() below
hist(Blackmore$exercise, include.lowest = TRUE, plot = FALSE)[1:2]
#> $breaks
#>  [1]  0  2  4  6  8 10 12 14 16 18 20 22 24 26 28 30
#> 
#> $counts
#>  [1] 594 166  75  43  20  19  11   5   3   5   1   1   1   0   1
#> 

  # Tweak Blackmore data frame by converting "age" to dates for the argument
  #   timepoint (using an arbitrary "origin" of 1-Jan-2000), and converting
  #   "exercise" to an ordered factor "result" with {base} cut()
Blackmore <- transform(Blackmore,
    timepoint = as.Date("2000-01-01") + round(age * 365.25),
    result = cut(
        exercise,
        breaks = seq(0, 30, 2),
        labels = paste0("<=", seq(0, 30, 2)[-1]),
        include.lowest = TRUE,
        ordered_result = TRUE
    )
)

  # subject, timepoint and result arguments now defaults and required types
Blackmore |> str()
#> 'data.frame':    945 obs. of  6 variables:
#>  $ subject  : Factor w/ 231 levels "100","101","102",..: 1 1 1 1 1 2 2 2 2 2 ...
#>  $ age      : num  8 10 12 14 15.9 ...
#>  $ exercise : num  2.71 1.94 2.36 1.54 8.63 0.14 0.14 0 0 5.08 ...
#>  $ group    : Factor w/ 2 levels "control","patient": 2 2 2 2 2 2 2 2 2 2 ...
#>  $ timepoint: Date, format: "2008-01-01" "2009-12-31" ...
#>  $ result   : Ord.factor w/ 15 levels "<=2"<"<=4"<"<=6"<..: 2 1 2 1 5 1 1 1 1 3 ...

  # Integer vector of test result transitions (defaults: cap = modulate = 0)
get_transitions(Blackmore)
#>   [1] NA -1  1 -1  4 NA  0  0  0  2 NA  0  2 10 NA  1  0  2 NA  2 -3  6 NA  0  0
#>  [26]  0  0 NA  0  0  0  2 NA  0  0  2 -2 NA  1  0  8 -7 NA -1  9 NA  0  0  6 -5
#>  [51] NA  0  2  5 NA  0  0  0  0 NA  0  1  8 NA  0  0  0 NA  0  1 -1 NA  0  0  1
#>  [76]  2 NA  0  0  1  4 NA  0  0  1 NA  0  0  0  4 NA  0  0  0  0 NA  0  5 -3 NA
#> [101]  0  0  3 -1 NA  0  0  0 NA  0  1  1 NA  1  2 -2 NA  0  0  1 NA  0  0  1  1
#> [126] NA  0  0 NA  0  0  5 NA  0  1  0  4 NA  0  2 NA  1  0 -1  6 NA  2  3  4 -1
#> [151] NA  0  0  0  0 NA  0  1  0  0 NA  0  0  0 NA  0  0  0 NA  0  4 -2  1 NA  1
#> [176]  0  0  0 NA  0  0  0  2 NA -3  0  5 NA  1  2 -3  2 NA  0  0  2 -2 NA  0  0
#> [201]  2 NA  0  0  2 NA  0  1 NA  0  0  0  4 NA  0  1 NA  1  0  2  3 NA  0  0  0
#> [226]  0 NA  2  0  0  1 NA  0  1 -1 NA  1  0  0 NA  0  1 NA  0  0  3 NA  0  0  9
#> [251] -6 NA  0  0 NA  0  0  0 NA  5  1  2 -1 NA  0  0  0  0 NA  0  0 NA -2  0 12
#> [276] NA  0  1 -1  2 NA  0  0  2 NA  1  0  2  2 NA  1  1  4 NA  0 NA  2  5 NA  0
#> [301]  0  0  1 NA  0  0  1 NA  0  2  1 NA  0  0  1 NA  0  1 NA  0  1 -1  0 NA  0
#> [326]  0  0  0 NA  0  0  1 NA  0  0  6 NA  0  0  0  0 NA  1  0  4 NA  0  0  0  2
#> [351] NA  0 -1  5 NA  0  0  0 NA  1  0 NA  0  0  0  1 NA  1  2  3 NA  1  0  2 NA
#> [376] -1  5  0 NA  0  1  0  0 NA  0  1  1 NA  0  0  2 NA  1  4 NA  0  0  0 NA  0
#> [401]  0  0 NA  1  0 NA  0  1  4 NA  0  1  3 NA  0  0  0  3 NA  0  0  0  0 NA  0
#> [426]  0  2  3 NA  2 -2  0  0 NA  1  2  2  2 NA  1 -2  0  4 NA  0  0  0  1 NA  0
#> [451]  0  1 NA  0  0  4 NA  0  0  2 NA  0  1 -1  1 NA  0  0  0  5 NA  0  0  0  1
#> [476] NA  0  0  1 NA  1  1  1 NA  1 -1 NA  0 -1 NA  0  0  0 NA  0  1  2  0 NA  0
#> [501]  0 -2 NA  0  0  1 -1 NA  1  4 NA  0  1 NA  0  0  0  0 NA  1  3 NA  0  0  0
#> [526] NA  0  0  1 NA  0  1 -1  1 NA  0  0  0  0 NA -1  1 NA  2 -1  3 NA  0  0  0
#> [551] NA  1  0  1 NA  1  0  7 NA  0  0  0  0 NA  0  2 -2 NA  0  0  0 NA -1  4 NA
#> [576]  0  0  0 NA  0  3  0  0 NA  0  0 NA  1 -2  3 -2 NA  0  0 NA  0  0 NA  0  0
#> [601]  0 NA  2  0  1 NA  0  0  0  0 NA  0  0 NA  0  0  0  1 NA  0  0  0 NA  0  0
#> [626] NA  0  0  0 NA  1  0 -1 NA  0  1 NA  1 -1  3  0 NA  0  0 -1 NA  0  0  1 NA
#> [651]  1  0  2 NA  1 -1 NA  0  0 NA  0  0  0  0 NA  0  0  0  0 NA  0  0  2 NA  2
#> [676]  1 NA  0 NA  2 -2 NA  1  0  0 NA  1 -1  1 NA  0  0 NA -2  0 NA  0  0  0  1
#> [701] NA  0  0  0 NA  0  0  0  1 NA  0  0 NA  0  1  0 NA  0  0  0  0 NA  1 -1  0
#> [726]  1 NA  0  0 NA -1  1 NA  0  0  1  2 NA  1  0 -1  1 NA  3  0  0 -2 NA  0  1
#> [751] NA  0  0 NA  0  4 NA  1  0 NA  2 -2  0 NA  0  0  0  0 NA  0  0  0  0 NA  0
#> [776]  0  0 NA  0  0  0 NA -2  0 NA  0  0  1  0 NA  1  0  1 NA  0  0  0 NA  0  1
#> [801] NA  0  0  1  0 NA  0  0 NA  0  0  0 NA -1  1 -1  1 NA  0  0  1 NA  0  1  0
#> [826] NA  0  0 NA  0  0  0 NA  0  0 NA  0  0 NA  0  0 NA  0  0 NA  0  0 NA  0 -1
#> [851] NA  0  0 NA  0  0  0 NA  0  0  0 NA  0  1 NA  1  0 -1 NA  0  0  0 NA  1  0
#> [876] NA  0  0  0 NA  0  0  0  0 NA  0  1 NA  0  0  0  0 NA  0  0  0 NA  0  0  0
#> [901] NA -2  0 NA  0  0 NA  0  0  0 NA  0  0  1 NA  0  0  1 -1 NA  0  1  0  0 NA
#> [926]  0  0  0  0 NA  0  1 NA  0  0  0  0 NA  0  0 NA  0  0  0  0

  # Tabulate values of transitions
get_transitions(Blackmore) |> table()
#> 
#>  -7  -6  -5  -3  -2  -1   0   1   2   3   4   5   6   7   8   9  10  12 
#>   1   1   1   4  17  34 444 116  46  14  16   9   4   1   2   2   1   1 

  # Effect of cap argument
get_transitions(Blackmore, cap = 6) |> table()
#> 
#>  -6  -5  -3  -2  -1   0   1   2   3   4   5   6 
#>   2   1   4  17  34 444 116  46  14  16   9  11 

  # Effect of modulate argument
get_transitions(Blackmore, modulate = 2) |> table()
#> 
#>  -4  -3  -2  -1   0   1   2   3   4   5   6 
#>   1   2   4  51 444 162  30  13   3   3   1 

  # Add column of test result transitions to data frame
add_transitions(Blackmore) |> head(22)
#>    subject   age exercise   group  timepoint result transition
#> 1      100  8.00     2.71 patient 2008-01-01    <=4         NA
#> 2      100 10.00     1.94 patient 2009-12-31    <=2         -1
#> 3      100 12.00     2.36 patient 2012-01-01    <=4          1
#> 4      100 14.00     1.54 patient 2014-01-01    <=2         -1
#> 5      100 15.92     8.63 patient 2015-12-03   <=10          4
#> 6      101  8.00     0.14 patient 2008-01-01    <=2         NA
#> 7      101 10.00     0.14 patient 2009-12-31    <=2          0
#> 8      101 12.00     0.00 patient 2012-01-01    <=2          0
#> 9      101 14.00     0.00 patient 2014-01-01    <=2          0
#> 10     101 16.67     5.08 patient 2016-09-02    <=6          2
#> 11     102  8.00     0.92 patient 2008-01-01    <=2         NA
#> 12     102 10.00     1.82 patient 2009-12-31    <=2          0
#> 13     102 12.00     4.75 patient 2012-01-01    <=6          2
#> 14     102 15.08    24.72 patient 2015-01-30   <=26         10
#> 15     103  8.00     1.04 patient 2008-01-01    <=2         NA
#> 16     103 10.00     2.90 patient 2009-12-31    <=4          1
#> 17     103 12.00     2.65 patient 2012-01-01    <=4          0
#> 18     103 14.08     6.86 patient 2014-01-30    <=8          2
#> 19     104  8.00     2.75 patient 2008-01-01    <=4         NA
#> 20     104 10.00     6.62 patient 2009-12-31    <=8          2
#> 21     104 12.00     0.29 patient 2012-01-01    <=2         -3
#> 22     104 15.42    12.37 patient 2015-06-03   <=14          6

  # Showing transitions as either positive (1) or negative (-1)
  #   (defaults to modulate = 0)
add_transitions(Blackmore, cap = 1) |> head(14)
#>    subject   age exercise   group  timepoint result transition
#> 1      100  8.00     2.71 patient 2008-01-01    <=4         NA
#> 2      100 10.00     1.94 patient 2009-12-31    <=2         -1
#> 3      100 12.00     2.36 patient 2012-01-01    <=4          1
#> 4      100 14.00     1.54 patient 2014-01-01    <=2         -1
#> 5      100 15.92     8.63 patient 2015-12-03   <=10          1
#> 6      101  8.00     0.14 patient 2008-01-01    <=2         NA
#> 7      101 10.00     0.14 patient 2009-12-31    <=2          0
#> 8      101 12.00     0.00 patient 2012-01-01    <=2          0
#> 9      101 14.00     0.00 patient 2014-01-01    <=2          0
#> 10     101 16.67     5.08 patient 2016-09-02    <=6          1
#> 11     102  8.00     0.92 patient 2008-01-01    <=2         NA
#> 12     102 10.00     1.82 patient 2009-12-31    <=2          0
#> 13     102 12.00     4.75 patient 2012-01-01    <=6          1
#> 14     102 15.08    24.72 patient 2015-01-30   <=26          1

rm(Blackmore)
```
