#!/bin/bash
github_sha=$1
test_token=$2
test_endpoint="https://api.fhionnghaile.ie/api/sim/test"
tester_token_header="tester-token:$test_token"
testResultId=$(curl $test_endpoint/$github_sha/commit -H $tester_token_header);
printf "testResultId: $testResultId";
if [[ $testResultId = *"error"* ]]; then
  exit 1;
fi

testResult="";
testStatus="RUNNING";
get_test_result() {
  sleep 10;
  testResult=$(curl $test_endpoint/$testResultId/result -H $tester_token_header);
  printf "test result status: $testResult\n";
  testStatus=$( jq -r  '.testStatus' <<< "${testResult}" );
  printf "testStatus: $testStatus\n";
}

while [[ $testStatus = *"RUNNING"* ]]; do
  get_test_result();
done
printf "final test result: \n";
printf $testResult;
if [[ $testStatus = *"SUCCESS"* ]]; then
    exit 0;
fi
exit 1;