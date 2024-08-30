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
isReady=$(echo $testResult | jq -r '.isReady');
while [ $isReady = "false" ]; do
    sleep 10;
    testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "tester-token:$test_token");
    echo "testResult: $testResult";
    isReady=$(echo $testResult | jq -r '.isReady');
done
printf "final test result message: $testResult\n";
printf $(echo $testResult | jq -r '.message');
isSuccess=$(echo $testResult | jq -r '.isSuccess');
if [ $isSuccess = "true" ]; then
    exit 0;
fi
exit 1;