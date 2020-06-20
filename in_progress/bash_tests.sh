#!/usr/bin/env bash

# echo, cd, pwd, export, unset, env, exit

#           _          _        _  __
#\  /  /\  |__) |  /\  |__) |    |__  /__`
# \/  /~~\ |  \ | /~~\ |__) |___ |___ .__/
#

# Note that spaces cannot be used around the = assignment operator
whomvariable="World"

echo
echo =================
echo testing variables
echo =================
echo

echo WEAK :
# Use printf to safely output the data
echo "Hello, $whomvariable"
#> Hello, World
echo

#Execute/Run via: ./hello.sh World
#echo "Hello, $1"
#> Hello, World

echo STRONG :
#vs
echo 'Hello, $whomvariable'
#> Hello, $whom_variable
echo

# _  _        _
#|__  /  ` |__| /  \
#|___ \__, |  | \__/
#

echo
echo ====================
echo unexisting variables
echo ====================
echo

name="myself"
echo "Hello, $name."
echo "You are ${name}ing."
echo "You are ${test}ing."
echo "You are \${test}ing."
echo

echo
echo ===================
echo using the backslash
echo ===================
echo
echo NONE, STRONG, WEAK :
echo \h\e\l\l\o\"\`\'\\
echo '\h\e\l\l\o\"\`\\'
echo "\h\e\l\l\o\"\`\\"
echo
echo NONE, STRONG, WEAK :
echo hello \"
echo 'hello \" '
echo "hello \" "
echo
#  _   _
#/  ` |  \
#\__, |__/
#
echo
echo ===========
echo testing pwd
echo ===========
echo

pwd;
cd ..;pwd;
cd - ;
cd   ;pwd;
cd - ;
cd ~ ;pwd;
cd - ;
