#!/bin/bash

. config

FUNCTION_NAME=$1
FUNCTION_PATH=functions
FUNCTION=$FUNCTION_PATH/$FUNCTION_NAME

echo "Updating lambda function "$FUNCTION_NAME" from "$FUNCTION

pushd $FUNCTION
zip -q -r $FUNCTION_NAME . -x "*.DS_Store" 
popd

~/Library/Python/2.7/bin/aws s3 cp $FUNCTION/$FUNCTION_NAME.zip $S3_BUCKET/$FUNCTION_NAME

# aws cloudformation update-stack --stack-name $STACK_NAME$FUNCTION_NAME --template-body file://$FUNCTION_PATH/$FUNCTION_NAME/stack.json
~/Library/Python/2.7/bin/aws lambda update-function-code --zip-file fileb://$FUNCTION/$FUNCTION_NAME.zip --publish --function-name simhubLambdaprocessKinesis-ProcessKinesisFunction-16EZRH4FEEMK4

rm $FUNCTION/$FUNCTION_NAME.zip

if [ $? -eq 1 ] 
then
  echo "... waiting for lambda update to complete"
  ~/Library/Python/2.7/bin/aws cloudformation wait stack-update-complete --stack-name $STACK_NAME$FUNCTION_NAME 
  echo "Lambda function "$FUNCTION_NAME" ihas been updated"
else 
  echo "Lambda update failed"
fi