
# Initialize the test output

# Fail a test

fail() {
  echo "$@"
  exit 1
}

# Assert that some command runs ok

should() {
  if eval "$@" >test.out 2>&1 ; then
    true
  else
    fail "Cmd $@ failed with status of $?"
  fi
}

# Assert that some test will fail

should_not() {
  if eval "$@" >test.out 2>&1 ; then
    fail "Cmd $@ did not fail as expected"
  fi
}

# Assert that some command will output a matching string

should_match() {
  re=$1
  shift
  output=`eval "$@"`

  if echo "$output" | grep -e "$re"  >test.out 2>&1; then
    true
  else
    echo Output: $output >test.out
    fail "Output of $@ did not match $re"
  fi
}

# Assert that some command will output a matching string

should_not_match() {
  re=$1
  shift
  output=`eval "$@"`

  if echo "$output" | grep -e "$re"  >test.out 2>&1; then
    echo Output: $output >test.out
    fail "Output of $@ did match $re"
  else
    true
  fi
}

