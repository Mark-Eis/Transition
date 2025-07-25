# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' @title
#' Identify Temporal Transitions in Longitudinal Study Data
#'
#' @name
#' Transitions
#'
#' @description
#' \code{get_transitions()} identifies temporal transitions in test results for individual
#' subjects in a longitudinal study.
#'
#' \code{add_transitions()} interpolates these transitions into a data frame for further analysis.
#'
#' @details
#' The data can be presented in any order e.g., ordered by \code{subject}, by \code{timepoint},
#' forwards or backwards in time, or entirely at random, and may have unbalanced designs with different
#' time points or numbers of test results per subject. However, the \emph{user} is responsible for
#' ensuring the data contain unique combinations of \code{subject}, \code{timepoint} and \code{result};
#' if not, outputs will be undefined.
#'
#' Time points should be formatted as \code{\link{Dates}} and included in data frame \code{object} in
#' the column named as specified by argument \code{timepoint} (see \emph{Note}).
#'
#' Test results should be semi-quantitiative, formatted as \code{\link[base:ordered]{ordered factor}}
#' and included in data frame \code{object} in the column named as specified by argument \code{result}
#' (see \emph{Note}).
#'
#' Temporal transitions in the test \code{results} for each \code{subject} within the \code{object}
#' \code{\link{data.frame}} are characterised using methods governed by options \code{cap} and
#' \code{modulate}. If these two parameters are both zero (their defaults), a simple arithmetic
#' difference between the levels of the present and previous result is calculated. Otherwise, if
#' the value of \code{modulate} is a positive, non-zero integer, the arithmetic difference is
#' subjected to integer division by that value. Finally, if \code{cap} is a positive, non-zero
#' integer, the (possibly modulated) absolute arithmetic difference is capped at that value.
#'
#' @family transitions
#' @seealso
#' \code{\link{data.frame}}, \code{\link{Dates}}, and \code{\link[base:factor]{ordered factor}}.
#'
#' @param object a \code{\link{data.frame}} (or object coercible by \code{\link{as.data.frame}()} to
#'   a data frame) containing the data to be analysed.
#'
#' @param subject \code{\link{character}}, name of the column (of type \code{\link{integer}} or
#'   \code{\link{factor}}) identifying individual study subjects; default \code{"subject"}.
#'
#' @param timepoint \code{character}, name of the column recording time points (as \code{\link{Dates}})
#'   of testing of subjects; default \code{"timepoint"}.
#'
#' @param result \code{character}, name of the column (of type \code{\link[base:factor]{ordered factor}})
#'   recording test results; default \code{"result"}.
#'
#' @param transition \code{character}, name to be used for a new column (of type
#'   \code{\link{integer}}) to record transitions; default \code{"transition"}.
#'
#' @param cap \code{\link{integer}}, required for calculating transitions; default \code{0L}.
#'
#' @param modulate \code{\link{integer}}, required for calculating transitions; default \code{0L}.
#'
#' @return
#'
#' \item{\code{add_transitions()}}{A \code{\link{data.frame}} based on \code{object}, with an added
#'    column of type \code{\link{integer}} containing the values of the test result transitions.}
#'
#' \item{\code{get_transitions()}}{An \code{\link[base:vector]{integer vector}} of length
#'    \code{\link{nrow}(object)}, containing the values of the test result transitions ordered in the exact
#'    sequence of the \code{subject} and \code{timepoint} in \code{object}.}
#'
#' @note
#' Time points represented by \code{\link{integer}} or \code{\link{numeric}} values can be converted
#'   to R \code{Dates} conveniently using \code{\link{as.Date}()}. If only \emph{year} information is
#'   available, arbitrary values could be used consistently for month and day e.g., 1st of January of
#'   each year; likewise, the first day of each month could be used arbitrary, if only the
#'   \emph{year} and \emph{month} were known.
#'
#' Quantitive results available as \code{\link{numeric}} data can be converted to a semi-quantitative
#'   \code{\link[base:factor]{ordered factor}} conveniently using \code{\link{cut}()} (see \emph{examples}).
#'
#' @examples
#'
#'   # Inspect Blackmore data frame using {base} str()
#' Blackmore |> str()
#'
#'   # {base} hist() gives insights into the "exercise" column,
#'   #   useful for choosing `breaks` and `labels` in cut() below
#' hist(Blackmore$exercise, include.lowest = TRUE, plot = FALSE)[1:2]
#'
#'   # Tweak Blackmore data frame by converting "age" to dates for the argument
#'   #   timepoint (using an arbitrary "origin" of 1-Jan-2000), and converting
#'   #   "exercise" to an ordered factor "result" with {base} cut()
#' Blackmore <- transform(Blackmore,
#'     timepoint = as.Date("2000-01-01") + round(age * 365.25),
#'     result = cut(
#'         exercise,
#'         breaks = seq(0, 30, 2),
#'         labels = paste0("<=", seq(0, 30, 2)[-1]),
#'         include.lowest = TRUE,
#'         ordered_result = TRUE
#'     )
#' )
#'
#'   # subject, timepoint and result arguments now defaults and required types
#' Blackmore |> str()
#'
#'   # Integer vector of test result transitions (defaults: cap = modulate = 0)
#' get_transitions(Blackmore)
#'
#'   # Tabulate values of transitions
#' get_transitions(Blackmore) |> table()
#'
#'   # Effect of cap argument
#' get_transitions(Blackmore, cap = 6) |> table()
#'
#'   # Effect of modulate argument
#' get_transitions(Blackmore, modulate = 2) |> table()
#'
#'   # Add column of test result transitions to data frame
#' add_transitions(Blackmore) |> head(22)
#'
#'   # Showing transitions as either positive (1) or negative (-1)
#'   #   (defaults to modulate = 0)
#' add_transitions(Blackmore, cap = 1) |> head(14)
#'
#' rm(Blackmore)
#'
add_transitions <- function(object, subject = "subject", timepoint = "timepoint", result = "result", transition = "transition", cap = 0L, modulate = 0L) {
    .Call(`_Transition_add_transitions`, object, subject, timepoint, result, transition, cap, modulate)
}

#' @rdname Transitions
get_transitions <- function(object, subject = "subject", timepoint = "timepoint", result = "result", cap = 0L, modulate = 0L) {
    .Call(`_Transition_get_transitions`, object, subject, timepoint, result, cap, modulate)
}

#' @title
#' Find Previous Test Date for Subject
#'
#' @name
#' PreviousDate
#'
#' @description
#' \code{get_prev_dates()} identifies the previous test date for individual subjects and timepoints
#' in a longitudinal study.
#'
#' \code{add_prev_date()} interpolates these previous test dates into a data frame for further analysis.
#'
#' @details
#' See \code{\link{Transitions}} \emph{details}.
#'
#' @family transitions
#' @seealso
#' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
#'
#' @inheritParams Transitions
#'
#' @return
#'
#' \item{\code{add_prev_date()}}{A \code{\link{data.frame}} based on \code{object}, with an added
#'    column of class \code{\link{Date}} containing the values of the previous test dates.}
#'
#' \item{\code{get_prev_date()}}{An \code{vector} of length \code{\link{nrow}(object)},
#'    class \code{\link{Date}}, containing the values of the previous test dates ordered in the exact
#'    sequence of the \code{subject} and \code{timepoint} in \code{object}.}
#'
#'
#' @examples
#'
#' \dontshow{
#' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
#'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
#'         include.lowest = TRUE, ordered_result = TRUE))
#' }
#'
#'  ## Continuing example from `add_transitions()`
#'   # subject, timepoint and result arguments all defaults and required types
#' Blackmore |> str()
#'
#'   # Integer vector of the previous test dates
#' get_prev_date(Blackmore)
#'
#'   # Add column of  previous test dates to data frame
#' add_prev_date(Blackmore) |> head(32)
#'
#' rm(Blackmore)
#'
#' ###
#' ## Example on formatting numeric values as R dates
#'
#' #  Data frame containing year as numeric: 2018 to 2025
#' (df <- data.frame(
#'     subject = rep(1001:1003),
#'     timepoint = rep(2018:2025, each = 3),
#'     result = gl(3, 4, lab = c("jolly", "good", "show"), ordered = TRUE)
#'     ))
#'
#' #  Convert to R dates
#' df <- transform(df,
#'            timepoint = as.Date(paste(timepoint, "01", "01", sep = "-"))
#'       )
#'
#'   # Add column of test result transitions (defaults: cap = 0, modulate = 0)
#' (df <- add_transitions(df))
#'
#' # Format R dates just to show the year
#' transform(df, timepoint = format(timepoint, "%Y"))
#'
#' #  Data frame containing year and month as numeric: July 2024 to June 2025
#' (df <- data.frame(
#'            subject = 1001:1002,
#'            year = rep(2024:2025, each = 12),
#'            month = rep(c(7:12, 1:6), each = 2),
#'            result = gl(2, 3, lab = c("low", "high"), ordered = TRUE)
#'        ))
#'
#' #  Convert to R dates
#' df <- transform(df, timepoint = as.Date(paste(year, month, "01", sep = "-")))
#' \dontshow{
#'     df$year <- NULL
#'     df$month <- NULL
#' }
#'
#'   # Add column of test result transitions (defaults: cap = 0, modulate = 0)
#' (df <- add_transitions(df))
#'
#' # Format R dates just to show the month and year
#' transform(df, timepoint = format(timepoint, "%b-%Y"))
#'
#' rm(df)
#'
add_prev_date <- function(object, subject = "subject", timepoint = "timepoint", result = "result") {
    .Call(`_Transition_add_prev_date`, object, subject, timepoint, result)
}

#' @rdname PreviousDate
get_prev_date <- function(object, subject = "subject", timepoint = "timepoint", result = "result") {
    .Call(`_Transition_get_prev_date`, object, subject, timepoint, result)
}

#' @title
#' Find Previous Test Result for Subject
#'
#' @name
#' PreviousResult
#'
#' @description
#' \code{get_prev_results()} identifies the previous test result for individual subjects and timepoints
#' in a longitudinal study.
#'
#' \code{add_prev_result()} interpolates these previous test results into a data frame for further analysis.
#'
#' @details
#' See \code{\link{Transitions}} \emph{details}.
#'
#' @family transitions
#' @seealso
#' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
#'
#' @inheritParams Transitions
#'
#' @return
#'
#' \item{\code{add_prev_result()}}{A \code{\link{data.frame}} based on \code{object}, with an added
#'    column of type \code{\link[base:factor]{ordered factor}} containing the values of the previous
#'    test results.}
#'
#' \item{\code{get_prev_result()}}{An \code{\link[base:factor]{ordered factor}} of length
#'    \code{\link{nrow}(object)}, containing the values of the previous test results ordered in the
#'    exact sequence of the \code{subject} and \code{timepoint} in \code{object}.}
#'
#' @examples
#'
#' \dontshow{
#' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
#'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
#'         include.lowest = TRUE, ordered_result = TRUE))
#' }
#'
#'  ## Continuing example from `add_transitions()`
#'   # subject, timepoint and result arguments all defaults and required types
#' Blackmore |> str()
#'
#'   # Previous test results as ordered factor
#' get_prev_result(Blackmore)
#'
#'   # Previous test result as column of data frame
#' (Blackmore <- add_prev_result(Blackmore)) |> head(32)
#'
#' rm(Blackmore)
#'
add_prev_result <- function(object, subject = "subject", timepoint = "timepoint", result = "result") {
    .Call(`_Transition_add_prev_result`, object, subject, timepoint, result)
}

#' @rdname PreviousResult
get_prev_result <- function(object, subject = "subject", timepoint = "timepoint", result = "result") {
    .Call(`_Transition_get_prev_result`, object, subject, timepoint, result)
}

#' @title
#' Unique Values for Subject, Timepoint and Result
#'
#' @name
#' uniques
#'
#' @description
#' \code{uniques()} identifies unique values for subjects, timepoints and test results in
#' longitudinal study data.
#'
#' @details
#' See \code{\link{Transitions}} \emph{details}.
#'
#' Works for \code{subject} as either an \code{\link[base:vector]{integer vector}} or
#' a \code{\link{factor}}.
#'
#' @family transitions
#' @seealso
#' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
#'
#' @inheritParams Transitions
#'
#' @return
#' A \code{\link{list}} of three elements
#'
#' \item{1.}{An \code{\link[base:vector]{integer vector}} or \code{\link{factor}} of unique subject
#'   identifications.}
#'
#' \item{2.}{A \code{\link{vector}} of class \code{\link{Date}} of unique timepoints in the study.}
#'
#' \item{3.}{An \code{\link[base:factor]{ordered factor}} of unique values for results of the study.}
#'
#' @examples
#'
#' \dontshow{
#' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
#'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
#'         include.lowest = TRUE, ordered_result = TRUE))
#' }
#'
#'  ## Continuing example from `add_transitions()`
#'   # subject, timepoint and result arguments all defaults and required types
#'   # (native subject is factor)
#' uniques(Blackmore)
#'   #
#' Blackmore <- transform(Blackmore, subject = as.integer(subject))
#'   # subject now as integer
#' Blackmore |> str()
#' uniques(Blackmore)
#'
#' rm(Blackmore)
#'
uniques <- function(object, subject = "subject", timepoint = "timepoint", result = "result") {
    .Call(`_Transition_uniques`, object, subject, timepoint, result)
}

