#include <iostream>
#include <stdint.h>
#include <assert.h>
#include "norm.h" 

void test_parent() {
    assert(normalize("/../bar") == "/bar");
    assert(normalize("../bar") == "/bar");
    assert(normalize("/bar/..") == "/");
    assert(normalize("bar/..") == "/");
    assert(normalize("bar/../../") == "/");
    assert(normalize("bar/../../foo") == "/foo");
    assert(normalize("bar/baz/x/../../../foo") == "/foo");
}

void test_current() {
    assert(normalize("/./bar") == "/bar");
    assert(normalize("./bar") == "/bar");
    assert(normalize("/bar/.") == "/bar");
    assert(normalize("bar/.") == "/bar");
}

void test_examples() {
    assert(normalize("/foo/bar") == "/foo/bar");
    assert(normalize("/foo/bar/../baz") == "/foo/baz");
    assert(normalize("/foo/bar/./baz/") == "/foo/bar/baz/");
    assert(normalize("/foo/../../baz") ==  "/baz");
}

void test_hidden_paths() {
    assert(normalize("../.foo./..bar../.") ==  "/.foo./..bar..");
    assert(normalize("/../.foo./..bar../..") ==  "/.foo.");
    assert(normalize("./.foo./..bar.././") ==  "/.foo./..bar../");
}

void test_double_slashes() {
    assert(normalize("//./.foo./..bar../") ==  "/.foo./..bar../");
    assert(normalize("./.foo.//..bar../.") ==  "/.foo./..bar..");
    assert(normalize("./.foo./..bar.././/") ==  "/.foo./..bar..//");
    assert(normalize("./.foo./..bar../..//") ==  "/.foo.//");
}

int32_t main(int32_t argc, char* argv[]) {
    test_parent();
    test_current();
    test_examples();
    test_hidden_paths();
    test_double_slashes();
    return 0;
}
