#!/bin/bash

echo "Deleting simhub environment"

cd stacks/lambda
./delete.sh processKinesis

cd ../kinesis
./delete.sh