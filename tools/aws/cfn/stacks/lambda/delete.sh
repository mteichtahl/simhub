#!/bin/bash

. config

FUNCTION_NAME=$1
FUNCTION_PATH=functions
FUNCTION=$FUNCTION_PATH/$FUNCTION_NAME


echo "Deleteing lambda function "$FUNCTION_NAME" from "$FUNCTION
aws cloudformation delete-stack --stack-name $STACK_NAME$FUNCTION_NAME 

if [ $? -eq 0 ] 
then
  echo " - waiting for lambda update to complete"
  aws cloudformation wait stack-create-complete --stack-name $STACK_NAME$FUNCTION_NAME
  echo "Lambda function "$FUNCTION_NAME" has been deleted"
else 
  echo "Lambda deleted"
fi