#!/bin/bash

echo "Creating simhub environment"

cd stacks/kinesis
./create.sh

cd ../lambda
./create.sh processKinesis

