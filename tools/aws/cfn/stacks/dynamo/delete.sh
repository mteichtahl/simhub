#!/bin/bash

. config

echo "Deleting cloudformation stack "$STACK_NAME
/Users/teichtah/Library/Python/2.7/bin/aws cloudformation delete-stack --stack-name $STACK_NAME --region $REGION

if [ $? -eq 0 ] 
then
  echo " - waiting for deletion to complete"
  /Users/teichtah/Library/Python/2.7/bin/aws cloudformation wait stack-delete-complete --stack-name $STACK_NAME --region $REGION
fi
