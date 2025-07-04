# Transition R Package
# Mark Eisler, Ana Rabaza June 2025
#
# Requires R version ≥ 4.1.0
#
# data.R

#' @title
#' Exercise Histories of Eating-Disordered and Control Subjects
#'
#' @description
#' The \code{Blackmore} data frame has 945 rows and 4 columns. Blackmore and Davis's data on
#' exercise histories of 138 teenaged girls hospitalized for eating disorders and 98 control
#' subjects.
#'
#' @usage
#' Blackmore
#'
#' @format
#'
#' This data frame contains the following columns:
#' \describe{
#'   \item{subject}{a factor with subject id codes. There are several observations for each subject,
#'         but because the girls were hospitalized at different ages, the number of cases and the
#'         age at the last case vary.}
#'   \item{age}{subject's age in years at the time of observation; all but the last observation for
#'         each subject were collected retrospectively at intervals of two years, starting at age
#'         8.}
#'   \item{exercise}{the amount of exercise in which the subject engaged, expressed as estimated
#'         hours per week.}
#'   \item{group}{a factor with levels: \code{control}, Control subjects; \code{patient},
#'         Eating-disordered patients.}
#' }
#'
#' @source
#' Personal communication from Elizabeth Blackmore and Caroline Davis, York University.
#'
#' @references
#' Davis C, Blackmore E, Katzman DK, Fox J. (2005). Female adolescents with anorexia nervosa and
#' their parents: a case-control study of exercise attitudes and behaviours. \emph{Psychological
#' Medicine} \strong{35}(3):377-386. \doi{10.1017/S0033291704003447}
#'
#' @note
#' The original version in package \pkg{carData} states there are 98 \code{control} subjects, but the
#' actual data only have 93 unique values, and that assuming \code{subject} id codes with suffixes
#' \code{a} and \code{b} represent different individuals; otherwise, there are just 87.
#'
"Blackmore"