#!/bin/bash

. config

FUNCTION_NAME=$1
FUNCTION_PATH=functions
FUNCTION=$FUNCTION_PATH/$FUNCTION_NAME


echo "Creating lambda function "$FUNCTION_NAME" from "$FUNCTION

pushd $FUNCTION
zip -q -r $FUNCTION_NAME . -x "*.DS_Store" 
popd

aws s3 cp $FUNCTION/$FUNCTION_NAME.zip $S3_BUCKET/$FUNCTION_NAME.zip
rm $FUNCTION/$FUNCTION_NAME.zip

aws cloudformation create-stack --stack-name $STACK_NAME$FUNCTION_NAME --template-body file://$FUNCTION_PATH/$FUNCTION_NAME/stack.json

if [ $? -eq 0 ] 
then
  echo " - waiting for lambda creation to complete"
  aws cloudformation wait stack-create-complete --stack-name $STACK_NAME$FUNCTION_NAME
  echo "Lambda function "$FUNCTION_NAME" is ready"
  aws cloudformation describe-stacks --stack-name $STACK_NAME$FUNCTION_NAME --output json | jq '.[][0].Outputs'
else 
  echo "Lambda creation failed"
fi