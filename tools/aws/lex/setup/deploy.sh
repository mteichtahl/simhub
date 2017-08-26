#!/bin/bash

STACK_NAME=keyvalquery
S3_BUCKET_NAME_PREFIX=simhub
REGION=us-east-1
BUCKET_NAME=${S3_BUCKET_NAME_PREFIX}-${STACK_NAME}-${REGION}

~/Library/Python/2.7/bin/aws s3 mb s3://${S3_BUCKET_NAME_PREFIX}-${STACK_NAME}-us-east-1 --region $REGION
~/Library/Python/2.7/bin/aws cloudformation package --template-file template.yml --s3-bucket ${BUCKET_NAME} --output-template-file template-export.yml --region ${REGION}
~/Library/Python/2.7/bin/aws cloudformation deploy --template-file template-export.yml --stack-name ${STACK_NAME} --capabilities CAPABILITY_IAM --region ${REGION}
