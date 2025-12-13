# Exercise Histories of Eating-Disordered and Control Subjects

The `Blackmore` data frame has 945 rows and 4 columns. Blackmore and
Davis's data on exercise histories of 138 teenaged girls hospitalized
for eating disorders and 98 control subjects.

## Usage

``` r
Blackmore
```

## Format

This data frame contains the following columns:

- subject:

  a factor with subject id codes. There are several observations for
  each subject, but because the girls were hospitalized at different
  ages, the number of cases and the age at the last case vary.

- age:

  subject's age in years at the time of observation; all but the last
  observation for each subject were collected retrospectively at
  intervals of two years, starting at age 8.

- exercise:

  the amount of exercise in which the subject engaged, expressed as
  estimated hours per week.

- group:

  a factor with levels: `control`, Control subjects; `patient`,
  Eating-disordered patients.

## Source

Personal communication from Elizabeth Blackmore and Caroline Davis, York
University.

## Note

The original version in package carData states there are 98 `control`
subjects, but the actual data only have 93 unique values, and that
assuming `subject` id codes with suffixes `a` and `b` represent
different individuals; otherwise, there are just 87.

## References

Davis C, Blackmore E, Katzman DK, Fox J. (2005). Female adolescents with
anorexia nervosa and their parents: a case-control study of exercise
attitudes and behaviours. *Psychological Medicine* **35**(3):377-386.
[doi:10.1017/S0033291704003447](https://doi.org/10.1017/S0033291704003447)
