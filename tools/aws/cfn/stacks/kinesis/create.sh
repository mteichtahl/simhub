#!/bin/bash

. config


echo "Creating Kinesis Stream"
aws cloudformation create-stack --stack-name $STACK_NAME --template-body file://stack.json 

if [ $? -eq 0 ] 
then
  echo " - waiting for Kinesis Stream creation to complete"
  aws cloudformation wait stack-create-complete --stack-name $STACK_NAME
  aws s3 rm $S3_BUCKET/$S3_KEY
  echo "Kinesis Stream creation completed."
    aws cloudformation describe-stacks --stack-name $STACK_NAME --output json | jq '.[][0].Outputs'

else 
  echo "Kinesis Stream creation failed"
fi
