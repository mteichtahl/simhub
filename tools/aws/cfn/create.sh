#!/bin/bash

echo "Creating simhub environment"

cd stacks/dynamo
./create.sh

cd ../kinesis
./create.sh

cd ../lambda
./create.sh processKinesis

