#!/bin/bash

. config

echo "Updating Kinesis Stream"

aws cloudformation update-stack --stack-name $STACK_NAME --template-body file://stack.json
echo " - waiting for Kinesis Stream update to complete. This may take some time"
aws cloudformation wait stack-update-complete --stack-name $STACK_NAME
