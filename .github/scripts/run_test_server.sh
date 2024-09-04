#!/bin/bash
github_sha=$1
test_token=$2
test_endpoint="https://api.fhionnghaile.ie/api/sim/test"
tester_token_header="tester-token:$test_token"
test_result_id=$(curl $test_endpoint/$github_sha/commit -H $tester_token_header);
printf "test_result_id: $test_result_id\n";
if [[ "$test_result_id" = *"error"* ]]; then
  exit 1;
fi

test_result="";
test_status="RUNNING";
tries=0;
max_tries=50;
get_test_result() {
  sleep 10;
  test_result=$(curl $test_endpoint/$test_result_id/result -H $tester_token_header);
  printf "test result status: $test_result\n";
  test_status=$( jq -r  '.testStatus' <<< "${test_result}" );
  printf "test_status: $test_status\n";
  tries=$((tries + 1));
}

while [[ "$test_status" = *"RUNNING"* && $tries < $max_tries ]]; do
  get_test_result;
done
printf "final test result: \n$test_result\n";
if [[ "$test_status" = *"SUCCESS"* ]]; then
    exit 0;
fi
exit 1;