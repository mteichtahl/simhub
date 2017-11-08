#!/bin/bash

. config


echo "Creating Dynamo Table(s)"
/Users/teichtah/Library/Python/2.7/bin/aws cloudformation create-stack --stack-name $STACK_NAME --template-body file://stack.json --region $REGION

if [ $? -eq 0 ] 
then
  echo " - waiting for Dynamo creation to complete"
  /Users/teichtah/Library/Python/2.7/bin/aws cloudformation wait stack-create-complete --stack-name $STACK_NAME --region $REGION
  echo "Dynamo creation completed."
    /Users/teichtah/Library/Python/2.7/bin/aws cloudformation describe-stacks --stack-name $STACK_NAME --region $REGION --output json | jq '.[][0].Outputs'

else 
  echo "Dynam creation failed"
fi
