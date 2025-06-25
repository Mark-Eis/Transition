# Transition
### Characterise Transitions in Test Result Status in Longitudinal Studies

#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
Analyse data from longitudinal studies to characterise changes in values of semi-quantitative outcome
variables within individual subjects, using high performance C++ code to enable rapid processing of
large datasets. A choice of methods is available for codifying these state transitions.

## Installation

You can install the currently-released version from CRAN with this R
command:

``` r
install.packages("Transition")
```

Alternatively, you can install the latest development version of Transition
from [GitHub](https://github.com/) with:
      
``` r
# install.packages("devtools")
devtools::install_github("Mark-Eis/Transition")
```
---

**Authors:** Mark C. Eisler and Ana V. Rabaza

**eMail:** Mark.Eisler@bristol.ac.uk

**ORCID** = [0000-0001-6843-3345](https://orcid.org/0000-0001-6843-3345)
**ORCID** = [0000-0002-9713-0797](https://orcid.org/0000-0002-9713-0797)

### Transition Package Overview: –

* Create <code><a href="https://mark-eis.github.io/Waypoint/reference/coords.html">"coords"</a></code>
  objects in each format with `as_coords()`.

* Create <code><a href="https://mark-eis.github.io/Waypoint/reference/waypoints.html">"waypoints"</a></code>
 objects in each format with `as_waypoints()`.

* Convert `"coords"` and `"waypoints"` objects between decimal degrees, degrees
  and minutes, and degrees, minutes and seconds formats with `convert()`.

* Assign latitude and longitude attributes to individual coordinate values
  within `"coords"` objects with
  <code><a href="https://mark-eis.github.io/Waypoint/reference/coords.html">latlon&lt;-()</a></code>.

* Ensure values within `"coords"` and `"waypoints"` objects are valid
  geographic locations with `validate()` and identify individual invalid
  values with `review()`.

* Use `format()` and
  <code><a href="https://mark-eis.github.io/Waypoint/reference/format.html">print()</a></code>
  S3 methods for neat formatting and printing of objects of classes `"coords"` and `"waypoints"`.

* Use 
  <code><a href="https://mark-eis.github.io/Waypoint/reference/Extract.html">&#96;[&#96;(<i>&lt;coords&gt;</i>)</a></code> and 
  <code><a href="https://mark-eis.github.io/Waypoint/reference/Extract.html">&#96;[&lt;-&#96;(<i>&lt;coords&gt;</i>)</a></code>
  S3 methods to extract or replace subsets of `"coords"` objects.

#### Methodology  

*Transition* uses high performance C++ code seamlessly integrated into R using
[`Rcpp`](https://www.rcpp.org) to enable rapid processing of large longitudinal
study datasets.

#### Disclaimer

While every effort is made to ensure this package functions as expected, the
authors accept no responsibility for the consequences of errors.