#!/bin/bash
testResultId=$(curl https://api.fhionnghaile.ie/api/sim/test/${{ github.sha }}/commit -H "TEST-TOKEN:test");
echo $testResultId;
if [[ $testResultId == *"error"* ]]; then
  exit 1;
fi;
testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "TEST-TOKEN:test");
if [[ $testResult == *"error"* ]]; then
  exit 1;
fi
isReady=$(echo $testResult | jq -r '.isReady');
while [ $isReady = "false" ]; do
    sleep 10;
    testResult=$(curl https://api.fhionnghaile.ie/api/sim/test/$testResultId/result -H "TEST-TOKEN:test");
    if [[ $testResult == *"error"* ]]; then
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