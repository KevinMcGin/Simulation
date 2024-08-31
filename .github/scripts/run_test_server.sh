#!/bin/bash
github_sha=$1
test_token=$2
testResultId=$(curl https://api.fhionnghaile.ie/api/sim/test/$github_sha/commit -H "tester-token:$test_token");
printf "testResultId: $testResultId";
if [[ $testResultId = *"error"* ]]; then
  exit 1;
fi
sleep 10;
testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "tester-token:$test_token");
printf "test result status: $testResult\n";
isReady=$(testResult | jq '.isReady');
while [[ $isReady = false ]]; do
    sleep 10;
    testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "tester-token:$test_token");
    printf "test result status: $testResult\n";
isReady=$(testResult | jq '.isReady');
done
printf "final test result: \n";
printf $testResult;
isSuccess=$(testResult | jq '.isSuccess');
if [[ $isSuccess = true ]]; then
    exit 0;
fi
exit 1;