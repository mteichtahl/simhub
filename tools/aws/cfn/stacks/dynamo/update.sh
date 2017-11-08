#!/bin/bash

. config

echo "Updating Dynamo"

aws cloudformation update-stack --stack-name $STACK_NAME --template-body file://stack.json --region $REGION
echo " - waiting for dynamo update to complete. This may take some time"
aws cloudformation wait stack-update-complete --stack-name $STACK_NAME --region $REGION
