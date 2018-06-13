#include "catch.hpp"
#include "../catch2-multiline-matcher.hpp"

using CatchExtension::OneLineMatches;
using CatchExtension::NoLinesMatch;
using CatchExtension::AllLinesMatch;

using CatchExtension::OneLineContains;
using CatchExtension::NoLinesContain;
using CatchExtension::AllLinesContain;

using CatchExtension::NoLineMatches;	// synonym for NoLinesMatch
using CatchExtension::NoLineContains;	// synonym for NoLineContains

using Catch::CaseSensitive;


TEST_CASE("README.md") {
	SECTION( "demo") {
		CHECK_THAT("foo\nbar\nbaz", OneLineMatches("foo"));
		CHECK_THAT("foo xxx\nbar xxx\nbaz xxx", OneLineMatches("foo.*"));
		CHECK_THAT("foo xxx\nbar xxx\nbaz xxx", AllLinesMatch(".*xxx"));
		CHECK_THAT("foo\nbar\nbaz", OneLineMatches("FOO", CaseSensitive::Choice::No));
		CHECK_THAT("foo", NoLinesMatch("bar"));
		CHECK_THAT("foo", !NoLinesMatch("foo"));
		
		// & similarly for Contains
		CHECK_THAT("foo\nbar", OneLineContains("oo"));
		CHECK_THAT("foo\nbar", OneLineContains("OO", CaseSensitive::Choice::No));
		// ... etc
	}
}
