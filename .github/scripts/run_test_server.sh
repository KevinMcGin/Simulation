#!/bin/bash
github_sha=$1
test_token=$2
testResultId=$(curl https://api.fhionnghaile.ie/api/sim/test/$github_sha/commit -H "tester-token:$test_token");
echo "testResultId: $testResultId";
if [[ $testResultId = *"error"* ]]; then
  exit 1;
fi
testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "tester-token:$test_token");
echo "testResult: $testResult";
if [[ $testResult = *"error"* ]]; then
  exit 1;
fi
isReady=$(echo $testResult | jq -r '.isReady');
while [ $isReady = "false" ]; do
    sleep 10;
    testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "tester-token:$test_token");
    echo "testResult: $testResult";
    if [[ $testResult = *"error"* ]]; then
        exit 1;
    fi
    isReady=$(echo $testResult | jq -r '.isReady');
done
echo $(echo $testResult | jq -r '.message');
isSuccess=$(echo $testResult | jq -r '.isSuccess');
if [ $isSuccess = "false" ]; then
    exit 1;
fi
exit 0;