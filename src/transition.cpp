
// [[Rcpp::plugins(cpp23)]]

#include <Rcpp.h>
#include <cxxabi.h>
using namespace Rcpp;

#include "transition.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;


/// __________________________________________________
/// __________________________________________________
/// Development and Debugging functions
#ifdef DEBUG

/// Report object construction and destruction
void _ctrsgn(const std::type_info& obj, bool destruct)
{
//	cout << (destruct ? "Destroying " : "Constructing ") << std::flush;
	string s { obj.name() };
	system(("c++filt -t " + s).data());
}

/// Demangle object names functor
class Demangler {
	char* p;
	int status { 0 };
public:
	Demangler(const std::type_info& obj) : p(abi::__cxa_demangle(obj.name(), NULL, NULL, &status)) {}
	~Demangler() { std::free(p); }
	operator string() const { return string("\"") + p + "\" (status " + std::to_string(status) + ")"; }
};

ostream& operator<< (ostream& stream, const Demangler& d)
{
//  cout << "ostream& operator<< (ostream&, const Demangler&) ";
  return stream << string(d);
}

#endif // #ifdef DEBUG

/// __________________________________________________
/// Utility

/// __________________________________________________
/// Return named attribute as vector<U> or empty vector<U>
template<class T, class U>
inline vector<U> get_vec_attr(const T& t, const char* attrname)
{
//	cout << "@get_vec_attr<T, U>(const T&, const char*) attr \"" << attrname << "\" " << std::boolalpha << t.hasAttribute(attrname) << endl;
	static_assert(std::is_same<NumericVector, T>::value || std::is_same<DataFrame, T>::value, "T must be NumericVector or DataFrame");
	return t.hasAttribute(attrname) ? as<vector<U>>(t.attr(attrname)) : vector<U>();
}


/// __________________________________________________
/// string to lower case (see cppreference.com std::tolower)
inline string str_tolower(string s)
{
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
    return s;
}


/// __________________________________________________
/// Find data frame column with a specified name
int colpos(const DataFrame object, const char* colname)
{
//	cout << "@colpos(const DataFrame, const char*) name is " << colname << endl;
	if (!object.containsElementNamed(colname))
		stop("No column named \"%s\" in data frame", colname);
//		throw Rcpp::exception("No column named \"%s\" in data frame", colname);
	return object.offset(colname);
}


// Find unique values in vector
template<class T>
vector<T> get_unique(const vector<T> vec)
{
//	cout << "@get_unique<T>(const vector<T>) vec " << Demangler(typeid(vec)) << endl;
	vector<T> out { vec };
	std::sort(out.begin(), out.end());
	auto last { std::unique(out.begin(), out.end()) };
	out.erase(last, out.end());
	return out;
}


// Narrow the difference, symmetrically
inline int angust(int diff, int cutoff)
{
//	cout << "@angust(int, int) diff " << diff << "; cutoff " << cutoff << endl;
	int out { abs(diff) < cutoff ? abs(diff) : cutoff};
	return std::signbit(diff) ? out *= -1 : out;
}


// Adjust the difference,symmetrically
inline int adjust(int diff)
{
//	cout << "@adjust(int) diff " << diff << endl;
	int out = (abs(diff) + 1) / 2;
	return std::signbit(diff) ? out *= -1 : out;
}


/// __________________________________________________
/// Class Transitiondata

// Ctor auxilliary function
	template<typename T>
	T Transitiondata::typechecker(int colno, int arg)
	{	
//		cout << "@Transitiondata::typechecker<T>(int, int) colno " << colno << "; arg " << arg << std::endl;
		bool ordfct(true);
		if (3 == arg) {
			RObject colobj { df[colno] };
			if (!(colobj.inherits("factor") && colobj.inherits("ordered")))
				ordfct = false;
		}
		if (!(is<T>(df[colno]) && ordfct)) {
			std::vector<string> typestr {"data.frame", "integer or factor", "Date", "ordered factor" };
			throw std::invalid_argument(std::string("column `") + vector<string>(df.names())[colno] + "` not of type " + typestr[arg]);
		}
		return df[colno];
	}

// Test result for given subject and date
int Transitiondata::get_result(int subject, double date) const
{
//	cout << "@Transitiondata::get_result(int, double) const subject = " << subject << "; date = " << Date(date).getYear() << endl;
	for (int x { 0 }; x < nrows; ++x)
		if (id[x] == subject && testdate[x] == date) {
			return testresult[x];
		}
	return NA_INTEGER;
}

// All dates for a given subject, sorted
std::vector<double> Transitiondata::get_id_dates(int target) const
{
//	cout << "@Transitiondata::get_id_dates(int id) const target = " << target << endl;
	vector<double> out;
	for (int x { 0 }; x < nrows; ++x) {
		if (id[x] == target)
			out.push_back(testdate[x]);
	}
	std::sort(out.begin(), out.end());
	return out;
}

// most recent previous date for subject
double Transitiondata::get_prevdate(int subject, double date) const
{
//	cout << "@Transitiondata::get_prevdate(int, double) const subject = " << subject << "; date = " << Date(date).getYear() << endl;
	auto dates { get_id_dates(subject) };
	auto it { find(dates.begin(), dates.end(), date) };
	if (it == dates.end())
		stop("testdate %s not found for subject %i.", Date(date).format("%Y"), subject);
	return (it == dates.begin()) ? NA_REAL : *std::prev(it);
}

// vector of the most recent previous date by subject
vector<double> Transitiondata::prev_date() const
{
//	cout << "@Transitiondata::prev_date() const\n";
	vector<double> previous(nrows);
	transform(id.begin(), id.end(), testdate.begin(), previous.begin(), [this](int id, double date){ return get_prevdate(id, date); });
	return previous;
}

// vector of the most recent previous result by subject
vector<int> Transitiondata::prev_result() const
{
//	cout << "@Transitiondata::prev_result() const\n";	
	auto prevdate { prev_date() };
	vector<int> prevres(nrows);
	transform(id.begin(), id.end(), prevdate.begin(), prevres.begin(), [this](int id, double date){ return get_result(id, date); });
	return prevres;
}


// Add transitions column to data frame
DataFrame Transitiondata::add_transition(const char* colname, int method)
{
//	cout << "@Transitiondata::add_transition(int)\n";
	if (df.containsElementNamed(colname))
		stop("Data frame already has column named \"%s\", try another name", colname);
 	df.push_back(get_transition(method), colname);
	return df;
}


// Return transitions vector
vector<int> Transitiondata::get_transition(int method) const
{
//	cout << "@Transitiondata::get_transition(int) method = " << method << endl;
	if (method < 1 || method > 5)
		stop("\"method\" must be between 1 and 5");
	auto previous { prev_result() };
	std::vector<int> transitions(nrows);
	transform(previous.begin(), previous.end(), testresult.begin(), transitions.begin(),
		[method](int prev, int curr)
		{
			if (NA_INTEGER == prev)
				return NA_INTEGER;
			else {
				int diff {curr - prev};
				if (5 == method)
					return adjust(diff);
				else
					return angust(diff, 5 - method);
			}
		}
	);
	return transitions;
}


/// __________________________________________________
/// Auxilliary
inline IntegerVector prevres_intvec(DataFrame object, const char* subject, const char* timepoint, const char* result)
{
//	cout << "@prevres_intvec(DataFrame, const char*, const char*, const char*) subject " << subject
//		 << "; timepoint " << timepoint << "; result " << result << endl;
	int testcol { colpos(object, result) };
	IntegerVector intvec(wrap(vector<int>(Transitiondata(object, colpos(object, subject), colpos(object, timepoint), testcol).prev_result())));
	intvec.attr("class") = CharacterVector::create("factor", "ordered");
	intvec.attr("levels") = (RObject { object[testcol] }).attr("levels");
	return intvec;
}


/// __________________________________________________
/// Exported

//' @title
//' Identify Temporal Transitions in Longitudinal Study Data
//'
//' @name
//' Transitions
//'
//' @description
//' \code{get_transitions()} identifies temporal transitions in test results for individual
//' subjects in a longitudinal study.
//'
//' \code{add_transitions()} interpolates these transitions into a data frame for further analysis.
//'
//' @details
//' The data can be presented in any order e.g., ordered by \code{subject}, by \code{timepoint},
//' forwards or backwards in time, or entirely at random, and may have unbalanced designs with different
//' time points or numbers of test results per subject. However, the \emph{user} is responsible for
//' ensuring the data contain unique combinations of \code{subject}, \code{timepoint} and \code{result};
//' if not, outputs will be undefined.
//'
//' Time points should be formatted as \code{\link{Dates}} and included in data frame \code{object} in
//' the column named as specified by argument \code{timepoint} (see \emph{Note}).
//'
//' Test results should be semi-quantitiative, formatted as \code{\link[base:ordered]{ordered factor}}
//' and included in data frame \code{object} in the column named as specified by argument \code{result}
//' (see \emph{Note}).
//'
//' Temporal transitions in the test \code{results} for each \code{subject} within the \code{object}
//' \code{\link{data.frame}} are characterised using one of various methods choosen using option
//' \code{method}.
//'
//' @family transitions
//' @seealso
//' \code{\link{data.frame}}, \code{\link{Dates}}, and \code{\link[base:factor]{ordered factor}}.
//'
//' @param object a \code{\link{data.frame}} (or object coercible by \code{\link{as.data.frame}()} to
//'   a data frame) containing the data to be analysed.
//'
//' @param subject \code{\link{character}}, name of the column (of type \code{\link{integer}} or
//'   \code{\link{factor}}) identifying individual study subjects; default \code{"subject"}.
//'
//' @param timepoint \code{character}, name of the column recording time points (as \code{\link{Dates}})
//'   of testing of subjects; default \code{"timepoint"}.
//'
//' @param result \code{character}, name of the column (of type \code{\link[base:factor]{ordered factor}})
//'   recording test results; default \code{"result"}.
//'
//' @param transition \code{character}, name to be used for a new column (of type
//'   \code{\link{integer}}) to record transitions; default \code{"transition"}.
//'
//' @param method \code{\link{integer}}, \code{1L}, \code{2L}, ... \code{5L}, specifying the method
//'   required for calculating transitions; default \code{1L}.
//'
//' @return
//'
//' \item{\code{add_transitions()}}{A \code{\link{data.frame}} based on \code{object}, with an added
//'    column of type \code{\link{integer}} containing the values of the test result transitions.}
//'
//' \item{\code{get_transitions()}}{An \code{\link[base:vector]{integer vector}} of length
//'    \code{\link{nrow}(object)}, containing the values of the test result transitions ordered in the exact
//'    sequence of the \code{subject} and \code{timepoint} in \code{object}.}
//'
//' @note
//' Time points represented by \code{\link{integer}} or \code{\link{numeric}} values can be converted to R
//'   \code{Dates} conveniently using \code{\link{as.Date}()}. If only the year is available, an arbitrary
//'   value may be used consistently for month and day e.g., the 1st of January; likewise, the 1st day of the
//'   month could be used if only the year and month are available (see \emph{examples}).
//'
//' Quantitive results available as \code{\link{numeric}} data can be converted to a semi-quantitative
//'   \code{\link[base:factor]{ordered factor}} conveniently using \code{\link{cut}()}.
//'
//' @examples
//'
//'   # Inspect Blackmore data frame using {base} str()
//' Blackmore |> str()
//'   # {base} hist() gives insights into "exercise" column, useful for {base} cut() below
//' hist(Blackmore$exercise, include.lowest = TRUE, plot = FALSE)[1:2]
//'   # Convert "age" to dates for timepoint argument, using arbitrary "origin" 1-Jan-2000,
//'   # and convert exercise to ordered factor "result" using cut()
//' Blackmore <- transform(Blackmore,
//'     timepoint = as.Date("2000-01-01") + round(age * 365.25),
//'     result = cut(
//'         exercise,
//'         breaks = seq(0, 30, 2),
//'         labels = paste0("<=", seq(0, 30, 2)[-1]),
//'         include.lowest = TRUE,
//'         ordered_result = TRUE
//'     )
//' )
//'   # subject, timepoint and result arguments now as defaults and required types
//' Blackmore |> str()
//'   # Integer vector of test result transitions (default method 1)
//' get_transitions(Blackmore)
//'   # Add column of test result transitions to data frame
//' add_transitions(Blackmore) |> head(32)
//'   # Method 4, showing transitions as either positive (1) or negative (-1)
//' add_transitions(Blackmore, method = 4) |> head(10)
//'
//' rm(Blackmore)
//'
//' ## Formatting numeric values as R dates
//'
//' #  Data frame containing year as numeric: 2018 to 2025
//' (df <- data.frame(
//'     subject = rep(1001:1002, 4),
//'     timepoint = 2018:2025
//'     ))
//'
//' #  Convert to R dates
//' (df <- transform(df, timepoint = as.Date(paste(timepoint, "01", "01", sep = "-"))))
//'
//' # Format R dates to show just the year
//' (df <- transform(df, year = format(timepoint, "%Y")))
//'
//' #  Data frame containing year and month as numeric: July 2024 to June 2025
//' (df <- data.frame(
//'            subject = rep(1001:1002, 6),
//'            year = rep(2024:2025, each = 6),
//'            month = c(7:12, 1:6)
//'        ))
//'
//' #  Convert to R dates
//' df <- transform(df, timepoint = as.Date(paste(year, month, "01", sep = "-")))
//' \dontshow{
//'     df$year <- NULL
//'     df$month <- NULL
//' }
//' df
//'
//' # Format R dates to show just the month and year
//' (df <- transform(df, month_year = format(timepoint, "%b-%Y")))
//'
//' rm(df)
//'
// [[Rcpp::export]]
DataFrame add_transitions(
	DataFrame object,
	const char* subject = "subject",
	const char* timepoint = "timepoint",
	const char* result = "result",
	const char* transition = "transition",
	int method = 1)
{
//	cout << "——Rcpp::export——add_transitions(DataFrame, const char*, const char*, const char*, const char*, int) subject " << subject
//		 << "; timepoint " << timepoint << "; result " << result << "; transition " << transition << endl;
	try {
		return Transitiondata(object, colpos(object, subject), colpos(object, timepoint), colpos(object, result)).add_transition(transition, method);
	} catch (exception& e) {
		Rcerr << "Error in add_transitions(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return DataFrame::create();
}


//' @rdname Transitions
// [[Rcpp::export]]
IntegerVector get_transitions(
	DataFrame object,
	const char* subject = "subject",
	const char* timepoint = "timepoint",
	const char* result = "result",
	int method = 1)
{
//	cout << "——Rcpp::export——get_transitions(DataFrame, const char*, const char*, const char*, int) subject " << subject
//		 << "; timepoint " << timepoint << "; result " << result << endl;
	try {
		return wrap(Transitiondata(object, colpos(object, subject), colpos(object, timepoint), colpos(object, result)).get_transition(method));
	} catch (exception& e) {
		Rcerr << "Error in get_transitions(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return IntegerVector();
}


//' @title
//' Find Previous Test Date for Subject
//'
//' @name
//' PreviousDate
//'
//' @description
//' \code{get_prev_dates()} identifies the previous test date for individual subjects and timepoints
//' in a longitudinal study.
//'
//' \code{add_prev_date()} interpolates these previous test dates into a data frame for further analysis.
//'
//' @details
//' See \code{\link{Transitions}} \emph{details}.
//'
//' @family transitions
//' @seealso
//' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
//'
//' @inheritParams Transitions
//'
//' @return
//'
//' \item{\code{add_prev_date()}}{A \code{\link{data.frame}} based on \code{object}, with an added
//'    column of class \code{\link{Date}} containing the values of the previous test dates.}
//'
//' \item{\code{get_prev_date()}}{An \code{vector} of length \code{\link{nrow}(object)},
//'    class \code{\link{Date}}, containing the values of the previous test dates ordered in the exact
//'    sequence of the \code{subject} and \code{timepoint} in \code{object}.}
//'
//'
//' @examples
//'
//' \dontshow{
//' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
//'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
//'         include.lowest = TRUE, ordered_result = TRUE))
//' }
//'  ## Continuing example from `add_transitions`
//'   # subject, timepoint and result arguments all as defaults and required types
//' Blackmore |> str()
//'   # Integer vector of the previous test dates
//' get_prev_date(Blackmore)
//'   # Add column of  previous test dates to data frame
//' add_prev_date(Blackmore) |> head(32)
//'
//' rm(Blackmore)
//'
// [[Rcpp::export]]
DataFrame add_prev_date(DataFrame object, const char* subject = "subject", const char* timepoint = "timepoint", const char* result = "result")
{
//	cout << "——Rcpp::export——add_prev_date(DataFrame, const char*, const char*, const char*) subject " << subject << "; timepoint " << timepoint << "; result " << result << endl;
	try {
		object.push_back(DateVector(wrap(Transitiondata(object, colpos(object, subject), colpos(object, timepoint), colpos(object, result)).prev_date())), "prev_date");
		return object;
	} catch (exception& e) {
		Rcerr << "Error in add_prev_date(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return DataFrame::create();
}


//' @rdname PreviousDate
// [[Rcpp::export]]
DateVector get_prev_date(DataFrame object, const char* subject = "subject", const char* timepoint = "timepoint", const char* result = "result")
{
//	cout << "——Rcpp::export——get_prev_date(DataFrame, const char*, const char*, const char*) subject " << subject << "; timepoint " << timepoint << "; result " << result << endl;
	try {
		return wrap(Transitiondata(object, colpos(object, subject), colpos(object, timepoint), colpos(object, result)).prev_date());
	} catch (exception& e) {
		Rcerr << "Error in get_prev_date(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return DateVector(0);
}


//' @title
//' Find Previous Test Result for Subject
//'
//' @name
//' PreviousResult
//'
//' @description
//' \code{get_prev_results()} identifies the previous test result for individual subjects and timepoints
//' in a longitudinal study.
//'
//' \code{add_prev_result()} interpolates these previous test results into a data frame for further analysis.
//'
//' @details
//' See \code{\link{Transitions}} \emph{details}.
//'
//' Differences between levels of a result and the previous result for the same subject may easily be
//' calculated as an alternative to using \code{\link{add_transitions}()} or
//' \code{\link{get_transitions}()}, allowing application of any user-defined function to these
//' differences, see \emph{examples}.
//'
//' @family transitions
//' @seealso
//' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
//'
//' @inheritParams Transitions
//'
//' @return
//'
//' \item{\code{add_prev_result()}}{A \code{\link{data.frame}} based on \code{object}, with an added
//'    column of type \code{\link[base:factor]{ordered factor}} containing the values of the previous
//'    test results.}
//'
//' \item{\code{get_prev_result()}}{An \code{\link[base:factor]{ordered factor}} of length
//'    \code{\link{nrow}(object)}, containing the values of the previous test results ordered in the
//'    exact sequence of the \code{subject} and \code{timepoint} in \code{object}.}
//'
//' @examples
//'
//' \dontshow{
//' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
//'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
//'         include.lowest = TRUE, ordered_result = TRUE))
//' }
//'  ## Continuing example from `add_transitions`
//'   # subject, timepoint and result arguments all as defaults and required types
//' Blackmore |> str()
//'   # Previous test results as ordered factor
//' get_prev_result(Blackmore)
//'   # Previous test result as column of data frame
//' (Blackmore <- add_prev_result(Blackmore)) |> head(32)
//'   # Difference between levels of current and previous results as integer vector
//' (diffs <- with(Blackmore, as.integer(result) - as.integer(prev_result)))
//'   # Differences as data frame column "transition"
//' Blackmore$transition <- diffs
//' Blackmore |> head(32)
//'   # More esoteric, user-defined function of the differences as integer vector
//' (diffs2 <- with(Blackmore, as.integer((abs(transition) + 1) / 3) * sign(transition)))
//'   # Function range as data frame column "transition2"
//' Blackmore$transition2 <- diffs2
//' Blackmore |> head(36)
//'
//' rm(Blackmore, diffs, diffs2)
//'
// [[Rcpp::export]]
DataFrame add_prev_result(DataFrame object, const char* subject = "subject", const char* timepoint = "timepoint", const char* result = "result")
{
//	cout << "——Rcpp::export——add_prev_result(DataFrame, const char*, const char*, const char*) subject " << subject << "; timepoint " << timepoint << "; result " << result << endl;
	try {
		object.push_back(prevres_intvec(object, subject, timepoint, result), "prev_result");
		return object;
	} catch (exception& e) {
		Rcerr << "Error in add_prev_result(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return DataFrame::create();
}


//' @rdname PreviousResult
// [[Rcpp::export]]
IntegerVector get_prev_result(DataFrame object, const char* subject = "subject", const char* timepoint = "timepoint", const char* result = "result")
{
//	cout << "——Rcpp::export——get_prev_result(DataFrame, const char*, const char*, const char*) subject " << subject << "; timepoint " << timepoint << "; result " << result << endl;
	try {
		return prevres_intvec(object, subject, timepoint, result);
	} catch (exception& e) {
		Rcerr << "Error in get_prev_result(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return IntegerVector();
}


//' @title
//' Unique Values for Subject, Timepoint and Result
//'
//' @name
//' uniques
//'
//' @description
//' \code{uniques()} identifies unique values for subjects, timepoints and test results in
//' longitudinal study data.
//'
//' @details
//' See \code{\link{Transitions}} \emph{details}.
//'
//' Works for \code{subject} as either an \code{\link[base:vector]{integer vector}} or
//' a \code{\link{factor}}.
//'
//' @family transitions
//' @seealso
//' \code{\link{data.frame}}, \code{\link{Dates}}, \code{\link[base:factor]{ordered factor}}.
//'
//' @inheritParams Transitions
//'
//' @return
//' A \code{\link{list}} of three elements
//'
//' \item{1.}{An \code{\link[base:vector]{integer vector}} or \code{\link{factor}} of unique subject
//'   identifications.}
//'
//' \item{2.}{A \code{\link{vector}} of class \code{\link{Date}} of unique timepoints in the study.}
//'
//' \item{3.}{An \code{\link[base:factor]{ordered factor}} of unique values for results of the study.}
//'
//' @examples
//'
//' \dontshow{
//' Blackmore <- transform(Blackmore, timepoint = as.Date("2000-01-01") + round(age * 365.25),
//'     result = cut(exercise, breaks = seq(0, 30, 2), labels = paste0("<=", seq(0, 30, 2)[-1]),
//'         include.lowest = TRUE, ordered_result = TRUE))
//' }
//'  ## Continuing example from `add_transitions`
//'   # subject, timepoint and result arguments all as defaults and required types
//'   # (native subject is factor)
//' uniques(Blackmore)
//'   #
//' Blackmore <- transform(Blackmore, subject = as.integer(subject))
//'   # subject now as integer
//' Blackmore |> str()
//' uniques(Blackmore)
//'
//' rm(Blackmore)
//'
// [[Rcpp::export]]
List uniques(DataFrame object, const char* subject = "subject", const char* timepoint = "timepoint", const char* result = "result")
{
//	cout << "——Rcpp::export——uniques(DataFrame)\n";
	try {
		Transitiondata td(object, colpos(object, subject), colpos(object, timepoint), colpos(object, result));
		IntegerVector subvec(wrap(td.unique_sub()));
		RObject subcol{ object[colpos(object, subject)] };
		if (subcol.inherits("factor")) {
			subvec.attr("class") = string { "factor" };			
			subvec.attr("levels") = subcol.attr("levels");
		}
		IntegerVector rltvec(wrap(td.unique_test()));
		rltvec.attr("class") = CharacterVector::create("factor", "ordered");
		rltvec.attr("levels") = (RObject { object[colpos(object, result)] }).attr("levels");
		return List::create(_[subject] = subvec, _[timepoint] = td.unique_date(), _[result] = rltvec);
	} catch (exception& e) {
		Rcerr << "Error in uniques(): " << e.what() << '\n';
	} catch (std::invalid_argument& iva) {
		Rcerr << "Error invalid argument: " << iva.what() << '\n';
	}
	return List::create();
}
